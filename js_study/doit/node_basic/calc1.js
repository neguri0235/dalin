var Calc = require('./calc');

var calc1  = new Calc();

calc1.emit('stop');

console.log('Calc에 stop 이벤트 전달함');