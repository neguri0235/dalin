// image file을 전송하는 경우

var http = require('http');
var fs   = require('fs');

var server = http.createServer();

var host = '192.168.219.111'; //loca
var port = 3000;

// 50000 은 backlog 로서 동시에 접속할 수 있는 숫자
server.listen(port,host, 50000, function() {
	console.log('웹서버가 실행되었습니다 : ' + host + ':' + port );
});

// event 생성
server.on('connection',function(socket) { 
	console.log('client socket 접속');
});

// req는 요청 객체
// res는 응답 객체
server.on('request', function(req, res) {
	console.log('client 요청이 들어왔습니다');
	//console.dir(req); // 로그가 너무 많이 나와서 주석 처리함.
	var filename = './icon.png';
	fs.readFile(filename, function(err, data) {
		res.writeHead(200, {"Content-Type":"image/png"});
		res.write(data);
		res.end();		
	});

});