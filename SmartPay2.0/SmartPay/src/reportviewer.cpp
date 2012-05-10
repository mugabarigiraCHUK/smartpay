#include "reportviewer.h"
#include "ui_reportviewer.h"

#include <QMessageBox>
#include <QInputDialog>


#include <QPrintDialog>
#include <QPrintPreviewDialog>

#include "renderobjects.h"
#include "openreports.h"
#include "orprerender.h"
#include "orprintrender.h"
#include "parameterproperties.h"
#include "data.h"
#include "parsexmlutils.h"
#include "paramlistedit.h"
#include "previewdialog.h"
#include "builtinSqlFunctions.h"

#include <QFile>
#include <QFileInfo>

ReportViewer::ReportViewer(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::ReportViewer)
{
    ui->setupUi(this);
    db = database;

    connect (ui->zoomIn, SIGNAL(clicked()), ui->widget, SLOT(zoomIn()));
    connect (ui->zoomOut, SIGNAL(clicked()), ui->widget, SLOT(zoomOut()));

    connect (ui->print, SIGNAL(clicked()), SLOT(print()));
    connect (ui->pageSetup, SIGNAL(clicked()), SLOT(pageSetup()));
    connect (ui->savePDF, SIGNAL(clicked()), SLOT(generatePDF()));

    connect (ui->widget, SIGNAL(previewChanged()), SLOT(reportChanged()));

    connect (ui->FirstPage, SIGNAL(clicked()), SLOT(FirstPage()));
    connect (ui->PreviousPage, SIGNAL(clicked()), SLOT(PreviousPage()));
    connect (ui->NextPage, SIGNAL(clicked()), SLOT(NextPage()));
    connect (ui->LastPage, SIGNAL(clicked()), SLOT(LastPage()));

    ui->FirstPage->setEnabled(false);
    ui->LastPage->setEnabled(false);
    ui->PreviousPage->setEnabled(false);
    ui->NextPage->setEnabled(false);

    QFile fil(QDir::tempPath() + QDir::separator() + "tmp.pdf");
    if (fil.open(QIODevice::ReadWrite))
    {
        fil.write("test");
        fil.close();
        QFileInfo inf(QDir::tempPath() + QDir::separator() + "tmp.pdf");
        QFileIconProvider ic;
        ui->savePDF->setIcon(ic.icon(inf));
    }

}

ReportViewer::~ReportViewer()
{
    delete ui;
}

void ReportViewer::loadReport(QString reportName, QString param_where)
{
    m_reportName = reportName;
    m_param_where = param_where;

    QSqlQuery rq = db.exec("SELECT * FROM report WHERE report_name= '" + reportName + "' ORDER BY report_grade DESC");

    if (rq.lastError().isValid()) {
        QMessageBox::critical(this, "Report Error", "Database Error\n" + rq.lastError().text());
        return;
    }
    rq.first();

    QDomDocument doc;

    QString errMsg;
    int errLine, errColm;
    QString reportContent = rq.record().value("report_source").toString();

    reportContent.replace("param_where", m_param_where);

    //QMessageBox::information(this, "", reportQuery);

    if (!doc.setContent(reportContent, &errMsg, &errLine, &errColm))
    {
        QMessageBox::critical(this, tr("Error Loading Report"),
                              tr("There was an error opening the report %1."
                                 "\n\n%2 on line %3 column %4.")
                              .arg(reportName).arg(errMsg).arg(errLine).arg(errColm) );
        return;
    }



    QDomElement root = doc.documentElement();
    if (root.tagName() != "report") {
        QMessageBox::critical(this, tr("Not a valid file"),
                              tr("The file %1 does not appear to ba a valid file"
                                 "\n\nThe root node is not 'report'.").arg(reportName));
        return;
    }

    _doc = doc;

    connect (ui->widget, SIGNAL(paintRequested(QPrinter*)), SLOT(paintRequested(QPrinter*)));
    ui->widget->updatePreview();
    ui->widget->fitInView();
}

void ReportViewer::paintRequested(QPrinter *p)
{
    ORPreRender pre;
    pre.setDatabase(db);
    pre.setDom(_doc);

    oDoc = pre.generate();
    if (oDoc) {
        ORPrintRender render;
        render.setPrinter(p);
        render.render(oDoc);
        render.setupPrinter(oDoc, p);

        ui->widget->setCurrentPage(1);
    }
}


void ReportViewer::print()
{
    QPrintDialog *d = new QPrintDialog(printer, this);
    if (d->exec() == QDialog::Accepted) {
        ui->widget->print();
        qDebug() << "Printed";
    }
}

void ReportViewer::pageSetup()
{
    QPageSetupDialog *pgSetup = new QPageSetupDialog(printer, this);
    if (pgSetup->exec() == QDialog::Accepted)
        ui->widget->updatePreview();
}

void ReportViewer::generatePDF()
{

}

void ReportViewer::reportChanged()
{
    ui->PageLabel->setText(tr("Page %1 of %2").arg(QString::number(ui->widget->currentPage()), QString::number(ui->widget->pageCount())));

    ui->FirstPage->setEnabled(false);
    ui->LastPage->setEnabled(false);
    ui->PreviousPage->setEnabled(false);
    ui->NextPage->setEnabled(false);

    if (ui->widget->currentPage() > 1) {
        ui->FirstPage->setEnabled(true);
        ui->PreviousPage->setEnabled(true);
    }

    if (ui->widget->currentPage() < ui->widget->pageCount()) {
        ui->NextPage->setEnabled(true);
        ui->LastPage->setEnabled(true);
    }
}

void ReportViewer::FirstPage()
{
    ui->widget->setCurrentPage(1);
    reportChanged();
}

void ReportViewer::PreviousPage()
{
    if (ui->widget->currentPage() > 1)
        ui->widget->setCurrentPage(ui->widget->currentPage() - 1);
    reportChanged();
}

void ReportViewer::NextPage()
{
    if (ui->widget->currentPage() < ui->widget->pageCount())
        ui->widget->setCurrentPage(ui->widget->currentPage() + 1);
    reportChanged();
}

void ReportViewer::LastPage()
{
    ui->widget->setCurrentPage(ui->widget->pageCount());
    reportChanged();
}

void ReportViewer::on_savePDF_clicked()
{
    QString pdfFileName = QFileDialog::getSaveFileName(this, "Select PDF File Name", QDir::currentPath(), "PDF Files (*.pdf)");
    if (!pdfFileName.isEmpty()) {
        ORPreRender pre;
        pre.setDatabase(db);
        pre.setDom(_doc);

        oDoc = pre.generate();
        if (oDoc) {
            ORPrintRender render;
            render.setPrinter(printer);
            render.render(oDoc);
            render.exportToPDF(oDoc, pdfFileName);
        }
    }
}
