#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QtSql>
#include <QMainWindow>

namespace Ui {
class Timetable;
}

class Timetable : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Timetable(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Timetable();
    
private slots:
    void on_CreateTimetable_clicked();

    void on_ViewEmployees_clicked();

private:
    Ui::Timetable *ui;
    QSqlDatabase db;
    void reloadShifts();
    void reloadTimeTable();
};

#endif // TIMETABLE_H
