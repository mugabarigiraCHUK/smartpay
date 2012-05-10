#ifndef DEPARTMENTS_H
#define DEPARTMENTS_H

#include <QtGui>
#include <QtSql>

namespace Ui {
class Departments;
}

class Departments : public QWidget
{
    Q_OBJECT
    
public:
    explicit Departments(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Departments();
    
private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_cmdAddNew_clicked();

    void on_cmdSave_clicked();

    void on_cmdSetDepartmenytHead_clicked();

    void on_cmdDelete_clicked();

private:
    Ui::Departments *ui;
    QSqlDatabase    db;
    void            reloadDepartmentList();
    bool            isAdding;
    void            clearTexts();
    QSqlQueryModel  *model;
    QString         currentID;
    QString         headID;
};

#endif // DEPARTMENTS_H
