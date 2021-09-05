var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var db = require('./db');
var urlencodedParser = bodyParser.urlencoded({ extended: false });

app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
    res.header("Access-Control-Allow-Headers", "X-Requested-With");
    res.header('Access-Control-Allow-Headers', 'Content-Type');
    next();
});//处理跨域请求

app.use('/public', express.static('public'));
//设置主页面，登录，注册页面
app.get('/main.html', function (req, res) {
    res.sendFile(__dirname + '/' + 'main.html');
})
app.get('/login.html', function (req, res) {
    res.sendFile(__dirname + '/' + 'login.html');
})
app.get('/register.html', function (req, res) {
    res.sendFile(__dirname + '/' + 'register.html');
})
app.get('/', function (req, res) {//主页面作为默认界面main.html
    res.sendFile(__dirname + '/' + 'main.html');
})
//为注册和登录操作添加接口
//登录接口
app.post('/process_login', urlencodedParser, function (req, res) {
    var userName = req.body.userName;
    var pwd = req.body.pwd; 
    if (!userName) {
        res.json({ code: -1, message: '用户名不能为空' });
    } else if (!pwd) {
        res.json({ code: -1, message: '密码不能为空' });
    } else {
        db.searchUser({ name: userName }, function (result) {
            if (result.length > 0) {
                if (result[0].name == userName && result[0].pwd == pwd) {
                    res.json({ code: 0, message: '登录成功' }); 
                } else {
                    res.json({ code: -1, message: '用户名或密码错误' });
                }
            } else {
                res.json({ code: -1, message: '不存在该用户' });
            }
        });
    }
})

//注册接口
app.post('/process_register', urlencodedParser, function (req, res) {
    var userName = req.body.userName;
    var pwd = req.body.pwd;
    if (!userName) {
        res.json({ code: -1, message: '用户名不能为空' });
    } else if (!pwd) {
        res.json({ code: -1, message: '密码不能为空' });
    } else {
        db.searchUser({ name: userName }, function (result) {
            if (result.length > 0 && result[0].name == userName) {
                res.json({ code: -1, message: '用户已存在，可直接登录' });
            } else {
                // res.json({ code: -1, message: '不存在该用户' });
                db.insertUser({ name: userName, pwd: pwd }, function (insertResult) {
                    console.log(insertResult)
                    if (insertResult.insertedCount > 0) {
                        res.json({ code: 0, message: '注册成功' });
                    } else {
                        res.json({ code: -1, message: '注册失败，请重新注册' });
                    }
                })
            }
        });
    }
})
//8080端口监听
var server = app.listen(8008, function () { 
    console.log("后端启动成功！")
})