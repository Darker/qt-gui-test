[
    new Command.Simple("encoding utf-8"),
    new Command.WaitFor("QLineEdit"),
    new Command.Simple("dblclickitem::#treeWidget::second item"),
    new Command.Wait(100),
    new Command.IfEquals("gettext::QAction", "Such menu")
        .then([new Command.Print("Equals!")]),
        .else([new Command.Print("Does not equal!")])         
//     new Command.Simple("selectitems::#tableWidget::B1,C1,A1"),
//     new Command.Wait(2002),
//     new Command.Simple("selectitems::#tableWidget::C1,B1,A1"),
//     new Command.Wait(2002),
//     new Command.Simple("selectitems::#tableWidget::A1,C1"),
//     new Command.Wait(2002),
//     new Command.Simple("selectitems::#tableWidget::B1,C1,A1"),
    //new Command.Simple("value::QLineEdit::hovno"),
    //new Command.WaitFor("\"Action 1\""),
    //new Command.Simple("click::\"Pičo vokno\""),
    //new Command.WaitFor("QDialog"),
    //new Command.Simple("click::File"),
    //new Command.WaitFor("die!"),
    //new Command.Simple("value::die!::C:\\MYSELF\\Programming"),
    //new Command.Wait(1000),
    //new Command.Simple("submit::die!")
]