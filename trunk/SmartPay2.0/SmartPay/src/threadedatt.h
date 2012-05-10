#ifndef THREADEDATT_H
#define THREADEDATT_H

#include <QtSql>
#include <QThread>


class ThreadedAtt : public QThread
{
    Q_OBJECT
public:
    explicit ThreadedAtt(QObject *parent = 0);
    ~ThreadedAtt();
    void run();
    QSqlDatabase db;
    QStringList employees;
    QDate startDate;
    QDate endDate;
    int perc;

    void setVars(QSqlDatabase d, QStringList e, QDate sD, QDate eD, int p);

signals:
    void showPercentage(int p);

};

#endif // THREADEDATT_H
