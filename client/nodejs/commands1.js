[
    new Command.Simple("encoding utf-8"),
    new Command.Simple("dblclickitem::#treeWidget::second item"),
    new Command.Wait(2002),
    new Command.Simple("value::QLineEdit::hovno"),
    //new Command.WaitFor("\"Action 1\""),
    new Command.Simple("click::\"Pičo vokno\""),
    //new Command.WaitFor("QDialog"),
    //new Command.Simple("click::File"),
    //new Command.WaitFor("die!"),
    //new Command.Simple("value::die!::C:\\MYSELF\\Programming"),
    //new Command.Wait(1000),
    //new Command.Simple("submit::die!")
]