#ifndef CREATETIMETABLE_H
#define CREATETIMETABLE_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class CreateTimetable;
}

class CreateTimetable : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateTimetable(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CreateTimetable();
    
private slots:
    void on_CreateTimetableButton_clicked();
    void threadFinished();
    void on_SelectAll_clicked();

    void on_SelectNone_clicked();

private:
    Ui::CreateTimetable *ui;
    QSqlDatabase db;
    void reloadShifts();
    void reloadEmployees();
};

#endif // CREATETIMETABLE_H
