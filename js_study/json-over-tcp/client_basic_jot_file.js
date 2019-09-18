var jot = require('json-over-tcp');

    var fs = require('fs');



    var HOST = '127.0.0.1';

    var PORT = 34271;



    var socket  = new jot.Socket();

    var msg = { req : 'file' , filename  : 'test.bmp' };



    socket.setNoDelay(true);



    socket.connect(PORT, HOST, function() {



        console.log('client connected to : ' + HOST + ':' + PORT );

        

        socket.setTimeout( 1000 );

        

        socket.on('drain', function () {

            console.log('client occured drain >> write buffer is empty' );	

        })

        

        socket.on('data', function (data) {

            console.log('client received data >> [filename : %s, size : %d]' , data.filename, data.data.length );	

            

            fs.writeFile( './' + data.filename , new Buffer( data.data ), function (err) {

                if (err) console.log(err);

                socket.end();

            });

        })



        socket.on('error', function (error) {

            console.error('client occured error >> ', error);

        });

        

        socket.on('timeout', function () {

            console.log('client occured timeout >> ' );	

            socket.end();

        });



        socket.on('end', function () {

            console.log('client received end >> ');	

        });

        

        socket.on('close', function (error) {

            console.log('client closed >>' );	

            if (error) {

                console.log('The socket had a transmission error.');

            }		

        });

        

        socket.write(msg);

        console.log( 'client send data [%j] ', msg );

        

    });