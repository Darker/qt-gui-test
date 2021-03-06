var connect = require('net');
var Promise = require('bluebird');
// 
function connectForever(port, ip, commands) {
    var client = connect.connect(port, ip);

    client.on('data', function (data) {
        // Log the response from the HTTP server.
        console.log('RECEIVED: ' + data);
    }).on('connect', function () {
        console.log('Connection Success!\n\n');
        commands.execute(client)
          .then(function () {
              console.log("All commands done!");
          })
          .catch(function (error) {
              console.log("Error while executing commands: " + error);
          })
    }).on('end', function () {
        console.log('Disconnected');
        connectForever(port, ip, commands);
    }).on('error', function (error) {
        if(error.code!="ECONNREFUSED") {
            console.log("ERROR: " + JSON.stringify(error));
        }
        connectForever(port, ip, commands);
    });
}
//connectForever("9666", "127.0.0.1", commands);
module.exports = connectForever;