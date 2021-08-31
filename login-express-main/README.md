# login-express
实现了登陆注册功能的小项目，全部使用js和html完成，使用MongoDB作为数据库。欢迎star。

本项目借鉴了[这个项目](https://github.com/Lemon-Yan/node-login)，大家也可以去star。

## 结果展示

实现的功能：

- 主页面，登陆页面，注册页面
- 注册密码两次输入
- 验证码检验

使用的技术

- 使用**MongoDB**作为后端数据库保存用户信息
- 使用**node.js**部署前端
- 采用**ajax**实现前端与服务器交换数据

直接输入网址（http://localhost:8008/）进入主界面，提示需要登陆

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201226160547957.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzI2MzM0Ng==,size_16,color_FFFFFF,t_70)


进入注册界面注册账号

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201226160708586.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzI2MzM0Ng==,size_16,color_FFFFFF,t_70)


注册成功进入主页面

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201226161156553.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzI2MzM0Ng==,size_16,color_FFFFFF,t_70)


也可以从登陆界面进入
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201226161216516.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzI2MzM0Ng==,size_16,color_FFFFFF,t_70)
## 环境配置

### MongoDB

在ubuntu20.04下安装MongoDB

```sh
sudo apt-get install mongodb
```

在项目目录下建立MongoDB的数据和日志目录

```sh
mkdir log
mkdir data
```

启动MongoDB

```sh
mongod --dbpath ./data/ --logpath ./log/mongod.log --fork
```

检查MongoDB是否已经启动

```sh
ps aux|grep mongo
```

输出为

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201226161304738.png)


说明启动成功。

检查MongoDB监听的默认端口

```sh
lsof -i:27017
```

输出为

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201226161313528.png)


和上图的pid一致，说明端口已经被打开。

或者在OSX上安装MongoDB

```sh
brew tap mongodb/brew 
brew install mongodb-community@4.2
```

启动和关闭

```sh
brew services start mongodb-community@4.2
brew services stop mongodb-community@4.2
```

### 配置node.js

```sh
sudo apt-get install nodejs
sudo apt-get install npm
```

在项目下需要安装的node.js模块

```shell
npm install express --save
npm install body-parser --save
npm install cookie-parser --save
npm install multer --save
npm install mongodb --save
```

其中

- express是我们使用的前端框架

- body-parser用于处理 JSON, Raw, Text 和 URL 编码的数据。

- cookie-parser解析Cookie

- multer 用于处理MIME编码的表单数据。

## 主要代码

### 后端

项目的后端是Express和MongoDB，在项目目录下启动`node backend.js`启动后端。

#### Express

启动Express

```js
var express = require('express');
var app = express();
```

后端程序中需要处理浏览器的跨域请求

```js
app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
    res.header("Access-Control-Allow-Headers", "X-Requested-With");
    res.header('Access-Control-Allow-Headers', 'Content-Type');
    next();
});
```

设置主页面、登录和注册界面

```js
app.get('/main.html', function (req, res) {
    res.sendFile(__dirname + '/' + 'main.html');
})
app.get('/login.html', function (req, res) {
    res.sendFile(__dirname + '/' + 'login.html');
})
app.get('/register.html', function (req, res) {
    res.sendFile(__dirname + '/' + 'register.html');
})
```

将主界面作为默认界面

```js
app.get('/', function (req, res) {
    res.sendFile(__dirname + '/' + 'main.html');
})
```

为注册和登录操作添加接口

```js
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
```

最后是开启后端，监听`8008`端口

```js
var server = app.listen(8008, function () { 
    console.log("后端启动成功！")
})
```

#### MongoDB

建立MongoDB对象

```js
var db = require('./db');
```

建立`db.js`文件，编写数据库相关操作

通过默认端口访问MongoDB

```js
var mongoClient = require('mongodb').MongoClient;
var url = 'mongodb://127.0.0.1:27017/';
```

MongoDB会在我们进行数据路操作的时候自动建立相应的数据库，我们只需要负责编写插入和查询的代码，数据库的名字是`login_project`，下面是查找和插入的代码

```js
function searchUser(whereStr, callBack) {
    mongoClient.connect(url, { useNewUrlParser: true }, function (err, db) {
        if (err) throw err;
        var dbo = db.db('login_project');
        dbo.collection('site').find(whereStr).toArray(function (err, result) {
            if (err) throw err;
            console.log('查询指定条件的数据...', result);
            callBack(result);
            db.close();
        })
    })
}

function insertUser(myobj, callBack) {
    mongoClient.connect(url, { useNewUrlParser: true }, function (err, db) {
        if (err) throw err;
        var dbo = db.db('login_project');
        dbo.collection('site').insertOne(myobj, function (err, res) {
            if (err) throw err;
            console.log('文档插入成功');
            callBack(res);
            db.close();
        })
    })
}
```

最后，允许这两个函数被外部文件调用

```js
exports.searchUser = searchUser;
exports.insertUser = insertUser;
```

### 前端

前端主要的工作是`main.html`、`register.html`和`login.html`的编写。

三个界面的公共部分是导航栏

```html
<div id="nav">
	<ul>
		<li>
			<a href="main.html">主页</a>
		</li>
		<li>
			<a href="login.html">登录</a>
		</li>
		<li>
			<a href="register.html">注册</a>
		</li>
	</ul>
</div>
```

#### main.html

`main.html`页面通过`js`通过url获得当前的用户名并给出提示

```js
var name =  getUrlParameter('name');
console.log(name);
if(name != ""){
	document.getElementById("info").innerHTML = "当前登陆的账号为：" + name;
}

function getUrlParameter(name){
  name = name.replace(/[]/,"\[").replace(/[]/,"\[").replace(/[]/,"\\\]");
  var regexS = "[\\?&]"+name+"=([^&#]*)";
  var regex = new RegExp( regexS );
  var results = regex.exec(window.parent.location.href );
  if( results == null ) return ""; 
  else {
  	return results[1];
  }
};
```

通过上面的`js`自动更改html中的信息

```html
<div class="wrapper">
  <h1 id="info"></h1>欢迎使用NJU-SE-Web系统</h1>
	<h1 id="info">请登陆！</h1>
</div>
```

#### login.html

登陆界面如下

```html
<div class="wrapper">
	<h1>欢迎登录NJU-SE-Web系统</h1>
	<div class="form-list">
		<div class="form-item">
			<span>用户名：</span>
			<input type="text" name="username" id="name" />
		</div>
		<div class="form-item">
			<span>密码：</span>
			<input type="password" name="userpwd" id="pwd" />
		</div>
    <div class="form-item">
      <canvas id="verifi-code" style='width:110px;height:25px'></canvas>
      <input id="input-code" type="text" placeholder="请输入验证码">
    </div>
		<div class="btn">
			<button onclick="submit()">登录</button>
		</div>
	</div>
</div>
```

使用js完成登陆后的页面切换和数据库查询

```js
function submit() {
  var name = $("#name").val().trim();
  var pwd = $("#pwd").val().trim(); 
  $.ajax({
    url: "http://127.0.0.1:8008/process_login",
    type: "post",
    data: {
      userName: name,
      pwd: pwd
    },
    success: function(res) {
      console.log(res);
      if (res.code == 0) {
        window.location.href = 'main.html?name=' + name;
      } else {
        alert(res.message);
      }
    },
    error: function(){
      console.info("网络出错");
      alert("网络出错，请再试一次");
    }
  })
}
```

其中，通过url将登陆用户的信息传递给`main.html`页面。

如果ajax请求成功则页面跳转，如果登陆失败则给出提示信息。

通过js代码实现验证码生成

```js
function createCode() {
  let code = "";
  var codeLength = 4;
  var selectChar = new Array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z');
  for (var i = 0; i < codeLength; i++) {
    var charIndex = Math.floor(Math.random() * 36);
    code += selectChar[charIndex];
  }
  return code;
}
```

在canvas上画出验证码

```js
function draw_canvas(code) {
  if (canvas) {
    var ctx=canvas.getContext('2d');
    ctx.clearRect(0,0,canvas.width,canvas.height);
    ctx.font="80px Verdana";
    ctx.strokeText(code,25,110);
    console.log("canvas 绘制完成")
  }
  else
  	console.log("没有找到canvas")
}
```

编写函数检查字符串是否相同，并给出提示

```js
function isequal(str,str1,alert_info){
  if(str != str1){
  	alert(alert_info);
  	return false;}
  else return true;
}
```

在`submit`函数中检查

```js
var input_code = $("#input-code").val().trim(); 
if(!isequal(code, input_code, "验证码错误")) return;
```

同时，需要在加载页面时加载这个验证码

```js
var canvas = document.getElementById('verifi-code');
var code = '';
window.onload = function () {
  code = createCode();
  draw_canvas(code);
}
```

以及支持验证码点击刷新

```js
canvas.onclick = function () {
  code = createCode();
  draw_canvas(code);
}
```

#### register.html

`register.html`和`login.html`大致相同，主要的区别是`register.html`需要对密码进行二次验证，在`submit`函数中进行检验

```js
var pwd = $("#pwd").val().trim(); 
var pwda = $("#pwda").val().trim(); 
if(!isequal(pwd, pwda, "两次输入不一致")) return;
```

如果验证通过，则向数据库中插入信息，如果ajax请求成功，则实现跳转

```js
success: function(res) {
  console.log(res);
  if (res.code == 0) {
    alert("注册成功");
    window.location.href = 'main.html?name=' + name;
  } else {
  	alert(res.message);
  }
},
```
