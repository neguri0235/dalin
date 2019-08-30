var output = '안녕';
var buffer1 = new Buffer(10);
var len = buffer1.write(output, 'utf8');
console.log('문자열의 길이 ' + len);
console.log('버퍼에 쓰인 문자열 ' + buffer1.toString());
console.log('버퍼 객체인지 여부 확인 ' + Buffer.isBuffer(buffer1));

var byteLen = Buffer.byteLength(buffer1);
console.log('bytelon : ' + byteLen);

var str1 = buffer1.toString('utf8',0,6);
console.log('str1 : ' + str1);


var fs = require('fs');

var infile = fs.createReadStream('./output.txt', {flasg:'r'});

infile.on('data', function(data) {
	console.log('읽어들인 데이터: ' + data)
});

infile.on('end', function() {
	console.log('읽기 종료');
});

var buffer2 = Buffer.from('Hello', 'utf8');
console.log('두번째 버퍼의 길이 : ' + Buffer.byteLength(buffer2));


var str2 = buffer2.toString('utf8', 0, Buffer.byteLength(buffer2));
console.log('str2 : ' + str2);