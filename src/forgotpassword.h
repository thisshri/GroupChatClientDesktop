#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = 0);

    QVector<QString> commaEndedStr(QString Str);
    QString hashSha1(QString hashIt);

    ~ForgotPassword();

private slots:
    void on_pbGetQuestion_clicked();
    void ReplyFromServer(QString messageFromServer);

    void on_pbChangePass_clicked();

private:
    Ui::ForgotPassword *ui;
};

#endif // FORGOTPASSWORD_H
