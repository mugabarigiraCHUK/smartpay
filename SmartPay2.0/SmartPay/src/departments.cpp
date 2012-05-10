#include "departments.h"
#include "ui_departments.h"
#include "selectemployee.h"
Departments::Departments(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::Departments)
{
    ui->setupUi(this);
    db = database;
    reloadDepartmentList();
    on_cmdAddNew_clicked();
}

Departments::~Departments()
{
    delete ui;
}

void Departments::reloadDepartmentList()
{
    model = new QSqlQueryModel(this);
    model->setQuery("SELECT DepartmentID, DepartmentName as 'Department Name' FROM departments", db);
    ui->treeView->setModel(model);
    ui->treeView->setColumnHidden(0, true);
}

void Departments::clearTexts()
{
    ui->txtDepartmentHead->setText("");
    ui->txtDepartmentName->setText("");
}

void Departments::on_treeView_clicked(const QModelIndex &index)
{
    ui->txtDepartmentHead->setText("");
    currentID = model->record(index.row()).value(0).toString();
    ui->txtDepartmentName->setText(model->record(index.row()).value(1).toString());
    ui->txtDepartmentHead->setText("");
    QSqlQuery qu = db.exec("SELECT * FROM departments WHERE departmentID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        QMessageBox::critical(this, "Database Error", qu.lastError().text());
    } else {
        while (qu.next())
            headID = qu.value(3).toString();
        QSqlQuery qu2 = db.exec("SELECT concat(FirstName, ' ', OtherNames) FROM employees WHERE employeeID = '" + headID + "'");
        if (qu.lastError().isValid()) {
            QMessageBox::critical(this, "Database Error", qu2.lastError().text());
        } else {
            while (qu2.next())
                ui->txtDepartmentHead->setText(qu2.value(0).toString());
        }
    }
    isAdding = false;
    ui->cmdDelete->setEnabled(true);
}

void Departments::on_cmdAddNew_clicked()
{
    clearTexts();
    ui->cmdAddNew->setEnabled(true);
    ui->cmdDelete->setEnabled(false);
    ui->cmdSave->setEnabled(true);
    isAdding = true;
}

void Departments::on_cmdSave_clicked()
{
    if (!isAdding) {
        db.exec("UPDATE departments SET DepartmentName = '" + ui->txtDepartmentName->text() + "', DepartmentHead = '" + headID + "' WHERE DepartmentID = '" + currentID + "'");
        if (db.lastError().isValid()) {
            QMessageBox::critical(this, "Database Error", db.lastError().text());
            return;
        }
    } else {
        QSqlQuery qu =  db.exec("INSERT INTO departments (DepartmentName, DepartmentHead) VALUES ('"
                                + ui->txtDepartmentName->text() + "', '" + headID + "')");
        if (!qu.lastError().isValid()) {
            isAdding = false;
            currentID = qu.lastInsertId().toString();
        } else {
            QMessageBox::critical(this, "Database Error", qu.lastError().text());
            return;
        }
    }
    reloadDepartmentList();
}

void Departments::on_cmdSetDepartmenytHead_clicked()
{
    SelectEmployee sel(this);
    if (sel.exec() == QDialog::Accepted) {
        ui->txtDepartmentHead->setText(sel.selectedEmployeeName);
        headID = sel.selectedEmployeeID;
    }
}

void Departments::on_cmdDelete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete " + ui->txtDepartmentName->text() + "?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        db.exec("DELETE FROM departments WHERE DepartmentID = '" + currentID + "'");
        reloadDepartmentList();
        on_cmdAddNew_clicked();
    }
}
