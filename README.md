# plant-partner-nodejs-mongodb-cxy
this project is prepare for boya primary school's education project, this part is my part of the project, and before I just to do the hardware for  auto-water and web control, as the principal of this project, this times I do the backend software.
## something before the work
I was a rookie in the backend software, and in this process I get the help form many githubers, and if there are something wrong and unfriendly, just tell me and then I will take it on the way.
## the tools and ways in this project
- nodejs
- ubuntu18.04
- mongodb
- html and js
- ajax jq-ajax

## others

## HOW TO RUN
1. mongod --dbpath ./data/ --logpath ./log/mongod.log --fork  
启动MongoDB服务器
2. node backend.js
运行js代码，开始响应前段数据请求

目前该项目能够进一步前进，下一步我们计划配合HTML和Vue进行打包APP，今晚进行HTML发送ajax请求的测试，目前是在Ubuntu18.04系统下操作的。
今晚实现了浇水的通信，但是在写入数据库方面还存在问题
具体报错如下
---
后端启动成功！
查询指定条件的数据... []
_http_outgoing.js:561
    throw new ERR_HTTP_HEADERS_SENT('set');
    ^

Error [ERR_HTTP_HEADERS_SENT]: Cannot set headers after they are sent to the client
    at ServerResponse.setHeader (_http_outgoing.js:561:11)
    at ServerResponse.header (/home/cxy/node_modules/express/lib/response.js:771:10)
    at ServerResponse.send (/home/cxy/node_modules/express/lib/response.js:170:12)
    at ServerResponse.json (/home/cxy/node_modules/express/lib/response.js:267:15)
    at /home/cxy/node-mongodb/backend.js:88:21
    at /home/cxy/node-mongodb/db.js:27:13
    at /home/cxy/node_modules/mongodb/lib/utils.js:532:9
    at /home/cxy/node_modules/mongodb/lib/cursor/abstract_cursor.js:243:32
    at /home/cxy/node_modules/mongodb/lib/cursor/abstract_cursor.js:477:68
    at /home/cxy/node_modules/mongodb/lib/utils.js:532:9 {
  code: 'ERR_HTTP_HEADERS_SENT'
}
---
希望明天能解决

---
测试的时候可以查看一下数据库的信息，看看有没有写进去和对应的标签
浇水时间的变量应该加上登陆的个人信息
#### 查看数据库
    db.stats();
    - 数据库表
    db.sirius.stats();
    - 其他常用的命令
    db.adminCommand(nameOrDocument)// 切换到'admin'数据库,并且运行命令
db.AddUser(username,password[, readOnly=false])  //添加用户  
db.auth(usrename,password)     // 设置数据库连接验证  
db.cloneDataBase(fromhost)     // 从目标服务器克隆一个数据库  
db.commandHelp(name)           // returns the help for the command  
db.copyDatabase(fromdb,todb,fromhost)  // 复制数据库fromdb---源数据库名称，todb---目标数据库名称，fromhost---源数据库服务器地址  
db.createCollection(name,{size:3333,capped:333,max:88888})  // 创建一个数据集，相当于一个表  
db.createView(name, viewOn, [ { $operator: {...}}, ... ], { viewOptions } ) // 创建视图
db.createUser(userDocument)    // 创建用户
db.currentOp()                 // 取消当前库的当前操作  
db.dropDataBase()              // 删除当前数据库  
db.eval(func,args)             // (已过时) run code server-side  
db.fsyncLock()                 // 将数据保存到硬盘并且锁定服务器备份
db.fsyncUnlock() unlocks server following a db.fsyncLock()
db.getCollection(cname)        // 取得一个数据集合，同用法：db['cname'] or db.cname
db.getCollenctionNames()       // 取得所有数据集合的名称列表  
db.getLastError()              // 返回最后一个错误的提示消息  
db.getLastErrorObj()           // 返回最后一个错误的对象  
db.getLogComponents()
db.getMongo()                  // 取得当前服务器的连接对象get the server  
db.getMondo().setSlaveOk()     // allow this connection to read from then nonmaster membr of a replica pair  
db.getName()                   // 返回当操作数据库的名称  
db.getPrevError()              // 返回上一个错误对象  
db.getProfilingLevel()         // 获取profile level  
db.getReplicationInfo()        // 获得重复的数据  
db.getSisterDB(name)           // get the db at the same server as this onew  
db.killOp()                    // 停止（杀死）在当前库的当前操作 
db.listCommands()              // lists all the db commands
db.loadServerScripts()         // loads all the scripts in db.system.js
db.logout()
db.printCollectionStats()      // 返回当前库的数据集状态  
db.printReplicationInfo()      // 打印主数据库的复制状态信息  
db.printSlaveReplicationInfo() // 打印从数据库的复制状态信息  
db.printShardingStatus()       // 返回当前数据库是否为共享数据库  
db.removeUser(username)        // 删除用户  
db.repairDatabase()            // 修复当前数据库  
db.resetError()  
db.runCommand(cmdObj)          // run a database command. if cmdObj is a string, turns it into {cmdObj:1}  
db.runCommand(cmdObj)          // run a database command.  if cmdObj is a string, turns it into { cmdObj : 1 }
db.serverStatus()
db.setLogLevel(level, <component>)
db.setProfilingLevel(level, <slowms>)    // 设置profile level 0=off,1=slow,2=all 
db.setWriteConcern( <write concern doc> ) // sets the write concern for writes to the db
db.unsetWriteConcern( <write concern doc> ) // unsets the write concern for writes to the db
db.setVerboseShell(flag)       // display extra information in shell output
db.shutdownServer()            // 关闭当前服务程序  
db.stats()                     // 返回当前数据库的状态信息
db.version()                   // 返回当前程序的版本信息
    
9-18勿忘国耻
    近期操作的主要内容是利用硬件写好的板块，把内容写进后端数据库进行操作，同时利用http请求获得浇水命令

    
## 后面部分添加后续农业模块的初步代码
    包括一些电控相关的源码，服务器相关代码未开源
    具体有SHT30的传感器读取，开关电磁阀控制，灯带控制，步进电机控制，深度优化未开源
