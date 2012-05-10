#ifndef THREADEDATTENDANCECALC_H
#define THREADEDATTENDANCECALC_H

#include <QThread>
#include <QtSql>
class ThreadedAttendanceCalc : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedAttendanceCalc(QObject *parent = 0);
    void run();
    QSqlDatabase db;
    QStringList employees;
    QDate startDate;
    QDate endDate;
    int perc;

    void setVars(QSqlDatabase d, QStringList e, QDate sD, QDate eD, int p);

signals:
    void showPercentage(int p);
    void showEmployeePercentage(int p);
    void employeeChanged(QString eName);
    void dateChanged(QString date);
public slots:
    
};

#endif // THREADEDATTENDANCECALC_H
