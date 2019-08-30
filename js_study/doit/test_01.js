console.log('Hello');

var person = {
	name:'jaehoc',
	age:42
};

console.log('json object %j',person);

console.dir(person)

console.time('time')
var result = 0;
for (var i = 0; i<10000; i++) {
	result +=i;
}

console.timeEnd('time');
console.log('%s',__filename);
console.log('%s',__dirname);
