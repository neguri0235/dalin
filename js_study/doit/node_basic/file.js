// file read
var fs = require('fs');
// 동기 방식
var data = fs.readFileSync('./package.json','utf-8');

console.log(data);
// 줄바꿈이 안맞음
console.dir(data);

// 비동기 방식
fs.readFile('./package.json','utf-8',function(err,data) {
	console.log(data);
  }
);


// file write

var wf = require('fs');
fs.writeFile('./output.txt','hello',function(err) {
	if(err) {
		console.log('write error');

	}else{
		console.log('write success');
	}
});

