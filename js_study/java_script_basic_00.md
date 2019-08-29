
* 객체
``` javascript
var person = {}; // 객체 생성

person['name'] = 'jaehoc';  // 속성을 부여
person['age'] = 42;

console.log('name: ' + person.name); //속성의 출력
console.log('age: ' + person.age);
```

* 함수 

자바 스크립트의 파라미터 타입과 반환되는 값의 타입이 없음

``` javascript
function add(a,b) { ...}
var add = function(a,b) {...} // 익명 함수
```


``` javascript
function add(a,b,callback) { var result =  a+b; callback(result);}

add(10,20, function (result) { console.log(result);});
```

callback 함수의 다른 예
``` javascript
function add(a,b, callback) {
    var result = a +b;
    callback(result);
    
    var history = function (){
        return a + ' + ' + b + '=' + result;
    };
    return history;
}


var add_history = add(20, 40, function (result) {
    console.log(result);
});


console.log(typeof(add_history)); // add_history의 자료형은 function
```

* closure  
내부 함수에서 외부 함수의 변수를 접근 가능할 때  
``` javascript
function add(a,b, callback) {
    var result = a +b;
    callback(result);
    var count = 0;
    var history = function (){
        count += 1;
        return count + ' : ' + a + ' + ' + b + '=' + result;
    };
    return history;
}


var add_history = add(20, 40, function (result) {
    console.log(result);
});


console.log(typeof(add_history)); // add_history의 자료형은 function
```


* 프로토타입 객체  
객체의 원형을 프로토타입이라고 하고 ,이 프로토타입이 클래스의 역할을 담당,

``` javascript
// 객체를 생성하는 경우 이렇게 생성할 수도 있지만
var person1 = { name:'jaehoc', age:42};
var person2 = { name:'jaehoc', age:42};

// 이렇게 만들수도 있음
function Person (name, age) {
    this.name = name;
    this.age = age;
}

// 그리고 함수를 추가할 수도 있음.
Person.prototype.walk = function(speed) {
    console.log(speed + '속도로 걸어갑니다.');
}

var person3 = new Person('jaehoc',42);
person3.walk(10);
```