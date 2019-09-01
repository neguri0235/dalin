var express = require('express');

var http = require('http');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);

app.use(function(req,res,next) {
	console.log('첫번째로 미들웨어 호출됨');
	
	// 다른 웹사이트로 리다이렉트
	res.redirect('http://google.com');
});
	
var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});