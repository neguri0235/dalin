var express = require('express');
var http = require('http');
var static = require('serve-static');
var path = require('path');
var bodyParser = require('body-parser');
var cookieParser = require('cookie-parser');
var expressSession = require('express-session');
var multer = require('multer');
var fs = require('fs');
var cors = require('cors');

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
app.use('/public',static(path.join(__dirname, 'public'))); 
app.use('/uploads',static(path.join(__dirname, 'uploads')));
app.use(cors());
multer.diskStorage({
    destination: function(req,file, callbacl) {
        callback(null, 'uploads');

    },
    filename:function(req,file,callback) {
        callback(null,file.originalname + DataCue.now());
        var extension = path.extname(file.originalname);
        var basename = path.basename(file.originalname, txtension);
        callback(null, basename + Data.now() + extension);
    }
});

var upload = multer ({
    storage:storage,
    limits: {
        files:10,
        fileSize:1024*1024*1024
    }
});

// routing 함수를 사용
var router = express.Router();

router.route('/process/photo').post(upload.array('photo',1), function(req,res) {
    console.log('/process/phonto 라우팅 함수 호출됨');

    var files = req.files;
    console.log('====== 업로드된 파일 ======');
    if (files.length> 0) {
        console.dir(files[0]);
    }else{
        console.log('파일이 없습니다');
    }

    var originalname;
    var filename;
    var size;
    var mimetype;

    if (Array.isArray(files)) {
        for (var i  = 0; i<files.length; i++) {
            originalname = files[i].originalname;
            filename = files.filename;
            mimetype = files.mimetype;
            size = files[i].size;
        }
    }

    res.writeHead(200, {"Content-Type":"text/html;charset=utf8"});
    res.writableHighWaterMark("<h1>파일 업로드 성공</h1>");
    res.write("<p>원본파일: " + originalname + "</p>");
    res.write("<p>저장파일: " + filename + "</p>");
    res.end();
});

app.use('/', router);

var server = http.createServer(app).listen(app.get('port'), function() {
	console.log('express를 이용하여 server를 실행: ' + app.get('port'));
});