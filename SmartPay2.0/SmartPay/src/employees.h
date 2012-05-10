#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <QMainWindow>
#include <QtSql>
#include <QtGui>
namespace Ui {
class Employees;
}

class Employees : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Employees(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Employees();
    void hideFinance();
    void hideHR();
private slots:
    void on_actionAdd_New_triggered();
    void on_actionSave_triggered();
    void on_treeView_clicked(const QModelIndex &index);
    void on_actionIssue_Advance_triggered();
    void on_AddAdvance_clicked();
    void on_DeleteAdvance_clicked();
    void on_NewSacco_clicked();
    void on_SaveSacco_clicked();
    void on_RemoveSacco_clicked();
    void on_SaccoTree_clicked(const QModelIndex &index);

    void on_actionDeactivate_triggered();

    void on_ShowInactive_toggled(bool checked);

private:
    Ui::Employees   *ui;
    QSqlDatabase    db;
    bool            isAdding;
    void            reload();
    QString currentID;
    QSqlQueryModel *model;
    QSortFilterProxyModel *f_model;

    QSqlQueryModel *advancesModel;
    void reloadTrees();
    void reloadAdvances();
    void reloadSaccos();
    void loadSaccoList();

    void clearLineEdits(QObject *parent);
    void clearTexts();
    void loadCombos();

    bool isAclick;

    bool isSaccoAdding;
    QString currentSaccoID;
    QSqlQueryModel *saccoModel;


public slots:
    void edit(QString employeeID);
    void addNew(QString employeeNo);
    bool saveChanges(QString err = QString());
};

#endif // EMPLOYEES_H
