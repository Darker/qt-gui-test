# qt-gui-test
Library for testing and scripting Qt GUI widgets

Usage at this point:

 - Compile the program
 - Run telnet, connect to port 9666
 - The telnet control supports following syntax:
     - `name of command::object selector::params
     - Object selector may be name of the object or text associated with it (eg. button text or window title)
 - Following commands may be used
     - `click` - creates click event for object
     - `submit` - If applicable, submits entered data
     - `value` - sets value of the object
     
Current work in progress:

  - Ensure that `QFileDialog` has correct value after submit
