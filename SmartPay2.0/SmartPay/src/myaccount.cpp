#include "myaccount.h"
#include "ui_myaccount.h"

MyAccount::MyAccount(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::MyAccount)
{
    ui->setupUi(this);
    ui->groupBox->setVisible(false);
    db = database;

    connect (ui->LogOff, SIGNAL(clicked()), SIGNAL(logOff()));
}

MyAccount::~MyAccount()
{
    delete ui;
}
