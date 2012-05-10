#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class MainWindow;

}
class Employees;
class Lists;
class Leaves;
class Payroll;
class Attendance;
class Timetable;
class Admin;
class MyAccount;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~MainWindow();
    void setDatabase(QSqlDatabase database);
private:
    Ui::MainWindow *ui;
    Employees  *m_employees;
    Lists   *m_lists;
    Leaves  *m_leaves;
    Payroll *m_payroll;
    Attendance *m_attendance;
    Timetable *m_timeTable;
    Admin *m_admin;
    MyAccount *m_acc;

    QSqlDatabase db;
    int count;
private slots:
    void logOff();
    void logIn();
};

#endif // MAINWINDOW_H
