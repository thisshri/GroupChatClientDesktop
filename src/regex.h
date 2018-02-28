#ifndef REGEX_H
#define REGEX_H

#include<QRegExp>

class RegEx
{
    //QRegExp regX;
public:
    RegEx();
    bool regEmail (QString );
    bool regUserName (QString );
    bool regDob (QString );
    bool regName (QString );
};

#endif // REGEX_H
