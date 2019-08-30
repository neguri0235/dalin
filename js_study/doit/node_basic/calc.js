
var EventEmitter = require('events').EventEmitter;
var util = require('util')


var Calc = function() {
	this.on('stop',function() {
		console.log('calc에 stop event 전달됨');
	});
};

// EventEmitter를 Calc를 상속함
util.inherits(Calc, EventEmitter);

Calc.prototype.add = function(a,b) {
	return a+b;
};

module.exports = Calc