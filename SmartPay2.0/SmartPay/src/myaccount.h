#ifndef MYACCOUNT_H
#define MYACCOUNT_H

#include <QtSql>
#include <QMainWindow>

namespace Ui {
class MyAccount;
}

class MyAccount : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MyAccount(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~MyAccount();
    QString userID;
private:
    Ui::MyAccount *ui;
    QSqlDatabase db;
signals:
    void logOff();
};

#endif // MYACCOUNT_H
