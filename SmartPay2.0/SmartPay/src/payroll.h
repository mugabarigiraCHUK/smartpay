#ifndef PAYROLL_H
#define PAYROLL_H

#include <QtGui>
#include <QtSql>

namespace Ui {
class Payroll;
}


class Payroll : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Payroll(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Payroll();
    
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Recalculate_clicked();

private:
    Ui::Payroll *ui;
    QSqlDatabase db;
    void reloadMonths();
    QSqlQueryModel *model;
    QSortFilterProxyModel *fModel;
    QString monthID;
    void loadPayroll();
};

#endif // PAYROLL_H
