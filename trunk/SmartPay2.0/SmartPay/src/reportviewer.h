#ifndef REPORTVIEWER_H
#define REPORTVIEWER_H

#include <QtGui>
#include <QMap>
#include <QPrintPreviewWidget>
#include <QtSql>
#include <QtXml>
#include <QPrinter>


namespace Ui {
class ReportViewer;
}
class ORPreRender;
class ORODocument;
class ReportViewer : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReportViewer(QWidget *parent = 0, QSqlDatabase database  = QSqlDatabase());
    ~ReportViewer();
    void loadReport(QString reportName, QString param_where);
    QSqlDatabase db;
private:
    Ui::ReportViewer *ui;
    QString m_reportName;
    QString m_param_where;
    QPrinter *printer;
    ORODocument *oDoc;

private slots:
    void paintRequested(QPrinter* p);
    void print();
    void pageSetup();
    void generatePDF();
    void reportChanged();
    void FirstPage();
    void PreviousPage();
    void NextPage();
    void LastPage();

    void on_savePDF_clicked();

protected:
    QMap<QString, QList<QPair<QString,QString> > > _lists;
    QDomDocument _doc;
    QMap<QString, QVariant> _params;
};

#endif // REPORTVIEWER_H
