//const Promise = require("bluebird");
function Message(client) {
    this.client = client;
}
Message.prototype.objectId = null;
Message.prototype.selector = "";
Message.prototype.client = null;
Message.prototype.reply = function (message) {
    message.objectId = this.objectId;
    client.protocol.sendMessage(message);
}