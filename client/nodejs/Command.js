var Promise = require('bluebird');

function Command(client) {
    this.client = client;
}
Command.prototype.execute = function (client) {
    if (client == null)
        client = this.client;
    var args = [];
    args.push.apply(args, arguments);
    args[0] = client;
    // must return a promise
    return new Promise((resolve, reject) => {
        if (client.destroyed)
            reject(new Error("The client was disconnected, commands cannot be executed!"));
        if (client == null)
            reject(new Error("The client was not set! Cannot run commands without client!"));
        args.unshift(resolve, reject);
        this.resolver.apply(this, args);
    });
}
// Executes instantly and returns null
Command.prototype.executeIgnore = function(client) {
    if (client == null)
        client = this.client;
    var args = [];
    args.push.apply(args, arguments);
    args[0] = client;
    args.unshift(()=>{}, ()=>{});
    this.resolver.apply(this, args);
}
Command.prototype.resolver = function (resolve, reject) {
    resolve();
    /*return (resolve, reject) => {
        resolve();
    };*/
}
Command.prototype.toString = function() {
    return "Generic command.";
}
Command.prototype.client = null;

function SimpleCommand(text, client) {
    this.text = text;
    Command.call(this, client);
}
SimpleCommand.prototype = Object.create(Command.prototype);
Command.Simple = SimpleCommand;
SimpleCommand.prototype.resolver = function (resolve, reject, client) {
    try {
        client.write(this.text + "\n");
        //console.log("SENT: " + this.text);
    }
    catch (error) {
        reject(error);
    }
    resolve();
}
SimpleCommand.prototype.toString = function() {
    return "Simple: \""+this.text+"\"";
}

function WaitCommand(timeout, client) {
    this.delay = timeout;
    Command.call(this, client);
}
WaitCommand.prototype = Object.create(Command.prototype);
Command.Wait = WaitCommand;
WaitCommand.prototype.resolver = function (resolve, reject) {
    console.log("WAIT: " + this.delay + "ms");
    setTimeout(function () { console.log("WAIT: done");resolve(); }, this.delay);
}
WaitCommand.prototype.toString = function() {
    return "Wait: " + this.delay + "ms";
}

function WaitFor(selector, client) {
    this.selector = selector;
    this.commandAfter = null;
    Command.call(this, client);
}
WaitFor.prototype = Object.create(Command.prototype);
Command.WaitFor = WaitFor;
WaitFor.prototype.resolver = function (resolve, reject, client) {
    //console.log("WAIT FOR: " + this.selector);
    var id = WaitFor.ID++;
    client.on('data', (data) => {
        data = data + "";
        var number = parseInt(data, 10);
        if (number == id)
            resolve();
    });
    try {
        client.write("wait::" + this.selector + "::" + id + "\n");
    }
    catch (error) {
        reject(error);
    }
    if(this.commandAfter)
      this.commandAfter.executeIgnore(client);
}
WaitFor.prototype.after = function(commandAfterWaitStarts) {
    this.commandAfter = commandAfterWaitStarts;
    return this;
}
WaitFor.prototype.toString = function() {
    return "Wait for selector: "+this.selector+"";
}
WaitFor.ID = 0;

function CommandList(commands, client) {
    this.commands = commands;
    Command.call(this, client);
}
CommandList.prototype = Object.create(Command.prototype);
Command.List = CommandList;
CommandList.prototype.resolver = function (resolve, reject, client) {
    var index = 0;
    var commands = this.commands;
    if (commands.length == 0)
        resolve();
    function invokeNext() {
        console.log("LIST: Running command #" + index);
        return commands[index].execute(client)
          .then(function () {
              console.log("LIST: Finished command #" + index+"\n");
              if (++index < commands.length) {
                  return invokeNext();
              }
              else {
                  resolve();
              }
          })
          .catch(function (error) {
              reject(error);
          });
    }
    return invokeNext();
}
CommandList.prototype.toString = function() {
    return "Commands: "+this.commands.map((a)=>{return x.constructor.name;}).join(", ");
}

module.exports = Command;
