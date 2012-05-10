#include "hourcalculator.h"
#include "publics.h"
HourCalculator::HourCalculator()
{
}

void HourCalculator::RecalculateEmployeeHours(QString employeeID, QString monthID, QSqlDatabase db)
{
    QString startDate = Publics::getDbValue(db, "SELECT StartDate FROM months WHERE MonthID = '" + monthID + "'", "StartDate");
    QString endDate = Publics::getDbValue(db, "SELECT EndDate FROM months WHERE MonthID = '" + monthID + "'", "StartDate");
    RecalculateEmployeeHours(employeeID, startDate, endDate, db);
}

void HourCalculator::RecalculateEmployeeHours(QString employeeID, QString startDate, QString endDate, QSqlDatabase db)
{
    //Loop through each day of the period, and recalculate
    //qDebug() << employeeID << startDate << endDate;
    int days = QDate::fromString(startDate, "yyyy-MM-dd").daysTo(QDate::fromString(endDate, "yyyy-MM-dd").addDays(1));
    for (int i = 0; i < days; i++) {
        //qDebug() << i;
        QDate d_dat = QDate::fromString(startDate, "yyyy-MM-dd").addDays(i);
        QString dat = Publics::getDateString(d_dat);
        CalculateAttendanceForDay(dat, employeeID, db);
    }
}

void HourCalculator::CalculateAttendanceForDay(QString date, QString employeeID, QSqlDatabase db)
{
    db.exec("DELETE FROM employees_attendance_ex WHERE `Date` = '" + date + "' AND `EmployeeID` = '" + employeeID + "'");
    if (db.lastError().isValid())
        qWarning() << db.lastError().text();

    //Get the shift id for this employee for this date
    QString shiftID = Publics::getDbValue(db, "SELECT ShiftID FROM employees_timetable WHERE Date = '" + date + "' AND EmployeeID = '" + employeeID  + "'", "ShiftID");
    QString shiftName = Publics::getDbValue(db, "SELECT * FROM Shifts WHERE ShiftID = '" + shiftID  + "'", "ShiftName");
    //Get the shift details
    QSqlQuery qu = db.exec("SELECT * FROM shifts WHERE ShiftID = '" + shiftID + "'");
    QString shiftStartTime = "07:30:00";
    QString shiftEndTime = "16:00:00";

    while (qu.next()) {
        shiftStartTime = qu.record().value("StartTime").toString();
        shiftEndTime = qu.record().value("EndTime").toString();
    }

    QTime t_shiftStartTime = QTime::fromString(shiftStartTime, "hh:mm:ss");
    QTime t_shiftEndTime = QTime::fromString(shiftEndTime, "hh:mm:ss");

    Q_UNUSED(t_shiftEndTime);

    //Get all clock ins/outs for this date for this employee
    QSqlQuery qu2 = db.exec("SELECT * FROM employees_attendance WHERE EmployeeID = '" + employeeID + "' AND Date = '" + date +"'");
    if (qu2.size() > 0) {
        QString clockIn = "00:00:00";
        QString clockOut = "00:00:00";
        while (qu2.next()) {
            QString tim = qu2.record().value("Time").toString();
            QTime t_clockTime = QTime::fromString(tim, "hh:mm:ss");
            if (shiftName.contains("Saturday")) {
                //Saturday shift
                if (t_clockTime < QTime::fromString("11:00:00", "hh:mm:ss"))
                    clockIn = tim;

                if (t_clockTime > QTime::fromString("11:00:00", "hh:mm:ss"))
                    clockOut = tim;
            } else if (shiftName.contains("Night")) {
                //Night shift
                if (t_clockTime < QTime::fromString("19:00:00", "hh:mm:ss")) {
                    clockIn = tim;
                    //Get clock out from following day.
                }
                if (t_clockTime > QTime::fromString("04:00:00", "hh:mm:ss") && t_clockTime < QTime::fromString("12:00:00", "hh:mm:ss"))
                    clockOut = tim;
            } else if (t_shiftStartTime < QTime::fromString("13:00:00", "hh:mm:ss")) {
                //Shift starts in the morning
                if (t_clockTime < QTime::fromString("15:00:00", "hh:mm:ss"))
                    clockIn = tim;

                if (t_clockTime > QTime::fromString("15:00:00", "hh:mm:ss"))
                    clockOut = tim;
            } else {
                //Shift starts in the evening
                if (t_clockTime < QTime::fromString("23:00:00", "hh:mm:ss"))
                    clockIn = tim;

                if (t_clockTime > QTime::fromString("01:00:00", "hh:mm:ss"))
                    clockOut = tim;
            }
        }

        if (clockIn == "00:00:00")
            clockIn = shiftStartTime;

        if (clockOut == "00:00:00")
            clockOut = shiftEndTime;

        int earlyMinutes = 0;
        int lateMinutes = 0;
        int earlyExitMinutes = 0;
        int overtimeMinutes = 0;

        QTime cIn = QTime::fromString(clockIn, "hh:mm:ss");
        QTime cOut = QTime::fromString(clockOut, "hh:mm:ss");
        QTime sIn = QTime::fromString(shiftStartTime, "hh:mm:ss");
        QTime sOut = QTime::fromString(shiftEndTime, "hh:mm:ss");

        earlyMinutes = cIn.secsTo(sIn) / 60;
        lateMinutes = sIn.secsTo(cIn) / 60;
        earlyExitMinutes = cOut.secsTo(sOut) /  60;
        overtimeMinutes = sOut.secsTo(cOut) / 60;

        if (earlyMinutes < 0)
            earlyMinutes = 0;

        if (lateMinutes < 0)
            lateMinutes = 0;

        if (earlyExitMinutes < 0)
            earlyExitMinutes = 0;

        if (overtimeMinutes < 0)
            overtimeMinutes = 0;

        db.exec("INSERT INTO employees_attendance_ex (EmployeeID, Date, ShiftID, "
                "ShiftStartTime, ClockIn, ShiftEndTime, "
                "EarlyMinutes, LateMinutes, EarlyExit, Overtime, "
                " ClockOut) VALUES ('" +
                employeeID + "', '" +
                date + "', '" +
                shiftID + "', '" +
                shiftStartTime + "', '" +
                clockIn + "', '" +
                shiftEndTime + "', '" +
                QString::number(earlyMinutes) + "', '" +
                QString::number(lateMinutes) + "', '" +
                QString::number(earlyExitMinutes) + "', '" +
                QString::number(overtimeMinutes) + "', '" +
                clockOut + "')");
    }

}

void HourCalculator::CreateEmployeeTimetable(QDate date, QString employeeID, QString shiftID, QSqlDatabase db)
{
    QDate tD = date;
    QSqlQuery shiftsQu = db.exec("SELECT * FROM shifts WHERE ShiftID = '" + shiftID + "'");
    shiftsQu.next();
    QSqlRecord rec = shiftsQu.record();
    bool isDayValid = false;
    int d = tD.dayOfWeek();

    if (d == Qt::Monday && rec.value("Monday") == "Yes")
        isDayValid = true;

    if (d == Qt::Tuesday && rec.value("Tuesday") == "Yes")
        isDayValid = true;

    if (d == Qt::Wednesday && rec.value("Wednesday") == "Yes")
        isDayValid = true;

    if (d == Qt::Thursday && rec.value("Thursday") == "Yes")
        isDayValid = true;

    if (d == Qt::Friday && rec.value("Friday") == "Yes")
        isDayValid = true;

    if (d == Qt::Saturday && rec.value("Saturday") == "Yes")
        isDayValid = true;

    if (d == Qt::Sunday && rec.value("Sunday") == "Yes")
        isDayValid = true;

    if (isDayValid) {
        QString s_tD = tD.toString("yyyy-MM-dd");
        db.exec("DELETE FROM employees_timetable WHERE EmployeeID = '" + employeeID + "' AND Date = '" + s_tD + "'");
        db.exec("INSERT INTO employees_timetable (EmployeeID, ShiftID, Date) VALUES ('" + employeeID + "', '" + shiftID + "', '" + s_tD + "')");
    }

}
