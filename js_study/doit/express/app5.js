var express = require('express');

var http = require('http');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);

app.use(function(req,res,next) {
	console.log('첫번째로 미들웨어 호출됨');
	
	// server에서 client에서 보내온 정보를 추출
	// reqeust의 header 정보에서 user agent를 추출
	
	var userAgent = req.header('User-Agent');
	var paramName = req.query.name;  // 여기서 name은 임의의 값임
	
	res.send('<h3>서버에서 응답. User-Agent: ' + userAgent + '</h3><h3>서버에서 응답. name: ' + paramName + '</h3>');
});
	
var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});