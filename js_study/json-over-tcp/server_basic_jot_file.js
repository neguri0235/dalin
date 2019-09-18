var jot = require('json-over-tcp');

var fs = require('fs');

    

var PORT = 34271;

var msg = { ack : 'file' , filename : 'test_ack.bmp' , data : null };

    

var server = jot.createServer();



server.on('connection', function ( client_socket ) { 



    console.log('client connected >> '  + client_socket.remoteAddress +':'+ client_socket.remotePort);

    client_socket.setNoDelay(true);

//	client_socket.setTimeout( 4000 );

    

    client_socket.on('drain', function () {

        console.log('client occured drain >> write buffer is empty' );	

    });



    client_socket.on('data', function (req_data) {

        console.log('client received data >> %s:%s [%j]', client_socket.remoteAddress, client_socket.remotePort , req_data );

        if( req_data.req === 'file' ){

            fs.readFile( './' + req_data.filename, function (err,data) {

                if (err) {

                return console.log(err);

                }

                console.log('readed file data %s:%d', req_data.filename, data.length );

                msg.data = data;

                client_socket.write(msg);

            });			

        }

        

    });



    client_socket.on('end', function () {

        console.log('client received end >> ' );	

    });

    

    client_socket.on('error', function (error) {

        console.error('client occured error >> ', error);

    });

    

    client_socket.on('timeout', function () {

        console.log('client occured timeout >> ' );	

    });



    client_socket.on('close', function (error) {

        console.log('client closed >>' );	

        if (error) {

            console.log('The socket had a transmission error.');

        }		

    });

    

});



		server.listen(PORT, function() {

			address = server.address();

			console.log("server listening on %j", PORT, address);

		});