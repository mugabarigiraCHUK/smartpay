#include "attendance.h"
#include "ui_attendance.h"

#include "uploadattendance.h"
#include "publics.h"
#include "hourcalculator.h"
#include "recalculateattendance.h"

Attendance::Attendance(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Attendance)
{
    ui->setupUi(this);
    db = database;
    reloadAttendance();
    reloadEmployees();
    ui->StartDate->setDate(QDate::currentDate());
    ui->EndDate->setDate(QDate::currentDate());
    ui->AttReportWidget->db = db;
    ui->DailySignIn->db = db;
    ui->AttStartDate->setDate(QDate::currentDate());
    ui->AttEndDate->setDate(QDate::currentDate());
}

Attendance::~Attendance()
{
    delete ui;
}

void Attendance::on_UploadAttendance_clicked()
{
    UploadAttendance up(this, db);
    if (up.exec()) {
        reloadAttendance();
    }
}

void Attendance::on_dtpPast_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadAttendance();
}

void Attendance::reloadAttendance()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_attendance WHERE Date = '" + ui->dtpPast->date().toString("yyyy-MM-dd") + "'");
    ui->lstAttendance->setModel(model);
    ui->lstAttendance->setColumnHidden(0, true);
}

void Attendance::reloadEmployees()
{
    Publics::loadDbToComboBox(db, "SELECT * FROM vw_employeenames", "Name", ui->Employee);
}

void Attendance::recalculateEmployee()
{
    QString empID = Publics::getDbValue(db, "SELECT EmployeeID FROM vw_employeenames WHERE Name = '" + ui->Employee->currentText() + "'", "EmployeeID");
    QString startDate = Publics::getDateString(ui->StartDate->date());
    QString endDate = Publics::getDateString(ui->EndDate->date());
    HourCalculator::RecalculateEmployeeHours(empID, startDate, endDate, db);
    showEmployeeAttendance();
}

void Attendance::showEmployeeAttendance()
{
    QString empID = Publics::getDbValue(db, "SELECT EmployeeID FROM vw_employeenames WHERE Name = '" + ui->Employee->currentText() + "'", "EmployeeID");
    QString startDate = Publics::getDateString(ui->StartDate->date());
    QString endDate = Publics::getDateString(ui->EndDate->date());
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM vw_attendance_ex WHERE employeeID = '" + empID + "' AND Date BETWEEN '" + startDate +"' AND '"+ endDate +"'");
    ui->lst_EmployeeAttendance->setModel(model);
    ui->lst_EmployeeAttendance->setColumnHidden(0, true);
    ui->lst_EmployeeAttendance->setColumnHidden(1, true);
}

void Attendance::on_ShowEmployeeAttendance_clicked()
{
    showEmployeeAttendance();
}

void Attendance::on_RecalculateEmployeeAttendance_clicked()
{
    recalculateEmployee();
}

void Attendance::on_AttShowReport_clicked()
{
    ui->AttReportWidget->loadReport("AttendanceReport", " WHERE `Date` BETWEEN '" + Publics::getDateString(ui->AttStartDate->date()) + "' AND '" + Publics::getDateString(ui->AttEndDate->date()) + "' ORDER BY Date");
    //ui->AttReportWidget->loadReport("AttendanceReport", "");
}

void Attendance::on_RecalculateAllAttendance_clicked()
{
    RecalculateAttendance rec(this, db);
    if (rec.exec()) {

    }
}

void Attendance::on_GenerateDailySignInSheets_clicked()
{
    ui->DailySignIn->loadReport("EmployeesDepartments", "");
}
