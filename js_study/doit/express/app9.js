var express = require('express');
var http = require('http');
var static = require('serve-static');
var path = require('path');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var expressSession = require('express-session');



// app 이 express server 객체
var app = express();

app.set('port', process.env.PORT || 3000);
app.use(static(path.join(__dirname, 'public'))); 
app.use(bodyParser.urlencoded({extended:false}));
app.use(bodyParser.json());
app.use(cookieParser());
app.use(expressSession({
    secret:'my key',
    resave:true,
    saveUninitialized:true
}));


// routing 함수를 사용
var router = express.Router();


router.route('/process/prodduct').get(function(req,res) {
    console.log('/process/product 라우팅 함수 호출됨');
    
    if(req.session.user) {
        res.redirect('/public/product.html');
    }else{
        res.redirect('/public/login2.html');
    }
})

router.route('/process/setUserCookie').get(function(req,res){
    console.log('/process/setUserCookie 라우팅 함수 호출됨.');

    res.cookie('user',{
        id:'mike',
        name:'dangel',
        authorized:true
    });

    res.redirect('/process/showCookie');
});

router.route('/process/showCookie').get(function(req,res){
    console.log('/process/showCookie 라우팅 함수 호출됨.');
    res.send(req.cookies);
});
app.use('/', router);

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});