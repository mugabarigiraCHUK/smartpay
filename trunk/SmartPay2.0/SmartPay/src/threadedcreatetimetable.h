#ifndef THREADEDCREATETIMETABLE_H
#define THREADEDCREATETIMETABLE_H

#include <QThread>
#include <QtSql>
#include <QDate>

class ThreadedCreateTimetable : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedCreateTimetable(QObject *parent = 0);
    void run();
    void setVars(QStringList e, QDate sD, QDate eD, QString sID, QSqlDatabase d = QSqlDatabase());
private:
    QStringList employees;
    QDate startDate;
    QDate endDate;
    QString shiftID;
    QSqlDatabase db;
signals:
    void employeeChanged(QString employeeName);
    void dateChanged(QString date);
    void employeeProgress(int p);
    void totalProgress(int p);
public slots:
    
};

#endif // THREADEDCREATETIMETABLE_H
