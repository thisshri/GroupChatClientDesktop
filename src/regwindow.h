#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "regex.h"
#include "global.h"
#include <QCryptographicHash>

namespace Ui {
class RegWindow;
}

class RegWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget *parent = 0);
    QString hashSha1(QString hashIt);
    ~RegWindow();

private slots:

    void ReplyFromServer(QString);
    void on_pbRegister_clicked();

    void on_pbCheckUsername_clicked();

private:

    QString userName;
    QString firstName;
    QString lastName;
    QString password;
    QString dob;
    QString email;
    QString prq;
    QString pra;

    RegEx regX;

    Ui::RegWindow *ui;
};

#endif // REGWINDOW_H
