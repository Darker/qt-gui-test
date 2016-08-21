#ifndef ANSI_H
#define ANSI_H

#include <QString>
class ANSI
{
    public:
        ANSI();

    static const QString control_sequence;
    static const char UP = 65;
    static const char DOWN = 66;
    static const char LEFT = 68;
    static const char RIGHT = 67;
    // Standalone control characters
    static const char BACKSPACE = 8;
    static const char DELETE = 127;
    static const char ESC = 27;
    static const char RETURN = 13;
    static const char NEW_LINE = 10;
    static const char BEGIN_CONTROL = '[';


};

#endif // ANSI_H
