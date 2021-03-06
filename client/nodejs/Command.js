var Promise = require('bluebird');

function Command(client) {
    this.client = client;
    // Contains array of events that were assigned but not deleted
    // the structure is:
    /*
     [ [name_of_event, callback_of_event], ...]
    **/
    this.activeEvents = [];
    // Array of callback to cancel/cleanup whatever this command
    // created.
}
(()=>{
    let ID = 0;
    Object.defineProperty(Command, "MESSAGE_ID", {
        get: function() {return ++ID;},
        enumerable: false,
        configurable: false
    });
})();
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
        // Ensure that resolving or rejecting clears any events
        var callbackInfo = {resolved: false};
        resolve = this.clearEvents.bind(this, client, resolve, callbackInfo);
        reject  = this.clearEvents.bind(this, client, reject, callbackInfo);
        // Ensure that commend rejects if client disconnects
        this.event(client, "end", ()=>{reject(new Error("Disconnected."));});
        this.event(client, "error", (error)=>{reject(new Error("Client error: "+error));});
            
        args.unshift(resolve, reject);
        this.resolver.apply(this, args);
    });
}
/**
 * Sends a message and waits for reply from the server. 
 * resolves with string reply, rejects on error or timeout.
**/
Command.prototype.messageWithReply = function(message, client, timeout) {
    return new Promise((resolve, reject)=>{
        var id = Command.MESSAGE_ID;
        var timeoutId = 0;
        var timedOut = false;
        this.event(client, 'data', (data) => {
            if(timedOut) {
                console.error("Warning: received event after timed out, this means event listener wasn't removed properly.");
                return;
            }
            data = data + "";
           
            // there is a comma at the end of the transaction ID
            var idFragment = data.substr(0, data.indexOf(","));
            var number = parseInt(idFragment, 10);
            if (number == id)  {
                data = data.substr(data.indexOf(",")+1);
                while(data.endsWith("\n") || data.endsWith("\r"))
                    data = data.substr(0, data.length-1);
                console.log("Resolving with: ",data);
                resolve(data);
            } 
        });
        try {
            client.write(id+","+message+"\n");
        }
        catch (error) {
            reject(error);
        }
        if(typeof timeout=="number" && timeout>0) {
            timeoutId = setTimeout(()=>{timedOut=true; reject(new Error("timeout"))}, timeout);
        }
    });
}

/**
 * Adds event listener which is guaranteed to be removed before the
 * command resolves or rejects 
**/
Command.prototype.event = function(client, event, callback, isOnce) {
    if(isOnce === true) 
        client.once(event, callback);
    else
        client.on(event, callback);
    this.activeEvents.push([client, event, callback]);
}
/**
 * Removes all lingering event listeners from client. Callback is mostly used so that
 * this method can be passed as reject/resolve callback. Actual reject/resolve is then
 * passed as second argument using bind()
 * 
 * The last argument, callback info, is used to pass info to calling callback.
 * Primary use: {resolved: false} used to prevent multiple calls to resolve/reject
**/
Command.prototype.clearEvents = function(client, callback, callbackInfo) {
    for(var i=0, l=this.activeEvents.length; i<l; ++i) {
        if(this.activeEvents[i][0]==client) {
            //console.log("Removed listener ", this.activeEvents[i][1]);
        }   
        else {
            console.log("Removed UNKNOWN! listener ", this.activeEvents[i][1]);
        } 
        this.activeEvents[i][0].removeListener(this.activeEvents[i][1], this.activeEvents[i][2]);                                                                           
    }
    //console.log("All listeners removed.");
    this.activeEvents.length = 0;
    // Calling the underlying callback
    if(typeof callback=="function") {
        var validCallbackInfo = typeof callbackInfo=="object" && callbackInfo.hasOwnProperty("resolved");
        // Prevents multiple calls
        if(validCallbackInfo) {
            if(callbackInfo.resolved===true)
                return;
            else
                callbackInfo.resolved = true;
        }
        // pass all but first two or three arguments
        var args = [];
        args.push.apply(args, arguments);
        args.splice(0, validCallbackInfo?3:2);
        return callback.apply(null, args);
    }
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
    reject(new Error("Command not implemented!"));
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
    var id = Command.MESSAGE_ID;
    this.event(client, 'data', (data) => {
        data = data + "";
        // there is a comma at the end of the transaction ID
        data = data.substr(0, data.indexOf(","));
        var number = parseInt(data, 10);
        if (number == id)
            resolve();
    });
    try {
        client.write(id+",wait::" + this.selector + "\n");
    }
    catch (error) {
        reject(error);
    }
    if(this.commandAfter instanceof Command) {
        console.log("During wait: "+this.commandAfter);
        this.commandAfter.executeIgnore(client);
    }
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
        console.log("LIST: Running command #" + index + " " + commands[index]);
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
/**
/* Takes two lists of commands, a single command and a value.
 * if given commands return value equals given value, executes "true commands", else executes "false commands"                                                        
**/
function CommandIfEquals(command, value, iftrue, iffalse) {
    this.command = command;
    this.refValue = value;
    this.truecommands = iftrue instanceof Array?iftrue:[];
    this.falsecommands = iffalse instanceof Array?iffalse:[];
    Command.call(this);
}
CommandIfEquals.prototype = Object.create(Command.prototype);
Command.IfEquals = CommandIfEquals;
CommandIfEquals.prototype.truecommands = null;
CommandIfEquals.prototype.falsecommands = null;
CommandIfEquals.prototype.resolver = function (resolve, reject, client) {
    this.messageWithReply(this.command, client)
      .then((value)=>{
          var commands;
          //console.log("<"+value+">");
          console.log(value+" == "+this.refValue+" => "+(value==this.refValue));
          if(value==this.refValue) {
              commands = this.truecommands;
          }
          else {
              commands = this.falsecommands;
          }
          console.log(commands);
          new CommandList(commands, client).execute(client)
              .then(function(value) {
                   resolve();
              })
              .catch(function(error) {
                   reject(error);
              });
      })
      .catch(function(error) {
           reject(error);
      });
}
CommandIfEquals.prototype.toString = function() {
    return "if ("+this.command+") == \""+this.refValue+"\"";
}
CommandIfEquals.prototype.then = function(commands) {
    if(commands instanceof Command)
        this.truecommands.push(commands);
    else if(commands instanceof Array) {
        this.truecommands.push.apply(this.truecommands, commands);
    }
}
CommandIfEquals.prototype.else = function(commands) {
    if(commands instanceof Command)
        this.falsecommands.push(commands);
    else if(commands instanceof Array) {
        this.falsecommands.push.apply(this.truecommands, commands);
    }
}
// Non-server commands
function CommandPrint(message) {
    Command.call(this);
    this.message = message;
}
CommandPrint.prototype = Object.create(Command.prototype);
Command.Print = CommandPrint;
CommandPrint.prototype.resolver = function(resolve, reject) {
    console.log(this.message);
    resolve();
}

module.exports = Command;
