#include "recalculateattendance.h"
#include "ui_recalculateattendance.h"

#include "threadedattendancecalc.h"

RecalculateAttendance::RecalculateAttendance(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::RecalculateAttendance)
{
    ui->setupUi(this);
    //ui->progressBar->setVisible(false);
    db = database;
    loadEmployees();
}

RecalculateAttendance::~RecalculateAttendance()
{
    delete ui;
}

void RecalculateAttendance::loadEmployees()
{
    QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames");
    if (!qu.lastError().isValid()) {
        while (qu.next()) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->EmployeesList);
            it->setCheckState(0, Qt::Unchecked);
            it->setText(0, qu.value(2).toString());
            it->setText(99, qu.value(0).toString());
        }
    }
}

void RecalculateAttendance::on_SelectAll_clicked()
{
    for (int i = 0; i < ui->EmployeesList->invisibleRootItem()->childCount(); i++) {
        ui->EmployeesList->invisibleRootItem()->child(i)->setCheckState(0, Qt::Checked);
    }
}

void RecalculateAttendance::on_SelectNone_clicked()
{
    for (int i = 0; i < ui->EmployeesList->invisibleRootItem()->childCount(); i++) {
        ui->EmployeesList->invisibleRootItem()->child(i)->setCheckState(0, Qt::Unchecked);
    }
}

void RecalculateAttendance::on_Recalculate_clicked()
{
    QStringList employees;
    for (int i = 0; i < ui->EmployeesList->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *it = ui->EmployeesList->invisibleRootItem()->child(i);
        if (it->checkState(0) == Qt::Checked) {
            employees.insert(employees.count(), it->text(99));
        }
    }

    ThreadedAttendanceCalc *th = new ThreadedAttendanceCalc(0);
    int p = 0;
    th->setVars(db, employees, ui->StartDate->selectedDate(), ui->EndDate->selectedDate(), p);
    connect (th, SIGNAL(showPercentage(int)), ui->totalProgress, SLOT(setValue(int)));
    connect (th, SIGNAL(showEmployeePercentage(int)), ui->progressBar, SLOT(setValue(int)));
    connect (th, SIGNAL(employeeChanged(QString)), ui->lblEmployeeName, SLOT(setText(QString)));
    connect (th, SIGNAL(dateChanged(QString)), ui->lblDate, SLOT(setText(QString)));
    th->start();
}
