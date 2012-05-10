#ifndef PAYROLLMONTHS_H
#define PAYROLLMONTHS_H

#include <QtGui>
#include <QWidget>
#include <QtSql>

namespace Ui {
class PayrollMonths;
}

class PayrollMonths : public QWidget
{
    Q_OBJECT
    
public:
    explicit PayrollMonths(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~PayrollMonths();
    
private slots:
    void on_cmdAddNew_clicked();

    void on_cmdSave_clicked();

    void on_cmdDelete_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::PayrollMonths *ui;
    QSqlDatabase db;
    void            reload();
    bool            isAdding;
    void            clearTexts();
    QSqlQueryModel  *model;
    QString         currentID;

};

#endif // PAYROLLMONTHS_H
