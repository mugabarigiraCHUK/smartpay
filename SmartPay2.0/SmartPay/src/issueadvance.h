#ifndef ISSUEADVANCE_H
#define ISSUEADVANCE_H

#include <QDialog>
#include <QWidget>
#include <QtSql>
#include <QtGui>

namespace Ui {
class IssueAdvance;
}

class IssueAdvance : public QDialog
{
    Q_OBJECT
    
public:
    explicit IssueAdvance(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), int employeeID =  0);
    ~IssueAdvance();
    
private slots:
    void on_cancelButton_clicked();

    void on_IssueButton_clicked();

private:
    Ui::IssueAdvance *ui;
    QSqlDatabase db;
    int id;
};

#endif // ISSUEADVANCE_H
