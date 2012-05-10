#include "uploadattendance.h"
#include "ui_uploadattendance.h"
#include <QMessageBox>
#include "publics.h"

UploadAttendance::UploadAttendance(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::UploadAttendance)
{
    ui->setupUi(this);
    db = database;
    ui->StartDate->setDate(QDate::currentDate());
    ui->EndDate->setDate(QDate::currentDate());
}

UploadAttendance::~UploadAttendance()
{
    delete ui;
}

void UploadAttendance::on_Close_clicked()
{
    this->reject();
}

void UploadAttendance::on_StartUpload_clicked()
{
    QSqlQuery qu = db.exec("SELECT * FROM checkinout WHERE checktime BETWEEN '" + ui->StartDate->date().toString("yyyy-MM-dd") + "' AND '" + ui->EndDate->date().toString("yyyy-MM-dd") + "'");
    if (!qu.lastError().isValid()) {
        while (qu.next()) {
            QString userID = qu.value(0).toString();
            QString cTime = qu.value(1).toString();
            cTime.replace("T", " ");
            QDateTime checkTime = QDateTime::fromString(cTime, "yyyy-MM-dd hh:mm:ss");
            //QMessageBox::information(this, "", cTime);
            QString employeeID = Publics::getDbValue(db, "SELECT * FROM employees_hr WHERE EmployeeNo = '" + userID + "'", "EmployeeID");

            QDate date = checkTime.date();
            QTime time = checkTime.time();

            QString query = "INSERT INTO employees_attendance (EmployeeID, Date, Time) VALUES ('" +
                    employeeID + "', '" +
                    date.toString("yyyy-MM-dd")   + "', '" +
                    time.toString("hh:mm:ss") + "')";

            //QMessageBox::information(this, "", query);

            db.exec(query);

            if (db.lastError().isValid()) {
                qDebug() << db.lastError().text();
            }else {
                //qDebug() << "Success";
            }
        }
    } else {
        QMessageBox::critical(this, "Error", qu.lastError().text());
    }
}
