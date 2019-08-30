var express = require('express');

var http = require('http');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});