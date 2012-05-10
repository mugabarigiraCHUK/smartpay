#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class Attendance;
}

class Attendance : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Attendance(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Attendance();
    
private slots:
    void on_UploadAttendance_clicked();
    void on_dtpPast_dateChanged(const QDate &date);
    void on_ShowEmployeeAttendance_clicked();
    void on_RecalculateEmployeeAttendance_clicked();
    void on_AttShowReport_clicked();
    void on_RecalculateAllAttendance_clicked();
    void on_GenerateDailySignInSheets_clicked();

private:
    Ui::Attendance *ui;
    QSqlDatabase db;
    void reloadAttendance();
    void reloadEmployees();
    void recalculateEmployee();
    void showEmployeeAttendance();
};

#endif // ATTENDANCE_H
