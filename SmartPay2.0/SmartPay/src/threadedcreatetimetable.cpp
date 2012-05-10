#include "threadedcreatetimetable.h"
#include "publics.h"
#include "hourcalculator.h"

ThreadedCreateTimetable::ThreadedCreateTimetable(QObject *parent) :
    QThread(parent)
{
    Q_UNUSED(parent)
}

void ThreadedCreateTimetable::run()
{
    double empCount = employees.count();
    double dayCount = startDate.daysTo(endDate);

    int empPerc = 0;
    int tPerc = 0;
    double daysSoFar = 0;

    double totalDays  = empCount * dayCount;

    for (double e = 0; e < empCount; e++) {
        QString empID = employees.at(e);
        QString employeeName = Publics::getDbValue(db, "SELECT Name FROM vw_employeenames WHERE employeeID = '" + empID + "'", "Name");
        emit employeeChanged(employeeName);

        for (double d = 0; d < dayCount; d++) {
            daysSoFar = daysSoFar + 1;
            QDate tD = startDate.addDays(d);
            emit dateChanged(tD.toString("dd-MMM-yyyy"));
            HourCalculator::CreateEmployeeTimetable(tD, empID, shiftID, db);

            empPerc = ( (d + 1) / dayCount  ) * 100;
            emit employeeProgress(empPerc);

            tPerc = ( daysSoFar / totalDays ) * 100;
            emit totalProgress(tPerc);
        }
    }
}

void ThreadedCreateTimetable::setVars(QStringList e, QDate sD, QDate eD, QString sID, QSqlDatabase d)
{
    employees = e;
    db = d;
    startDate = sD;
    endDate = eD;
    shiftID = sID;
}
