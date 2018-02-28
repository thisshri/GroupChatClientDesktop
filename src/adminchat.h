#ifndef ADMINCHAT_H
#define ADMINCHAT_H

#include <QMainWindow>
#include "global.h"

namespace Ui {
class AdminChat;
}

class AdminChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminChat(QWidget *parent = 0);

    void loadAllBlocked();
    void loadAllUnBlocked();
    QVector<QString> comaEndedStr(QString baStr);


    ~AdminChat();

private slots:
    void on_pbBlock_clicked();

    void on_pbUnblock_clicked();

    void loadMessage(QString mFromServ);

    void on_pbLoadUnblockedUsers_clicked();

    void on_pbLoadBlockUsers_clicked();

private:
    Ui::AdminChat *ui;
};

#endif // ADMINCHAT_H
