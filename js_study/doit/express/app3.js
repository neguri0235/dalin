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
	//send를 사용하면 좀더 간단하게 응답을 보낼 수 있음
	
	//res.send('<h1>서버에서 응답함: ' + req.user +  '</h1>' );
	
	
	// 아니면 이렇게 객체를 직접 보낼 수도 있음
	var person = {nane:'소녀시대', age:20}
	//res.send(person);
	
	// 혹은 string으로 변경해서 보낼 수도 있음
	var perStr = JSON.stringify(person);
	res.send(perStr);
	
});

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});