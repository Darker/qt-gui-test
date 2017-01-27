var Promise = require('bluebird');
const Command = require("./Command");
const fs = require("fs");
fs.statPromise = Promise.promisify(fs.stat);
fs.readFilePromise = Promise.promisify(fs.readFile);
fs.writeFilePromise = Promise.promisify(fs.writeFile);

function CommandLoader(file) {
    this.lastUpdate = 0;
    this.path = file;
    this.cache = [];
}
CommandLoader.prototype.getCommands = function() {
    return fs.statPromise(this.path)
      .then((stat)=>{
          if(!stat.isFile()) {
              throw new Error("File "+this.path+" does not exist or is not a file!");
          }
          var time = this.lastUpdate;
          var mtime = stat.mtime.getTime();
          console.log("Getting commands");
          if(time < mtime) {
              console.log("  ... from disk.");
              return this.loadCommands();
          }
          else {
              console.log("  ... from cache.");
              return this.cache;
          }
      })
      .catch(function(error) {
           console.log("Error in commands: "+error);
           return this.cache;
      }.bind(this));
}
CommandLoader.prototype.loadCommands = function() {
    return fs.readFilePromise(this.path)
      .then((data) => {
           this.lastUpdate = new Date().getTime();
           console.log("(function() {return (\n"+data+"\n);})()");
           var commands = eval("(function() {return ("+data+");})()");
           if(!(commands instanceof Array))
               throw new error("Provide file with an array of commands!");
           return this.cache = new Command.List(commands);
      });
}
module.exports = CommandLoader;

