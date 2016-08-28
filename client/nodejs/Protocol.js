//const Promise = require("bluebird");
//const Emitter = require("eventemitter2");
function Protocol(client) {
    this.client = client;
    if(client.protocol) {
        client.protocol.destroy();
    }
    client.protocol = this;
    client.on("data", this.onData = this.onData.bind(this));
    //Emitter.call(this);
}
//Protocol.prototype = Object.create(Emitter.prototype);
Protocol.prototype.sendMessage = function(message) {
    
}
Protocol.prototype.onData = function(message) {
    
}
Protocol.prototype.destroy = function() {
    client.off("data", this.onData);
}

function Plaintext(client) {
    Protocol.call(this, client);
}
Plaintext.prototype = Object.create(Protocol.prototype);
Plaintext.prototype.sendMessage = function(message) {
    var begin = typeof message.objectId == "string"?message.objectId+"::":"";
    client.write(begin+message.command+"::"+message.selector+"::"+message.params);
}
Plaintext.prototype.onData = function(message) {
    var chunks = message.split("::");
    var message = {objectId: message[0], className: message[1]};
}