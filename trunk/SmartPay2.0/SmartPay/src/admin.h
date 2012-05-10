#ifndef ADMIN_H
#define ADMIN_H

#include <QtGui>
#include <QtSql>
#include <QMainWindow>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Admin(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Admin();
    
private slots:
    void on_SaveAndNew_clicked();

    void on_SaveChanges_clicked();

    void on_Delete_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::Admin *ui;
    QSqlDatabase db;
    void loadUsers();
    QSqlQueryModel *model;
    void clearTexts();
    bool isAdding;
    QString currentID;
};

#endif // ADMIN_H
