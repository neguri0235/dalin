var http = require('http');

var options = {
	host : "127.0.0.1",
	port : 8000,
	path : "/"
};

var req = http.request(options, (res) => {
	var data = "request from client ";
	res.on('data', (chunk) => {
		data += chunk;
	});
	
	res.on('end', () => {
		console.log(data);
	});
	
});

req.end();