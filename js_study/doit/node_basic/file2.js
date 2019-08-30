
var fs = require('fs');

fs.open('./output,txt','w',function(err,fd) {
	if(err) {
		console.log('file open error');
		console.dir(err);
		return;
	}
	
	var buf = new Buffer('Hello\n');
	fs.write(fd, buf,0, buf.length, null, function(err, written, buffer) {
		if(err) {
			console.log('file write error');
			console.dir(err);
			return;
		}
		console.log('file write complete');

		fs.close(fd, function() {
			console.log('file close complete');
		});
	});
});
