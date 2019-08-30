/*
function func(callback) {
	callback("callback!!");
}


func ( (param) => {
	console.log(param);
});
*/

function func(callbacl) {
	process.nextTick(callback, "callback!!");
}

try {
	func((param) => {
		a.a = 0;
		});
}catch(e) {
	console.log("exception");
}