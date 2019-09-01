var express = require('express');

var http = require('http');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);

app.use(function(req,res,next) {
	console.log('첫번째로 미들웨어 호출됨');
	
	req.user = 'mike';

	next(); // next를 만나는 순간 현재 미들웨어를 떠나고 , 그다음 미들웨어가 받아서 처리

});

app.use(function(req,res, next) {
	console.log('두번째 미들웨어 호출됨');
	res.writeHead(200,{"Content-Type":"Text/html;charset=utf8"});
	res.end('<h1>서버에서 응답함: ' + req.user +  '</h1>' );	
});

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});