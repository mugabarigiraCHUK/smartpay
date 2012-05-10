#include "issueadvance.h"
#include "ui_issueadvance.h"
#include "publics.h"
IssueAdvance::IssueAdvance(QWidget *parent, QSqlDatabase database, int employeeID) :
    QDialog(parent),
    ui(new Ui::IssueAdvance)
{
    ui->setupUi(this);
    db = database;
    Publics pubs;
    ui->EmployeeName->setText(pubs.getDbValue(db, "SELECT Name FROM vw_employeenames WHERE EmployeeID = '" + QString::number(employeeID)  + "'", "Name"));
    ui->EmployeeName->setEnabled(false);
    id = employeeID;

    ui->AdvanceDate->setDate(QDate::currentDate());
}

IssueAdvance::~IssueAdvance()
{
    delete ui;
}

void IssueAdvance::on_cancelButton_clicked()
{
    this->reject();
}

void IssueAdvance::on_IssueButton_clicked()
{
    db.exec("INSERT INTO employee_advances (EmployeeID, AdvanceDate, Amount) VALUES ('" +
            QString::number(id) + "', '" + ui->AdvanceDate->date().toString("yyyy-MM-dd") + "', '" +
            QString::number(ui->Amount->value()) + "')");

    if (db.lastError().isValid()) {
        QMessageBox::critical(this, "Error", db.lastError().text());
    }
    else
    {
        this->accept();
    }
}
