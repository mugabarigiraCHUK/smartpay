#ifndef RECALCULATEATTENDANCE_H
#define RECALCULATEATTENDANCE_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class RecalculateAttendance;
}

class RecalculateAttendance : public QDialog
{
    Q_OBJECT
    
public:
    explicit RecalculateAttendance(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~RecalculateAttendance();
    
private slots:
    void on_SelectAll_clicked();

    void on_SelectNone_clicked();

    void on_Recalculate_clicked();

private:
    Ui::RecalculateAttendance *ui;
    void loadEmployees();
    QSqlDatabase db;
};

#endif // RECALCULATEATTENDANCE_H
