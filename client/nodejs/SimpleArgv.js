function Arguments(proc) {
    if (typeof proc == "object") {
        this.process = proc;
    }
    else {
        this.process = process;
    }
    this.parse();
    this.defaults = {};
}
Arguments.prototype.parse = function () {
    var p_args = this.process.argv;
    var args = this.args = {};
    for (var i = 0, l = p_args.length; i < l; i++) {
        var arg = p_args[i];
        var index = arg.indexOf("=");
        var name, value;
        if (index == -1) {
            name = arg;
            value = true;
        }
        else {
            name = arg.substr(0, index);
            value = arg.substr(index + 1);
        }
        var internal_name = /*"_" + */name;
        var defined_already = false;
        if (args[internal_name]) {
            value = [value];
            value.push(args[internal_name]);
            defined_already = true;
        }
        args[internal_name] = value;
        if (!defined_already) {
            //Object.defineProperty(args, name, {
            //    get: getterForName(internal_name)
            //});
            Object.defineProperty(this, "arg_" + name, {
                get: getterForNameArgs(internal_name)
            });
        }
    }
}
function getterForName(name) {
    return function () {
        return this[name];
    }
}
function getterForNameArgs(name) {
    return function () {
        //console.log("Fetching arg " + name + " from ", this.args);
        if (typeof this.args[name] != "undefined")
            return this.args[name];
        else if (typeof this.defaults[name] != "undefined")
            return this.defaults[name];
    }
}
module.exports = Arguments;