#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include "global.h"
#include "loginwindow.h"
#include <QMessageBox>

ForgotPassword::ForgotPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ForgotPassword)
{
     ui->setupUi(this);

     connect(SOCKET, SIGNAL(textMessageReceived(QString)),this,SLOT(ReplyFromServer(QString)));
     ui->leNewPass->setEchoMode(QLineEdit::Password);
     ui->leNewPassConfirm->setEchoMode(QLineEdit::Password);
}

ForgotPassword::~ForgotPassword(){
    delete ui;
}


QVector<QString> ForgotPassword::commaEndedStr(QString Str){


    //QVector<QStringRef> vStr = Str.splitRef(QRegExp("\\s*,\\s*"),QString::SkipEmptyParts);
    //return vStr;




    QString tempStr = "";
    QVector<QString> sv;

    for (int i=0; i < Str.length(); i++){
        if(Str.at(i) != ','){
            tempStr.append(Str.at(i));              //append temp str till , is reached
        }else{
            sv.append(tempStr);                 //when , : append temp str in vector and clear tempstr
            tempStr = "";
        }
    }//end for

    return sv;

}


void ForgotPassword::on_pbGetQuestion_clicked(){
    SOCKET->sendTextMessage("fq"+ui->leUsername->text()+","+LoginWindow::getStrRequestNumber()+",");
}


void ForgotPassword::ReplyFromServer(QString messageFromServer){ //reply from server
    if (messageFromServer.at(0) == 'f' && messageFromServer.at(1) == 'a'){
        messageFromServer.remove(0,2);
        QVector<QString> vMessage = commaEndedStr(messageFromServer);

        if(LoginWindow::getStrRequestNumber() == vMessage.at(0)){
            ui->lSecurityQFromServer->setText(vMessage.at(1));
            //qWarning()<<"LENGTH: "<<vMessage.at(1).length();
            //qWarning()<<"MESSAGE: "<<vMessage.at(1);

        }

        if(vMessage.at(1).length() == 0){
            QMessageBox::information(this,
                                     tr("User Registration"),
                                     tr("ERROR: invalid username."));

            ui->pbChangePass->setDisabled(true);
        }else{
            ui->pbChangePass->setEnabled(true);
        }
    }else if (messageFromServer.at(0) == 'f' && messageFromServer.at(1) == 'd') {

        messageFromServer.remove(0,2);
        if(LoginWindow::getStrRequestNumber() == messageFromServer.mid(0,8) && messageFromServer.length() ==10){
            QMessageBox::information(
                this,
                tr("Forgot Password"),
                tr("ERROR: Enter Correct Information.") );

        }else if (LoginWindow::getStrRequestNumber() == messageFromServer.mid(0,8) && messageFromServer.length() >10){
            QMessageBox::information(
                this,
                tr("Forgot Password"),
                tr("Password Change Sucessful.") );

            this->close();
        }
    }
}

void ForgotPassword::on_pbChangePass_clicked()
{
    bool isUsernameOk = false;
    bool isPwdOk = false;
    bool isSecurityAnsOk = false;
    bool isDOBOk = false;

    QString username = ui->leUsername->text();
    QString password1 = ui->leNewPass->text();
    QString password2 = ui->leNewPass->text();

    QString securityAns = ui->leSecurityAns->text();
    QString dob = ui->leDob->text();

    if(username.length()>3){
        isUsernameOk = true;
    }else{
        //enter username
    }

    if ( password1 == password2 && password1.length() > 4){
        isPwdOk = true;
        password1 = hashSha1(password1+username); //hash with salt
    }else{
        //Password doesn't match.
    }

    if (securityAns.length()>0){
        isSecurityAnsOk = true;
        securityAns = hashSha1(securityAns);
    }else{
        //enter answer
    }

    if (dob.length()>9){
        isDOBOk = true;
        dob = hashSha1(dob);
    }
    else{
        //enter dob in DD/MM/YYYY
    }

    //if everything checksouts true, all bool values
    if (isUsernameOk && isPwdOk && isSecurityAnsOk && isDOBOk){
        QString sendForPassChange = "fc"+username+","+password1+","+securityAns+","+dob+","+LoginWindow::getStrRequestNumber()+",";
        SOCKET->sendTextMessage(sendForPassChange);
        SOCKET->flush();


    }else{
        qWarning()<<"ERROR IN OK.";
        qWarning()<<"usename : "<<isUsernameOk<<username;
        qWarning()<<"password: "<<isPwdOk;
        qWarning()<<"sec ans : "<<isSecurityAnsOk;
        qWarning()<<"DOB     : "<<isDOBOk;

    }
}

QString ForgotPassword::hashSha1(QString hashIt){
    QString hashedString = QString("%1").arg(QString(QCryptographicHash::hash(hashIt.toUtf8(),QCryptographicHash::Sha1).toHex()));
    return hashedString;
}

