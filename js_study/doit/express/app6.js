var express = require('express');
var http = require('http');
var static = require('serve-static');
var path = require('path');

var bodyParser = require('body-parser');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);
//1.이렇게 쓸 수도 있고
app.use(static(path.join(__dirname, 'public'))); 
// use를 사용하는 것은 middleware를 등록하는 것임.

//2. public 이란 명시적 폴더를 쓸 수도 있음.
//app.use('/public',Sstatic(path.join(__dirname, 'public'))); 
// use를 사용하는 것은 middleware를 등록하는 것임.

app.use(bodyParser.urlencoded({extended:false}));
app.use(bodyParser.json());

app.use(function(req,res) {
	console.log('첫번째로 미들웨어 호출됨');
	
	var userAgent = req.header('User-Agent');
	var paramName = req.body.id || req.query.id;
	
	res.send('<h3> 서버에서 응답. User-Agent -> ' + userAgent + '</h3><h3>Param Name  -> ' + paramName + '</h3>');
	
});
	
var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});