#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "regwindow.h"
#include "chat.h"
#include "adminchat.h"
#include <QDebug>
#include <QMessageBox>
#include <regex.h>
#include <QCryptographicHash>
#include "global.h"

#include <forgotpassword.h>

#include <QWebSocket>

QString USERNAME;
//QTcpSocket *SOCKET;
QWebSocket *SOCKET;
QString DATA;

QString LoginWindow::strRandomNumber = "00000000";

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{

    SOCKET = new QWebSocket;

    connect(SOCKET, SIGNAL(connected()), this,SLOT(onConnected()));

    typedef void (QWebSocket:: *sslErrorsSignal)(const QList<QSslError> &);

    connect(SOCKET, static_cast<sslErrorsSignal>(&QWebSocket::sslErrors),
            this, &LoginWindow::onSslErrors);




    connect(SOCKET, SIGNAL(textMessageReceived(QString)),this,SLOT(ReplyFromServer(QString)));
    ui->setupUi(this);
    ui->leUserPassword->setEchoMode(QLineEdit::Password);

    strRandomNumber = getStrRandomNumber();



    SOCKET->open(QUrl(QStringLiteral("ws://localhost:1234")));
}


LoginWindow::~LoginWindow()
{
    delete ui;

}


void LoginWindow::onConnected()
{
    qDebug() << "WebSocket connected";
    //connect(&m_webSocket, &QWebSocket::textMessageReceived,
   //         this, &SslEchoClient::onTextMessageReceived);
//    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}
//! [onConnected]



void LoginWindow::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

    SOCKET->ignoreSslErrors();
}





QString LoginWindow::hashSha1(QString hashIt){
    QString hashedString = QString("%1").arg(QString(QCryptographicHash::hash(hashIt.toUtf8(),QCryptographicHash::Sha1).toHex()));
    return hashedString;
}

void LoginWindow::on_pbRegister_clicked()
{
    RegWindow * regWindow = new RegWindow;
    regWindow->show();

}



void LoginWindow::ReplyFromServer(QString serverMessage){

    qWarning()<<"-----------------------------------------------";
    qWarning()<<"AT CLIENT SERVER SAYS: "<<serverMessage;


    DATA = serverMessage;
    //qWarning()<<"client data at mid:"<<DATA.mid(3,10);
 //   qWarning()<<"Is login attempt : "<<isAdminLoginAttempt<<DATA.at(0)<<DATA.at(1);
    if( DATA.at(0) == 'a' && DATA.at(1) == 'a' && DATA.mid(3,10) == getStrRequestNumber()){

        qWarning()<<"working ---------------------------";
        AdminChat *adminChat = new AdminChat;
        adminChat->show();



        //DATA = "lb";

    }else if (DATA.at(0) == 'a' && DATA.at(1) == 'b' && DATA.mid(3,12) == getStrRequestNumber()) {
        //incorrect admin password.
        //QMessageBox::warning()
        QMessageBox::warning(
            this,
            tr("Admin login failed!"),
            tr("Incorrect admin password.") );

    }else if(DATA.at(0) == 'l' && DATA.at(1) == 'u' ){        //USER LOGIN
        QString tempData = DATA.remove(0,2);
            if(tempData == getStrRequestNumber()){
                Chat *chat = new Chat;
                chat->show();
                qWarning()<<"LOGINWINDOW: YOU GOT LOGIN";

            }
            else{
                    qWarning()<<"LOGINWINDOW: ANOTHER USER GOT LOGIN";
            }

    }else if(DATA.at(0) == 'l' && DATA.at(1) == 'b' ){        //USER LOGIN
        QString tempData = DATA.remove(0,2);
            //if(tempData == strRandomNumber){
            if(tempData == getStrRequestNumber()){

                qWarning()<<"LOGINWINDOW: INVALID AUTHENTICATION OR USER IS BLOCKED.";
            }
            else{
                    qWarning()<<"LOGINWINDOW: ANOTHER USER WITH INVALID AUTH TRING TO LOGIN";

            }

    }else{
        qWarning()<<"Other message: "<<DATA;

        // isAdminLoginAttempt = false;

    }



}


QString LoginWindow::getStrRandomNumber(){
    QString strRandom ;


    while (strRandom.length() != 8) {
        strRandom = QString::number(qrand());
    }
    //static QString str = "12341344";
    return strRandom;
}


QString LoginWindow::getStrRequestNumber(){
    //return this->strRandomNumber;
    return strRandomNumber;
}



void LoginWindow::on_pbLogin_clicked()
{
    qWarning()<<"message form server: "<<DATA;

    //admin is selected
    if (ui->leUsername->text() == "admin"){

        USERNAME = "admin";
        QString password = hashSha1(ui->leUserPassword->text());
        QString sendForLogin = "a"+password+","+strRandomNumber;
        qWarning()<<"SEND FOR LOGIN:"<<sendForLogin;

        SOCKET->sendTextMessage(sendForLogin);
        SOCKET->flush();


    }else{         //USER
        USERNAME = ui->leUsername->text();                      //check when to assign
        QString password = hashSha1(ui->leUserPassword->text()+USERNAME);
        QString sendForLogin = "l"+USERNAME+","+password+","+this->strRandomNumber+",";
        SOCKET->sendTextMessage(sendForLogin);
        SOCKET->flush();
    }

   // disconnect(SOCKET,SIGNAL(readyRead()),this,SLOT(ReplyFromServer()));

    //ui->leAdminPassword->clear();
    ui->leUsername->clear();
    ui->leUserPassword->clear();
}



void LoginWindow::on_pbForgotPassword_clicked()
{
    ForgotPassword * windowForgotPass = new ForgotPassword;
    windowForgotPass->show();
}
