#ifndef DIALOGREPORT_H
#define DIALOGREPORT_H

#include <QDialog>
#include <QSqlQuery>
#include <QTextCodec>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QProgressDialog>
#include <QFile>
#include <QDate>
#include <QTime>

#include "gpio.h"

#include "beton.h"

#ifdef TAKE_SCREENSHOTS
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>
#endif


namespace Ui {
    class DialogReport;
}

class DialogReport : public QDialog {
    Q_OBJECT
public:
    DialogReport(QWidget *parent = 0);
    ~DialogReport();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogReport *ui;

    bool showReport;
    QString table;

private slots:
    void onSave();
    void onShowReport();
    void onExit();

    void beep();

#ifdef TAKE_SCREENSHOTS
    void takeScreenShot();
#endif
};

#endif // DIALOGREPORT_H
