var connect = require('net');
var Promise = require('bluebird');
const CommandLoader = require("./CommandLoader");
// 
function connectForever(port, ip, commands) {
    if(typeof commands=="string")
        commands = new CommandLoader(commands);
    //var getCommands = commands.getCommands();

    var client = connect.connect(port, ip);
    var old_write = client.write;
    client.write = function(data) {
        console.log("SENT: "+data.replace("\n", "\\n"));
        old_write.apply(client, arguments);
    }

    client.on('data', function (data) {
        console.log('RECEIVED: ' + data);
    }).on('connect', function () {
        console.log('Connection Success!\n\n');
        commands.getCommands().then(function(commands) {
            commands.execute(client)
              .then(function () {
                  console.log("All commands done!");
              })
              .catch(function (error) {
                  console.log("Error while executing commands: " + error+"\n",error.stack);
              })
        });
    }).on('end', function () {
        console.log('Disconnected.');
        connectForever(port, ip, commands);
    }).on('error', function (error) {
        if(error.code!="ECONNREFUSED") {
            if (error.code == "ECONNRESET")
                console.log("Disconnected.");
            else {
                console.log("ERROR: " + JSON.stringify(error));
                console.log("    connecting to " + ip + ":" + port);
            }
        }
        connectForever(port, ip, commands);
    });
}
//connectForever("9666", "127.0.0.1", commands);
module.exports = connectForever;