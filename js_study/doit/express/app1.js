var express = require('express');

var http = require('http');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);

app.use(function(req,res,next) {
	console.log('첫번째로 미들웨어 호출됨');
	res.writeHead(200,{"Content-Type":"Text/html;charset=utf8"});
	res.end('<h1>서버에서 응답함</h1>');
});

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});