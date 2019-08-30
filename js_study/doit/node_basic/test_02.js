console.log('argv : ' + process.argv.length);
console.dir(process.argv)

process.argv.forEach(function(item, index) {
	console.log(index + ':' + item);
});