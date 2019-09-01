var express = require('express');
var http = require('http');
var static = require('serve-static');
var path = require('path');

var bodyParser = require('body-parser');

// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);
app.use('/public',static(path.join(__dirname, 'public'))); 

app.use(bodyParser.urlencoded({extended:false}));
app.use(bodyParser.json());

// routing 함수를 사용
var router = express.Router();
router.route('/process/login').post(function(req,res) {
    console.log('/process/login 라우팅 함수에서 받음. ');
    var parmId = req.body.id || req.query.id;
    var paramPassword = req.body.password || req.query.password;

    res.writeHead(200, {"Content-Type":"text/html;charset=utf8"});
    res.write("<h1>서버에서 응답</h1>");
    res.write("<div><p>" + paramId + "</p></div>");
    res.write("<div><p>" + paramPassword + "</p></div>");
    res.end();
});
app.use('/', router);

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});