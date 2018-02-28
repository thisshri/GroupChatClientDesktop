#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QHostAddress>
#include <string>
#include <QDataStream>


namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    void closeEvent (QCloseEvent *event);
    ~Chat();

private slots:
    void on_pbSend_clicked();
    void loadMessage(QString response);
    void on_leUserChat_returnPressed();

private:
    Ui::Chat *ui;
    //QTcpSocket *socket;

};

#endif // CHAT_H
