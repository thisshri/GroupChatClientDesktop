#include "adminchat.h"
#include "ui_adminchat.h"
#include <QWebSocket>

AdminChat::AdminChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminChat)
{
    ui->setupUi(this);

    //connect(SOCKET,SIGNAL(readyRead()),this,SLOT(loadMessage()));
    connect(SOCKET,SIGNAL(textMessageReceived(QString)),
                          this,SLOT(loadMessage(QString)));



}

AdminChat::~AdminChat()
{
    delete ui;
}

void AdminChat::loadMessage(QString mFromServ){

    //QByteArray byteMessage = SOCKET->readAll();
    qWarning()<<"MESSAGE RECIEVED AT ADMIN";
    DATA = mFromServ;
    if (mFromServ.at(0) == 'm'){          //loading all the messages
        //QString strMessage(byteMessage);
        ui->textBrowser->append(mFromServ.remove(0,1));
    }else if(mFromServ.at(0) == 'c'){             //loading all blocked users
        loadAllBlocked();
    }else if(mFromServ.at(0) == 'v'){             //loading all unblocked users
        loadAllUnBlocked();
    }else{
        qWarning()<<"CLIENT: ERROR: RECEIVED MESSAGE:"<<DATA;
    }
}

void AdminChat::loadAllBlocked(){
    ui->lwBlocked->clear();
    qWarning()<<"LOAD ALL UNBLOCKED CALLED:"<<DATA;

    QVector<QString> vString = comaEndedStr(DATA.remove(0,2));
    for (int i = 0; i < vString.length(); i++){
        ui->lwBlocked->addItem(vString.at(i));
    }
}

void AdminChat::loadAllUnBlocked(){
    ui->lwUnblocked->clear();
    qWarning()<<"LOAD ALL UNBLOCKED CALLED:"<<DATA;
    QVector<QString> vString = comaEndedStr(DATA.remove(0,2));
    for (int i = 0; i < vString.length(); i++){
        ui->lwUnblocked->addItem(vString.at(i));
    }//

}

void AdminChat::on_pbBlock_clicked()
{
    QString userN = ui->leBlock->text();
//    SOCKET->write("b"+userN.toUtf8());
//    SOCKET->flush();

    SOCKET->sendTextMessage("b"+userN);
    SOCKET->flush();

    ui->leBlock->clear();
    on_pbLoadBlockUsers_clicked();
    on_pbLoadUnblockedUsers_clicked();

}

void AdminChat::on_pbUnblock_clicked()
{
    QString userN = ui->leUnBlock->text();
    //SOCKET->write("u"+userN.toUtf8());


    SOCKET->sendTextMessage("u"+userN);
    SOCKET->flush();

    ui->leUnBlock->clear();
    on_pbLoadBlockUsers_clicked();
    on_pbLoadUnblockedUsers_clicked();

}

QVector<QString> AdminChat::comaEndedStr(QString Str){


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

void AdminChat::on_pbLoadUnblockedUsers_clicked()
{
    //SOCKET->write("v"); //get all unblocked users
    //SOCKET->flush();

    SOCKET->sendTextMessage("v");
    SOCKET->flush();


}

void AdminChat::on_pbLoadBlockUsers_clicked()
{
    //SOCKET->write("c"); //get all blocked users
    //SOCKET->flush();

    SOCKET->sendTextMessage("c");
    SOCKET->flush();

}

