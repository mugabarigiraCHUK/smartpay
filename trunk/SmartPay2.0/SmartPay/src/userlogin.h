#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QtSql>

#include <QDialog>

namespace Ui {
class UserLogin;
}

class UserLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserLogin(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~UserLogin();
    bool EditHR;
    bool EditLeaves;
    bool EditFinance;
    bool EditAttendance;
    bool EditPayroll;
    QString userID;
private:
    Ui::UserLogin *ui;
    QSqlDatabase db;

private slots:
    void tryLogin();
};

#endif // USERLOGIN_H
