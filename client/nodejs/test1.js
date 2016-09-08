const Command = require("./Command");
var commands = new Command.List([
    new Command.Simple("dblclickitem::treeWidget::second item"),
    new Command.Wait(2002),
    new Command.Simple("click::File"),
    new Command.WaitFor("die!"),
    new Command.Simple("value::die!::C:\\MYSELF\\Programming"),
    new Command.Wait(1000),
    new Command.Simple("submit::die!")
]);

require("./BasicTest.js")("6660", "127.0.0.1", commands);
