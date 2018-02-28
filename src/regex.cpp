#include "regex.h"
#include <QDebug>

RegEx::RegEx(){
}

bool RegEx::regEmail(QString str){
    QRegExp regX;
    regX.setPattern("[a-z]+[0-9]*[_]*[a-z]*[0-9]*@[a-z]+.[a-z]+");
    return regX.exactMatch(str);
}

bool RegEx::regUserName (QString str){
    QRegExp regX;
    regX.setPattern("([A-Za-z])\\w+");
    return regX.exactMatch(str);
}

bool RegEx::regName (QString str){
    QRegExp regX;
    regX.setPattern("[a-zA-Z]+");
    return regX.exactMatch(str);
}

bool RegEx::regDob (QString str){
    QRegExp regX;
    regX.setPattern("(0[1-9]|[12][0-9]|3[01])[/](0[1-9]|1[0-2])[/](19[0-9][0-9]|20[0-9][0-9])");
    return regX.exactMatch(str);
}
