#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTcpSocket>
#include <regex>
#include <QCryptographicHash>
#include <QSslError>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    QString hashSha1(QString hashIt);
    QString getStrRandomNumber();
    static QString getStrRequestNumber();


    ~LoginWindow();

private slots:
    void on_pbRegister_clicked();
    void on_pbLogin_clicked();
    void onConnected();
    void onSslErrors(const QList<QSslError> &errors);

    void ReplyFromServer(QString serverMessage);


    void on_pbForgotPassword_clicked();

private:
    Ui::LoginWindow *ui;
    QString SERVERMESSAGE = "Uninited string............";

    static QString strRandomNumber;

};

#endif // LOGINWINDOW_H
