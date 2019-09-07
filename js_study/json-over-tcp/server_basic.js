		var net = require('net');

		var PORT = 18888;
		var msg = 'will you be okay?';
		var server = net.createServer( function ( client_socket ) { 

			console.log('client connected >> '  + client_socket.remoteAddress +':'+ client_socket.remotePort);
			client_socket.setNoDelay(true);
		//	client_socket.setTimeout( 4000 );
			client_socket.on('drain', function () {
				console.log('client occured drain >> write buffer is empty' );	
			});

			client_socket.on('data', function (data) {
				console.log('client received data >> '  + client_socket._peername.address +':'+ client_socket._peername.port + ' [' + data + ']' );	
				client_socket.write(msg);
			});

			client_socket.on('end', function () {
				console.log('client received end >> '  + client_socket._peername.address +':'+ client_socket._peername.port );	
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