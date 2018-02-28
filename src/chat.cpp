#include "chat.h"
#include "ui_chat.h"
#include <QTime>

#include "global.h"



Chat::Chat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chat){
    ui->setupUi(this);

    connect(SOCKET,SIGNAL(textMessageReceived(QString)),
            this,SLOT(loadMessage(QString)));

    SOCKET->sendTextMessage("m\n< "+USERNAME+" joined the group >\n");
}


void Chat::closeEvent (QCloseEvent *event){
    SOCKET->sendTextMessage("m\n< "+USERNAME+" left the group >\n");
}



Chat::~Chat(){
    delete ui;
}


void Chat::loadMessage(QString response){
    if(response.at(0) == 'm'){
        ui->tbChatView->append(response.remove(0,1)); //message for group
    }
    else{
        qWarning()<<"CHAT loadMessage else: "<<DATA;
    }
}

void Chat::on_pbSend_clicked()
{
    QTime time = QTime::currentTime();
    QString cTimeStr = time.toString("hh:mm A");
    QString message = ui->leUserChat->text();
    ui->leUserChat->clear();

    if (message.length() > 0){
        SOCKET->sendTextMessage("m"+USERNAME+"\n"+message+"\n"+cTimeStr+"\n");
        SOCKET->flush();
    }else{
        //qWarning()<<"error: techat ";
    }
}

void Chat::on_leUserChat_returnPressed()
{
    on_pbSend_clicked();
}
