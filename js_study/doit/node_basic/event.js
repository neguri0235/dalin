
// on -> event를 register를 하기 위해 사용
// 'exit'은 이미 정의되어 있음


process.on('exit', function() {
	console.log('--> exit event 발생함');
});


setTimeout(function () {
	console.log('-> 2초후에 실행되었음');
	process.exit();
},2000);

console.log('2초후에 실행될 것임');




//tick 이란 임의의 event를 등록하는 경우
process.on('tick', function(count) {
	console.log('tick 이벤트 발생함 ' + count);
});

setTimeout(function() {
	console.log('2초후에 실행되었음');

	// 임의의 event를 발생시킴
	process.emit('tick','2');
},2000);

