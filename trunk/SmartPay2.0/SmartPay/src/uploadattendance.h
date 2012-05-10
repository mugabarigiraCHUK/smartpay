#ifndef UPLOADATTENDANCE_H
#define UPLOADATTENDANCE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class UploadAttendance;
}

class UploadAttendance : public QDialog
{
    Q_OBJECT
    
public:
    explicit UploadAttendance(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~UploadAttendance();
    
private slots:
    void on_Close_clicked();

    void on_StartUpload_clicked();

private:
    Ui::UploadAttendance *ui;
    QSqlDatabase db;
};

#endif // UPLOADATTENDANCE_H
