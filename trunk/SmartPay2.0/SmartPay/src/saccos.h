#ifndef SACCOS_H
#define SACCOS_H

#include <QtGui>
#include <QtSql>



namespace Ui {
class Saccos;
}

class Saccos : public QWidget
{
    Q_OBJECT
    
public:
    explicit Saccos(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Saccos();
    QString currentID;
private slots:
    void on_SaveAndNew_clicked();

    void on_Save_clicked();

    void on_Delete_clicked();

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::Saccos *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
    bool isAdding;
    void reload();
    void clearTexts();
};

#endif // SACCOS_H
