#include "holidays.h"
#include "ui_holidays.h"

Holidays::Holidays(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Holidays)
{
    ui->setupUi(this);
}

Holidays::~Holidays()
{
    delete ui;
}
