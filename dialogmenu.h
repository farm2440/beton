#ifndef DIALOGMENU_H
#define DIALOGMENU_H

#include <QDialog>
#include <QProgressDialog>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QDir>
#include <QTextCodec>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <math.h>

#include "beton.h"
#include "dialogdatetime.h"
#include "dialogrecepti.h"
#include "dialogselectfile.h"
#include "dialogreport.h"
#include "gpio.h"

#include "beton.h"

#ifdef TAKE_SCREENSHOTS
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>
#endif

extern RecepieStruct currentRecepie;
extern GlobalStateStruct states;
extern GlobalSettingsStruct globals;

namespace Ui {
    class DialogMenu;
}

extern QSqlDatabase logDB;

class DialogMenu : public QDialog {
    Q_OBJECT
public:
    DialogMenu(QWidget *parent = 0);
    ~DialogMenu();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogMenu *ui;
    QTimer clockTimer; //таймер за обновяване на часовника
    bool humidityChanged; // флаг който се вдига ако се промени влажност на материалите

//    QSqlDatabase logDB;
private slots:
    void exitMenu();
    void setDateTime();
    void loadRecipies();
    void saveRecepies();
    void clockTick(); //Date/Time update
    void Report();

    void onHumiditySandUp();
    void onHumidityFractionUp();
    void onHumiditySandDown();
    void onHumidityFractionDown();
    void onDumpTimeUp();
    void onDumpTimeDown();

    void onSandAdvUp();
    void onSandAdvDwn();

    void onFractAdvUp();
    void onFractAdvDwn();

    void onCementAdvUp();
    void onCementAdvDwn();

    void onPepelAdvUp();
    void onPepelAdvDwn();

    void beep();
    void onAbort();

#ifdef TAKE_SCREENSHOTS
    void takeScreenShot();
#endif
};

#endif // DIALOGMENU_H
