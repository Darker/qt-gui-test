var connect = require('net');
var Promise = require('bluebird');
const Command = require("./Command");

console.log('Starting to connect...');
var commands = new Command.List([
    new Command.Simple("dblclickitem::treeWidget::second item"),
    new Command.Wait(2002),
    new Command.Simple("click::File"),
    new Command.WaitFor("die!"),
    new Command.Simple("value::die!::C:\\MYSELF\\Programming"),
    new Command.Wait(1000),
    new Command.Simple("submit::die!")
]);
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
        console.log("ERROR: " + error);
        connectForever(port, ip, commands);
    });
}
connectForever("9666", "127.0.0.1", commands);
