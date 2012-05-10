#include "createtimetable.h"
#include "ui_createtimetable.h"

#include "publics.h"
#include "threadedcreatetimetable.h"

CreateTimetable::CreateTimetable(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::CreateTimetable)
{
    ui->setupUi(this);
    db = database;
    reloadShifts();
    reloadEmployees();
    ui->StartDate->setDate(QDate::currentDate());
    ui->EndDate->setDate(QDate::currentDate());
}

CreateTimetable::~CreateTimetable()
{
    delete ui;
}

void CreateTimetable::reloadShifts()
{
    Publics::loadDbToComboBox(db, "SELECT * FROM shifts", "ShiftName", ui->Shift);
}

void CreateTimetable::reloadEmployees()
{
    QSqlQuery qu = db.exec("SELECT EmployeeID, Name FROM vw_employeenames");
    while (qu.next()) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstEmployees);
        it->setText(99, qu.value(0).toString());
        it->setText(0, qu.value(1).toString());
        it->setCheckState(0, Qt::Unchecked);
    }
}

void CreateTimetable::on_CreateTimetableButton_clicked()
{
    QString shiftID = Publics::getDbValue(db, "SELECT * FROM shifts WHERE ShiftName = '" + ui->Shift->currentText() + "'", "ShiftID");
    if (ui->StartDate->date() > ui->EndDate->date()) {
        QMessageBox::warning(this, "Warning", "The start date must be before the end date.");
        return;
    }
    QStringList employeeList;
    for (int e = 0; e < ui->lstEmployees->invisibleRootItem()->childCount(); e++) {
        QTreeWidgetItem *it = ui->lstEmployees->invisibleRootItem()->child(e);
        if (it->checkState(0) == Qt::Checked)
            employeeList.insert(employeeList.count(), it->text(99));
    }

    if (employeeList.count() < 1) {
        QMessageBox::warning(this, "Error", "Please select one or more employees.");
        return;
    }

    ThreadedCreateTimetable *th = new ThreadedCreateTimetable(0);
    ui->CreateTimetableButton->setEnabled(false);
    ui->lstEmployees->setEnabled(false);
    ui->horizontalLayout->setEnabled(false);
    connect (th, SIGNAL(dateChanged(QString)), ui->lblDate, SLOT(setText(QString)));
    connect (th, SIGNAL(employeeChanged(QString)), ui->lblEmployeeName, SLOT(setText(QString)));

    connect (th, SIGNAL(employeeProgress(int)), ui->EmployeeProgressBar, SLOT(setValue(int)));
    connect (th, SIGNAL(totalProgress(int)), ui->TotalProgressBar, SLOT(setValue(int)));

    th->setVars(employeeList, ui->StartDate->date(), ui->EndDate->date(), shiftID, db);
    th->start();

    connect(th, SIGNAL(finished()), this, SLOT(threadFinished()));
}

void CreateTimetable::threadFinished()
{
    ui->CreateTimetableButton->setEnabled(true);
    ui->lstEmployees->setEnabled(true);
    ui->horizontalLayout->setEnabled(true);

    ui->lblDate->setText("");
    ui->lblEmployeeName->setText("");
}

void CreateTimetable::on_SelectAll_clicked()
{
    for (int i = 0; i < ui->lstEmployees->invisibleRootItem()->childCount(); i++) {
        ui->lstEmployees->invisibleRootItem()->child(i)->setCheckState(0, Qt::Checked);
    }
}

void CreateTimetable::on_SelectNone_clicked()
{

    for (int i = 0; i < ui->lstEmployees->invisibleRootItem()->childCount(); i++) {
        ui->lstEmployees->invisibleRootItem()->child(i)->setCheckState(0, Qt::Unchecked);
    }
}
