#include "userlogin.h"
#include "ui_userlogin.h"

#include <QMessageBox>

UserLogin::UserLogin(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::UserLogin)
{
    ui->setupUi(this);
    db = database;
    connect (ui->Cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect (ui->Login, SIGNAL(clicked()), SLOT(tryLogin()));
}

UserLogin::~UserLogin()
{
    delete ui;
}

void UserLogin::tryLogin() {
    bool ok = false;
    EditHR = false;
    EditLeaves = false;
    EditFinance = false;
    EditAttendance = false;
    EditPayroll  = false;

    QSqlQuery qu = db.exec("SELECT * FROM users WHERE LoginName = '" + ui->UserName->text() + "'");
    while (qu.next()) {
        if (qu.record().value("Password").toString() == ui->Password->text()) {
            this->accept();
            QSqlRecord rec = qu.record();
            if (rec.value("EditHR") == "Yes")
                EditHR = true;
            if (rec.value("EditFinance") == "Yes")
                EditFinance = true;
            if (rec.value("EditLeaves") == "Yes")
                EditLeaves = true;
            if (rec.value("EditPayroll") == "Yes")
                EditPayroll = true;
            if (rec.value("EditAttendance") == "Yes")
                EditAttendance = true;

            userID = rec.value("UserID").toString();
            ok = true;
        }
    }
    if (!ok)
        QMessageBox::critical(this, "Login Error", "Login failed.\nPlease check the user name/password");
}
