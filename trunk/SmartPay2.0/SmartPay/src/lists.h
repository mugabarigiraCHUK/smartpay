#ifndef LISTS_H
#define LISTS_H

#include <QtGui>
#include <QtSql>
#include "selectemployee.h"

namespace Ui {
class Lists;
}

class Departments;
class JobTitles;
class Holidays;
class PayrollMonths;
class Shifts;
class Saccos;

class Lists : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Lists(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Lists();
    
private slots:
    void on_actionDepartments_triggered();
    void on_actionJob_Titles_triggered();
    void on_actionShifts_triggered();
    void on_actionSaccos_triggered();
    void on_actionHolidays_triggered();
    void on_actionPayrollMonths_triggered();

private:
    Ui::Lists       *ui;
    Departments     *m_dept;
    JobTitles       *m_job_titles;
    Holidays        *m_holidays;
    QSqlDatabase    db;
    PayrollMonths   *m_months;
    Shifts          *m_shifts;
    Saccos          *m_saccos;
};

#endif // LISTS_H
