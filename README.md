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
