#include "payrollmonths.h"
#include "ui_payrollmonths.h"

PayrollMonths::PayrollMonths(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::PayrollMonths)
{
    ui->setupUi(this);
    db = database;
    model = new QSqlQueryModel(this);
    ui->treeView->setModel(model);
    reload();
    on_cmdAddNew_clicked();
}

PayrollMonths::~PayrollMonths()
{
    delete ui;
}

void PayrollMonths::reload()
{
    model->setQuery("SELECT * FROM vw_months", db);
    ui->treeView->setColumnHidden(0, true);
}

void PayrollMonths::clearTexts()
{
    ui->MonthName->setText("");
    ui->Year->setText("");
    ui->Closed->setChecked(false);
}

void PayrollMonths::on_cmdAddNew_clicked()
{
    isAdding = true;
    clearTexts();
    ui->cmdDelete->setEnabled(false);
}

void PayrollMonths::on_cmdSave_clicked()
{
    QString closed = "No";
    if (ui->Closed->isChecked())
        closed = "Yes";
    if (isAdding) {
        QSqlQuery qu =  db.exec("INSERT INTO months (Year, MonthName, StartDate, EndDate, Closed) VALUES ('" +
                                ui->Year->text() + "', '" +
                                ui->MonthName->text() + "', '" +
                                ui->StartDate->date().toString("yyyy-MM-dd") + "', '" +
                                ui->EndDate->date().toString("yyyy-MM-dd") + "', '" +
                                closed + "')");
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Error", qu.lastError().text());
            return;
        }
        currentID = qu.lastInsertId().toString();
        isAdding = false;
    } else {
        db.exec("UPDATE months SET "
                "Year = '" + ui->Year->text() + "', "
                "MonthName = '" + ui->MonthName->text()  + "', "
                "StartDate = " + ui->StartDate->date().toString("yyyy-MM-dd") +   "', "
                "EndDate = '" + ui->EndDate->date().toString("yyyy-MM-dd") + "', "
                "Closed = '" + closed  + "' WHERE MonthID  = " + currentID + "'");
        if (db.lastError().isValid()) {
            QMessageBox::critical(this, "Error", db.lastError().text());
            return;
        }
    }
    reload();
    ui->cmdDelete->setEnabled(false);
}

void PayrollMonths::on_cmdDelete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this month?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        db.exec("DELETE FROM months WHERE MonthID = '" + currentID + "'");
        reload();
        on_cmdAddNew_clicked();
    }
}

void PayrollMonths::on_treeView_clicked(const QModelIndex &index)
{
    currentID = model->record(index.row()).value(0).toString();
    clearTexts();
    QSqlQuery qu = db.exec("SELECT * FROM months WHERE MonthID = '" + currentID + "'");
    while (qu.next()) {
        ui->Year->setText(qu.value(1).toString());
        ui->MonthName->setText(qu.value(2).toString());
        ui->StartDate->setDate(QDate::fromString(qu.value(3).toString(), "yyyy-MM-dd"));
        ui->EndDate->setDate(QDate::fromString(qu.value(4).toString(), "yyyy-MM-dd"));
        QString closed = qu.value(6).toString();
        ui->Closed->setChecked(false);
        if (closed == "Yes")
            ui->Closed->setChecked(true);
    }
}
