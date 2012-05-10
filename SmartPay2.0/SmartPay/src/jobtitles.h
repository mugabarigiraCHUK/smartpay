#ifndef JOBTITLES_H
#define JOBTITLES_H

#include <QWidget>
#include <QtSql>
#include <QtGui>
namespace Ui {
class JobTitles;
}

class JobTitles : public QWidget
{
    Q_OBJECT
    
public:
    explicit JobTitles(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~JobTitles();
    
private slots:
    void on_cmdAddNew_clicked();

    void on_cmdSave_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_cmdDelete_clicked();

private:
    Ui::JobTitles   *ui;
    QSqlDatabase    db;
    void            reload();
    bool            isAdding;
    void            clearTexts();
    QSqlQueryModel  *model;
    QString         currentID;
};

#endif // JOBTITLES_H
