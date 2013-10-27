#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QImage>
#include <QColorGroup>
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPalette>

#include <qdebug.h>

#include "beton.h"
#include "dialogmenu.h"
#include "dialogselectconcrete.h"
#include "dialogchangeingradients.h"
#include "serialport.h"
#include "scale.h"
#include "gpio.h"
#include "modbus.h"
#include "iniparser.h"

#ifdef TAKE_SCREENSHOTS
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>
#endif

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    int repeatValve; //В последния цикъл тази променлива се ползва във фази 3 и 4 за да може да се изчака клапата два пъти да
        //се отвори и затвори защото материалите за последното бъркало се зареждат преди да е разтоварено предпоследното.

//Animation
    QImage imgWheel[8];
    QImage imgWater[8];
    QImage imgShnekH[7];

    QTimer tmrAnimate;
    int animationWheelCounter, animationShnekCounter;

//external devices
    Scale scaleSand, scaleFrac, scaleCement; //Везните

    modbus mb;
//database
//    QSqlDatabase clientsDB;
//Текущо избраната формула забетона е в тази структура
    FormulaConcrete formula;
//other
    QTimer cycleTimer; //таймер за основния цикъл на алгоритъма
    QTimer clockTimer; //таймер за обновяване на часовника
    GPIO *inPowerAC; //тук през GPIO се чете състоянието на АС захранването и в clockTick() му се прави проверка
    int shutdownCounter;//при достигане на 0 PIN34 на GPIO се сваля в 0. Той е вдигнат в 1 преди пускане на програмата от скрипт в /etc/init.d/rcS
    bool lastPowerState;

    int Phase;  //В тази променлива се записва число което показва в коя фаза на изпълнение е текущата заявка.
                //Всички решения по изпълнението се вземат във onCycleTimer() която се вика периодично от таймер който е
                //еднократен и се презапуска всеки път.
    ushort TwidoFlags; //Тук се пази думата с флаговете които се записват в twido MW7
    int MixLeft; //При стартиране на заявка в тази променлива се записва броя на бъркалата и с всяко бъркало намаля с 1
    bool _fPepeDose, _fSandDose, _fFracDose, _fCementDose; //помощни флагове които са критерии за излизане от фаза 0
    QByteArray resp; // Ползват се от функциите за връзка с twido
    QByteArray val;
private slots:
    void animation();
//Button slots
    void onMenu();
    void onChangeIngradients();
    void onSelectConcrete();
    void onStart();
//other
    void beep();

    void clockTick(); //Date/Time update
    void onCycleTimer();
    void finishCycle();  //Записва в БД данни за заявката. Нулира броячи и флагове.
//modbus test
    void onOpenMod();
    void onFunc3();
    void onFunc16a();
    void onFunc16b();

#ifdef TAKE_SCREENSHOTS
    void takeScreenShot();
#endif
};

#endif // MAINWINDOW_H
