#ifndef HOURCALCULATOR_H
#define HOURCALCULATOR_H

#include <QtSql>
#include <QtGui>

class HourCalculator
{
public:
    explicit HourCalculator();
    static void RecalculateEmployeeHours(QString employeeID, QString monthID, QSqlDatabase db);
    static void RecalculateEmployeeHours(QString employeeID, QString startDate, QString endDate, QSqlDatabase db);
    static void CalculateAttendanceForDay(QString date, QString employeeID, QSqlDatabase db);
    static void CreateEmployeeTimetable(QDate date, QString employeeID, QString shiftID, QSqlDatabase db);
};

#endif // HOURCALCULATOR_H
