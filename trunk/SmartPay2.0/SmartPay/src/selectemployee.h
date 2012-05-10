#ifndef SELECTEMPLOYEE_H
#define SELECTEMPLOYEE_H

#include <QtGui>
#include <QtSql>

namespace Ui {
class SelectEmployee;
}

class SelectEmployee : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectEmployee(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~SelectEmployee();
    QString selectedEmployeeName;
    QString selectedEmployeeID;
private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::SelectEmployee *ui;
};

#endif // SELECTEMPLOYEE_H
