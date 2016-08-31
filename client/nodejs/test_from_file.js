const Arguments = require("./SimpleArgv");
const ARGS = new Arguments();
ARGS.defaults.port = "9666";
ARGS.defaults.ip = "127.0.0.1";

if (typeof ARGS.arg_commands != "string")
    throw new Error("Argument commands=\"path/file.js\" required. Provide valid file name.");

require("./ReloadTest.js")(ARGS.arg_port, ARGS.arg_ip, ARGS.arg_commands);
