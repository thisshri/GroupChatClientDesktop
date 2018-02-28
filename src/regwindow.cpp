#include "regwindow.h"
#include "ui_regwindow.h"
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <global.h>
#include "loginwindow.h"

RegWindow::RegWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);

    ui->lePassword->setEchoMode(QLineEdit::Password);
    ui->lePasswordConfirm->setEchoMode(QLineEdit::Password);
    ui->pbRegister->setDisabled(true);

    connect(SOCKET, SIGNAL(textMessageReceived(QString)),this,SLOT(ReplyFromServer(QString)));

}

RegWindow::~RegWindow()
{
    delete ui;
}

QString RegWindow::hashSha1(QString hashIt){
    QString hashedString = QString("%1").arg(QString(QCryptographicHash::hash(hashIt.toUtf8(),QCryptographicHash::Sha1).toHex()));
    return hashedString;
}


void RegWindow::on_pbRegister_clicked()
{
    bool infoCorrent = true;

    if (regX.regUserName(ui->leUsername->text())){//USERNAME
        userName = ui->leUsername->text();
    }else{
        infoCorrent = false;
        qWarning()<<"Error: Username";
    }
    if (regX.regName(ui->leFirstName->text())){//FIRSTNAME
        firstName = ui->leFirstName->text();
    }else{
        infoCorrent = false;
        qWarning()<<"Error: FirstName";
    }
    if(regX.regName(ui->leLastName->text())){//LASTNAME
        lastName = ui->leLastName->text();
    }else{
        infoCorrent = false;
        qWarning()<<"Error: Lastname";
    }
    if (ui->lePassword->text() == ui->lePasswordConfirm->text() && ui->lePassword->text().length() >4 ){//PASSWORD
        password = hashSha1(ui->lePassword->text()+userName);
        //hashed and store in password
    }else{
        infoCorrent = false;
        qWarning()<<"Error: password";
    }
    if(regX.regDob(ui->leDob->text())){//DOB
        dob = hashSha1(ui->leDob->text());
    }else{
        infoCorrent = false;
        qWarning()<<"Error: Dob format";
    }
    if(regX.regEmail(ui->leEmailId->text())){
        email = ui->leEmailId->text();
    }else{
        infoCorrent = false;
        qWarning()<<"Enter valid email.";
    }
    if (ui->lePasswordRecoveryQ->text().length() > 0){
        prq = ui->lePasswordRecoveryQ->text();
    }else{
        infoCorrent = false;
        qWarning()<<"Error: prq";
    }
    if (ui->lePasswordRecoveryA->text().length() > 0){
        pra = hashSha1(ui->lePasswordRecoveryA->text());
    }else{
        infoCorrent = false;
        qWarning()<<"Error: pra";
    }
    if (infoCorrent){
        QString loginStr("rr'"+userName+"','"+firstName+"','"+lastName+"','"
                      +password+"','"+dob+"','"+email+"','"+prq+"','"+pra+"','u'");


        SOCKET->sendTextMessage(loginStr);
        SOCKET->flush();

    }else{
        QMessageBox::warning(this,
                             tr("Registration Window"),
                             tr("Fill all the information properly!"));
    }

}

void RegWindow::on_pbCheckUsername_clicked()
{
    //get username from db
    //assign username to usenameVar;

    QString username = ui->leUsername->text();
    SOCKET->sendTextMessage("ra"+LoginWindow::getStrRequestNumber()+username);
}



void RegWindow::ReplyFromServer(QString textFromServer){
    qWarning()<<"middle:\t"<<textFromServer.mid(2,10);


    if (textFromServer.at(0) == 'r' && textFromServer.at(1)=='a' &&
            LoginWindow::getStrRequestNumber() == textFromServer.mid(2,10)){
        qWarning()<<"username avalible";
        ui->pbRegister->setEnabled(true);
        QMessageBox::information(this,
                                 tr("Registration Window"),
                                 tr("username avalible!"));
    }else if(textFromServer.at(0) == 'r' && textFromServer.at(1)=='n' &&
            LoginWindow::getStrRequestNumber() == textFromServer.mid(2,10)){
        qWarning()<<"username not avalible";
        ui->pbRegister->setDisabled(true);
        QMessageBox::warning(this,
                                 tr("Registration Window"),
                                 tr("username not avalible!"));
    }

}



