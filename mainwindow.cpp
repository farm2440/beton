#include "mainwindow.h"
#include "ui_mainwindow.h"


/* globals е структура - глобални променливи част от които се зареждат от beton.ini и определя настройките */
GlobalSettingsStruct globals;
GlobalStateStruct states;
RecepieStruct currentRecepie;
QSqlDatabase logDB;

MainWindow::MainWindow(QWidget *parent) :    QMainWindow(parent),    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // *** -= КИРИЛИЗАЦИЯ !!! =- ***
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    //без курсор
    this->setCursor(QCursor(Qt::BlankCursor));
    this->showFullScreen();
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    qDebug() << "\n************************************************" ;
    qDebug() <<   "* beton project   v.1.0.1                      *" ;
    qDebug() <<   "* QtCreator 2.8.0                              *" ;
    qDebug() <<   "* Compiler: gcc-4.3.2                          *" ;
    qDebug() <<   "* QtVersion: Qt 4.6.3                          *" ;
    qDebug() <<   "* Platform: FriendlyARM mini2440               *" ;
    qDebug() <<   "************************************************\n" ;


    //зареждане на параметрите от beton.ini
    char * fn = new char[40];
    strcpy(fn,"/sdcard/beton.ini");
    dictionary *dict;
    dict = iniparser_load(fn);
    if(dict == NULL)
    {
        QMessageBox::information(this,"iniparser library",QString("Failed to load dictionary from beton.ini"));
    }
    globals.ShutdownTimeout = iniparser_getint(dict, QString("GLOBALS:ShutdownTimeout").toLatin1().data(), 10);
    globals.CoefVodomer = iniparser_getdouble(dict, QString("GLOBALS:CoefVodomer").toLatin1().data(), 3.38);

    globals.TwidoSerialPort = QString( iniparser_getstring(dict, QString("GLOBALS:TwidoSerialPort").toLatin1().data(), QString("/dev/ttyUSB1").toLatin1().data()) );
    globals.ScaleCementPort = QString( iniparser_getstring(dict, QString("GLOBALS:ScaleCementPort").toLatin1().data(), QString("/dev/ttyUSB0").toLatin1().data()) );
    globals.ScaleFractionPort = QString( iniparser_getstring(dict, QString("GLOBALS:ScaleFractionPort").toLatin1().data(), QString("/dev/ttySAC1").toLatin1().data()) );
    globals.ScaleSandPort = QString( iniparser_getstring(dict, QString("GLOBALS:ScaleSandPort").toLatin1().data(), QString("/dev/ttySAC2").toLatin1().data()) );

    //TODO: Да се зададат коректни стойности по подразбиране
    globals.MaxCement = iniparser_getint(dict, QString("GLOBALS:MaxCement").toLatin1().data(), 1000);
    globals.MinCement = iniparser_getint(dict, QString("GLOBALS:MinCement").toLatin1().data(), 0);
    globals.MaxFraction = iniparser_getint(dict, QString("GLOBALS:MaxFraction").toLatin1().data(), 1000);
    globals.MinFraction = iniparser_getint(dict, QString("GLOBALS:MinFraction").toLatin1().data(), 0);
    globals.MinWater = iniparser_getint(dict, QString("GLOBALS:MinWater").toLatin1().data(), 0);
    globals.MaxWater = iniparser_getint(dict, QString("GLOBALS:MaxWater").toLatin1().data(), 1000);
    globals.MaxPepelina = iniparser_getint(dict, QString("GLOBALS:MaxPepelina").toLatin1().data(), 1000);
    globals.MinPepelina = iniparser_getint(dict, QString("GLOBALS:MinPepelina").toLatin1().data(), 0);
    globals.MinSand = iniparser_getint(dict, QString("GLOBALS:MinSand").toLatin1().data(), 0);
    globals.MaxSand = iniparser_getint(dict, QString("GLOBALS:MaxSand").toLatin1().data(), 1000);
    globals.MinTime = iniparser_getint(dict, QString("GLOBALS:MinTime").toLatin1().data(), 5);
    globals.MaxTime = iniparser_getint(dict, QString("GLOBALS:MaxTime").toLatin1().data(), 15);
    globals.MixerVolume = iniparser_getdouble(dict, QString("GLOBALS:MixerVolume").toLatin1().data(), 0.7);
    globals.DumpTime = iniparser_getint(dict, QString("GLOBALS:DumpTime").toLatin1().data(),120);

    globals.AdvScaleCement = iniparser_getdouble(dict, QString("GLOBALS:AdvScaleCement").toLatin1().data(), 0.0);
    globals.AdvScaleSand = iniparser_getdouble(dict, QString("GLOBALS:AdvScaleSand").toLatin1().data(), 0.0);
    globals.AdvScaleFraction = iniparser_getdouble(dict, QString("GLOBALS:AdvScaleFraction").toLatin1().data(), 0.0);
    globals.AdvScalePepelina = iniparser_getdouble(dict, QString("GLOBALS:AdvScalePepelina").toLatin1().data(), 0.0);

    globals.MaxReadFails = iniparser_getint(dict, QString("GLOBALS:MaxReadFails").toLatin1().data(), 4);

    globals.CementLIV2multi = iniparser_getint(dict, QString("GLOBALS:CementLIV2multi").toLatin1().data(), 10);
    globals.CementLIV6multi = iniparser_getint(dict, QString("GLOBALS:CementLIV6multi").toLatin1().data(), 10);
    globals.SandLIV2multi = iniparser_getint(dict, QString("GLOBALS:SandLIV2multi").toLatin1().data(), 1);
    globals.FractionLIV2multi = iniparser_getint(dict, QString("GLOBALS:FractionLIV2multi").toLatin1().data(), 1);

    qDebug() << "\nDATA FROM BETON.INI:" ;
    qDebug() << "ShutdownTimeout=" << globals.ShutdownTimeout;
    qDebug() << "CoefVodomer=" << globals.CoefVodomer  << "\n" ;
    qDebug() << "ScaleCementPort=" << globals.ScaleCementPort ;
    qDebug() << "ScaleFractionPort=" << globals.ScaleFractionPort ;
    qDebug() << "ScaleSandPort=" << globals.ScaleSandPort ;
    qDebug() << "TwidoSerialPort=" << globals.TwidoSerialPort << "\n";

    qDebug() << "MaxCement=" << globals.MaxCement << "\t  MinCement=" << globals.MinCement ;
    qDebug() << "MaxFraction=" << globals.MaxFraction << " MinFraction=" << globals.MinFraction ;
    qDebug() << "MaxPepelina=" << globals.MaxPepelina << " MinPepelina=" << globals.MinPepelina;
    qDebug() << "MaxSand=" << globals.MaxSand << "\t  MinSand=" << globals.MinSand ;
    qDebug() << "MaxWater=" << globals.MaxWater << "\t  MinWater=" << globals.MinWater ;
    qDebug() << "MaxTime=" << globals.MaxTime << "\t  MinTime=" << globals.MinTime << "\n" ;

    qDebug() << "MixerVolume=" << globals.MixerVolume ;
    qDebug() << "DumpTime=" << globals.DumpTime << "\n";
    qDebug() << "AdvScaleCement=" << globals.AdvScaleCement << " AdvScaleSand=" << globals.AdvScaleSand << " AdvScaleFraction=" << globals.AdvScaleFraction << " AdvScalePepelina="<<  globals.AdvScalePepelina <<"\n";
    qDebug() << "MaxReadFails=" << globals.MaxReadFails << "\n";

    qDebug() << "SandLIV2multi=" << globals.SandLIV2multi;
    qDebug() << "FractionLIV2multi=" << globals.FractionLIV2multi;
    qDebug() << "CementLIV2multi=" << globals.CementLIV2multi;
    qDebug() << "CementLIV6multi=" << globals.CementLIV6multi << "\n";

    delete dict;
    //край зареждане на параметрите от beton.ini
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    //Инициализация на всичко касаещо анимацията
    animationShnekCounter=0;
    animationWheelCounter=0;
    //labels are used for displaying animated images
    ui->lblRotorStrip1->setBackgroundRole(QPalette::Base);
    ui->lblRotorStrip1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblRotorStrip1->setScaledContents(true);

    ui->lblRotorStrip2->setBackgroundRole(QPalette::Base);
    ui->lblRotorStrip2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblRotorStrip2->setScaledContents(true);

    ui->lblRotorTop->setBackgroundRole(QPalette::Base);
    ui->lblRotorTop->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblRotorTop->setScaledContents(true);

    ui->lblShnekMixer->setBackgroundRole(QPalette::Base);
    ui->lblShnekMixer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblShnekMixer->setScaledContents(true);

    ui->lblShnekH_1->setBackgroundRole(QPalette::Base);
    ui->lblShnekH_1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblShnekH_1->setScaledContents(true);

    ui->lblShnekH_2->setBackgroundRole(QPalette::Base);
    ui->lblShnekH_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblShnekH_2->setScaledContents(true);

    ui->lblWaterFlow->setBackgroundRole(QPalette::Base);
    ui->lblWaterFlow->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblWaterFlow->setScaledContents(true);

    //load images from resource file
    imgWheel[0] = QImage(":/res/wheel-0.png");
    imgWheel[1] = QImage(":/res/wheel-45.png");
    imgWheel[2] = QImage(":/res/wheel-90.png");
    imgWheel[3] = QImage(":/res/wheel-135.png");
    imgWheel[4] = QImage(":/res/wheel-180.png");
    imgWheel[5] = QImage(":/res/wheel-225.png");
    imgWheel[6] = QImage(":/res/wheel-270.png");
    imgWheel[7] = QImage(":/res/wheel-315.png");

    imgShnekH[0] = QImage(":/res/shnek-h-1.png");
    imgShnekH[1] = QImage(":/res/shnek-h-2.png");
    imgShnekH[2] = QImage(":/res/shnek-h-3.png");
    imgShnekH[3] = QImage(":/res/shnek-h-4.png");
    imgShnekH[4] = QImage(":/res/shnek-h-5.png");
    imgShnekH[5] = QImage(":/res/shnek-h-6.png");
    imgShnekH[6] = QImage(":/res/shnek-h-7.png");

    imgWater[0] = QImage(":/res/waterV0.png");
    imgWater[1] = QImage(":/res/waterV1.png");
    imgWater[2] = QImage(":/res/waterV2.png");
    imgWater[3] = QImage(":/res/waterV3.png");
    imgWater[4] = QImage(":/res/waterV4.png");
    imgWater[5] = QImage(":/res/waterV5.png");
    imgWater[6] = QImage(":/res/waterV6.png");

    imgWater[7] = QImage(":/res/nowater.png");
    //set initial image
    ui->lblRotorStrip1->setPixmap(QPixmap::fromImage(imgWheel[4]));
    ui->lblRotorStrip2->setPixmap(QPixmap::fromImage(imgWheel[5]));
    ui->lblRotorTop->setPixmap(QPixmap::fromImage(imgWheel[6]));
    ui->lblShnekH_1->setPixmap(QPixmap::fromImage(imgShnekH[1]));
    ui->lblShnekH_2->setPixmap(QPixmap::fromImage(imgShnekH[2]));
    ui->lblShnekMixer->setPixmap(QPixmap::fromImage(imgShnekH[3]));

    //КРАЙ на инициализацията на анимацията
//---------------------------------------------------------------------------------------------------------------------------------------------------------
    //Етикети за авариен стоп, ръчен режим
    QPalette pal = ui->lblAutomaticMode->palette();
    pal.setColor(ui->lblPower->backgroundRole(),Qt::yellow);
    ui->lblAutomaticMode->setPalette(pal);
    ui->lblAutomaticMode->setAutoFillBackground(true);

    pal = ui->lblEmebrgencyStop->palette();
    pal.setColor(ui->lblEmebrgencyStop->backgroundRole(),Qt::red);
    ui->lblEmebrgencyStop->setPalette(pal);
    ui->lblEmebrgencyStop->setAutoFillBackground(true);

    pal = ui->lblShutdownCounter->palette();
    pal.setColor(ui->lblShutdownCounter->backgroundRole(),Qt::red);
    ui->lblShutdownCounter->setPalette(pal);
    ui->lblShutdownCounter->setAutoFillBackground(true);

    ui->lblCurrentRecepie->setText(tr("НЯМА ЗАЯВКА"));
    ui->lblProgess->setText("");

    //connect event handlers
    connect(ui->btnMenu,SIGNAL(clicked()),this,SLOT(onMenu()));
    connect(ui->btnChange,SIGNAL(clicked()),this,SLOT(onChangeIngradients()));
    connect(ui->btnSelectConcrete,SIGNAL(clicked()),this,SLOT(onSelectConcrete()));
    connect(ui->btnStart,SIGNAL(clicked()),this,SLOT(onStart()));

    //отваряне на базата данни
    QFile cdbFile("/sdcard/beton.db");
    if(!cdbFile.exists())
    {   QMessageBox::critical(this, tr("Грешка база данни"), tr("Файлът с БД не съществува"));
        beep();
        return;
    }
    else
    {   logDB = QSqlDatabase::addDatabase("QSQLITE"); //QSQLITE е за версия 3 и нагоре, QSQLITE2 e за версия 2
        logDB.setDatabaseName("/sdcard/beton.db");
        if(!logDB.open())
        {
            QMessageBox::critical(this, tr("Грешка база данни"), tr("Не мога да отворя БД"));
            beep();
            return;
        }
    }

    //инициализация на везните
    scaleSand.scale_Open(globals.ScaleSandPort, B9600, 8, SerialPort::PARITY_NONE, 1, Scale::SCALE_TYPE_WE2108, 800);
    if(scaleSand.scale_isOpen())    qDebug() << "Opened sand scale port ";
    else
    {   qDebug() << "ERROR! Failed to open sand scale serial port!";
        qDebug() << "Sand Scale ErrMessage:" << scaleSand.getErrMessage() << "\n";
    }

    scaleFrac.scale_Open(globals.ScaleFractionPort, B9600, 8, SerialPort::PARITY_NONE, 1, Scale::SCALE_TYPE_WE2108, 800);
    if(scaleFrac.scale_isOpen())    qDebug() << "Opened fraction scale port ";
    else
    {   qDebug() << "ERROR! Failed to open fraction scale serial port!";
        qDebug() << "Fraction Scale ErrMessage:" << scaleFrac.getErrMessage() << "\n";
    }

    scaleCement.scale_Open(globals.ScaleCementPort, B9600, 8, SerialPort::PARITY_NONE, 1, Scale::SCALE_TYPE_WE2108, 800);
    if(scaleCement.scale_isOpen())    qDebug() << "Opened cement scale port ";
    else
    {   qDebug() << "ERROR! Failed to open cement scale serial port!";
        qDebug() << "Cement Scale ErrMessage:" << scaleCement.getErrMessage() << "\n";
    }
    //край на инициализацията на везните

    //TWIDO
    bool res = mb.Open(globals.TwidoSerialPort,B19200,8,SerialPort::PARITY_NONE,1);
    if(res) qDebug() << "Modbus port opened.";
    else qDebug() << "ERROR: Failed to open modbus serial port!";

    //управление на захранването
    inPowerAC = new GPIO(PIN33);
    inPowerAC->openPin();
    inPowerAC->setDirection(GPIO::In);

    shutdownCounter = globals.ShutdownTimeout;
    lastPowerState = false;

    states.PrevState=states.State;
    states.State = Idle;
    qDebug() << "STATE:Idle";
    states.fCementWheel = false;
    states.fMixer = false;
    states.fShnek1 = false;
    states.fShnek2 = false;
    states.fWater = false;
    states.failCounter = 0;

    globals.HumidityFraction = 0.00;
    globals.HumiditySand = 0.00;
    currentRecepie.Name = "";

    TwidoFlags = 0;

    //Date/Time update
    connect(&clockTimer,SIGNAL(timeout()),this,SLOT(clockTick()));
    clockTimer.start(1000);

    //start animation timer
    connect(&tmrAnimate,SIGNAL(timeout()),this,SLOT(animation()));
    tmrAnimate.setInterval(150);
    tmrAnimate.start();

    //init cycle timer
    connect(&cycleTimer,SIGNAL(timeout()),this,SLOT(onCycleTimer()));
    cycleTimer.setSingleShot(true);
    cycleTimer.start(1000);
}

void MainWindow::animation()    //animation of rotors - called on tmrAnimate timeout
{
    if(states.fBelt)
    {    ui->lblRotorStrip1->setPixmap(QPixmap::fromImage(imgWheel[animationWheelCounter]));
        ui->lblRotorStrip2->setPixmap(QPixmap::fromImage(imgWheel[animationWheelCounter]));
    }
    if(states.fCementWheel) ui->lblRotorTop->setPixmap(QPixmap::fromImage(imgWheel[animationWheelCounter]));
    if(states.fMixer) ui->lblShnekMixer->setPixmap(QPixmap::fromImage(imgShnekH[animationShnekCounter]));
    if(states.fShnek1) ui->lblShnekH_1->setPixmap(QPixmap::fromImage(imgShnekH[6-animationShnekCounter])); //долния на картинката
    if(states.fShnek2) ui->lblShnekH_2->setPixmap(QPixmap::fromImage(imgShnekH[animationShnekCounter]));
    if(states.fWater) ui->lblWaterFlow->setPixmap(QPixmap::fromImage((imgWater[6-animationShnekCounter])));

    animationWheelCounter++;
    if(animationWheelCounter==8) animationWheelCounter=0;

    animationShnekCounter++;
    if(animationShnekCounter==7) animationShnekCounter=0;
}

/* Бутон "МЕНЮ" от главния екран */
void MainWindow::onMenu()
{
    beep();
    DialogMenu *dlgMenu;
    dlgMenu = new DialogMenu(this);
    dlgMenu->setCursor(Qt::BlankCursor);
    dlgMenu->setModal(true);
    dlgMenu->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog) ; //скривам рамката на диалоговия прозорец
    dlgMenu->exec(); //трябва да се ползва exec а не show за да се спре изпълнението докато се затвори диалога за да може да се освободи паметта с delete
    delete dlgMenu;
    qDebug() << "Exit Settings Menu:\n";
    qDebug() << "AdvScaleCement=" << globals.AdvScaleCement << " AdvScaleSand=" << globals.AdvScaleSand << " AdvScaleFraction=" << globals.AdvScaleFraction << " AdvScalePepelina="<<  globals.AdvScalePepelina <<"\n";
}

/* Бутон "КОРЕКЦИЯ" от главния екран */
void MainWindow::onChangeIngradients()
{
    beep();
    if(currentRecepie.Name=="")
    {
        QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Няма избрана рецепта."));
        beep();
        return;
    }

    DialogChangeIngradients *dlg = new DialogChangeIngradients(this);
    dlg->setCursor(Qt::BlankCursor);
    dlg->setModal(true);
    dlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog) ; //скривам рамката на диалоговия прозорец
    dlg->exec();
    delete dlg;
}

/* Бутон "ЗАЯВКА" от главния екран */
void MainWindow::onSelectConcrete()
{
#ifdef TAKE_SCREENSHOTS
    takeScreenShot();
#endif
    beep();
    DialogSelectConcrete *dlgSelCon;
    dlgSelCon = new DialogSelectConcrete(this);
    dlgSelCon->setCursor(Qt::BlankCursor);
    dlgSelCon->setModal(true);
    dlgSelCon->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog) ; //скривам рамката на диалоговия прозорец
    if(dlgSelCon->exec() == QDialog::Accepted) //трябва да се ползва exec а не show за да се спре изпълнението докато се затвори диалога за да може да се освободи паметта с delete
    {
        ui->lblCurrentRecepie->setText(tr("ЗАЯВКА ЗА ") + QString::number(currentRecepie.Quantity,'f',1) + tr("куб. БЕТОН \"") + currentRecepie.Name.toUpper() + "\" ");
        ui->lblProgess->setText("");
    }
    delete dlgSelCon;
}

/* Бутон "САТРТ" от главния екран */
void MainWindow::onStart()
{
    beep();

    switch(states.State)
    {
    case Idle: //старт на смесване
        if(currentRecepie.Name=="")
        {
            QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Няма избрана рецепта."));
            beep();
            return;
        }
        ui->btnSelectConcrete->setEnabled(false);
        ui->btnChange->setEnabled(false);
        ui->btnStart->setText(tr("ПАУЗА"));
        qDebug() << "STATE:Start";
        currentRecepie.SatrtTime =  QTime::currentTime(); //Време начало на изпълнение на заявката
        currentRecepie.StartDate = QDate::currentDate();
        states.failCounter=0;
        states.PrevState=states.State;
        states.State = Start; //при този режим в onCycleTimer ще се заредят нива във везната  и режима ще се смени на Run
                              //ako всичко е ОК. При проблем влиза във Fail.
        break;
    case Paused:
        //Излизаме от пауза и започваме работа
        ui->btnChange->setEnabled(false);
        ui->btnSelectConcrete->setEnabled(false);
        ui->btnStart->setText(tr("ПАУЗА"));
        states.failCounter=0;
        states.PrevState=states.State;
        states.State = Run;
        qDebug() << "STATE:Run" ;
        break;

    case Run:
        //От режим работа влизаме в пауза
        ui->btnChange->setEnabled(true); //когато смесването е в пауза за корекция е достъпна само водата
        ui->btnSelectConcrete->setEnabled(false);
        ui->btnStart->setText(tr("СТАРТ"));
        states.PrevState=states.State;
        states.State = Paused;
        qDebug() << "STATE:Paused";
        break;

    case Fail:
    case Abort:
    case Start:
    case PowerDown:
        break;

    }
}

void MainWindow::beep()
{
    QTime tme;
    GPIO *buzzer;
    buzzer = new GPIO(PIN31);
    buzzer->openPin();
    buzzer->setDirection(GPIO::Out);
    tme.restart();
    buzzer->setState(true);
    while(tme.elapsed()<25){qApp->processEvents();}
    buzzer->setState(false);
    buzzer->closePin();
    delete buzzer;
}

MainWindow::~MainWindow()
{
    delete ui;
    if(logDB.open()) logDB.close();
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/* Функцията се вика всяка секунда. Актуализира се дата/час.
   Проверява се входа за наличие на мрежово захранване. Ако липсва тече таймаут за гасене.
 */
void MainWindow::clockTick()
{
    QDate dt;
    QTime tm;
    tm=QTime::currentTime();
    dt=QDate::currentDate();
    ui->lblDateTime->setText(dt.toString() +"  " + tm.toString());

    //проверка за наличие на мрежово захранване
    bool powerState = inPowerAC->getState();
    if (powerState)
    {
        if(lastPowerState != powerState)
        {
            ui->lblPower->setText(tr(" ЗАХРАНВАНЕ 220В "));
            ui->lblShutdownCounter->setVisible(false);

            shutdownCounter = globals.ShutdownTimeout;
            QPalette pal = ui->lblPower->palette();
            pal.setColor(ui->lblPower->backgroundRole(),Qt::green);
            ui->lblPower->setPalette(pal);
            ui->lblPower->setAutoFillBackground(true);
        }
    }
    else
    {
        ui->lblPower->setText(QString(tr(" НЯМА ЗАХРАНВАНЕ ")));
        ui->lblShutdownCounter->setVisible(true);
        ui->lblShutdownCounter->setText(QString(tr("Изключване след %1")).arg(shutdownCounter));
        ui->lblShutdownCounter->adjustSize();

        qDebug() << "Power down! Shutdown in " << shutdownCounter << "seconds" ;
        QPalette pal = ui->lblPower->palette();
        pal.setColor(ui->lblPower->backgroundRole(),Qt::red);
        ui->lblPower->setPalette(pal);
        ui->lblPower->setAutoFillBackground(true);

        //Първо минаваме в състояние PowerDown за да се приключи цикъла в onCycleTimer
        if(shutdownCounter != 0)
        {
            shutdownCounter--;
            if(shutdownCounter == 0)
            {
                if(states.State==Idle)
                {
                    GPIO off(PIN34);
                    off.setState(false);
                    QProcess *proc = new QProcess(this);
                    qDebug() << "Shutdown!";
                    proc->start("shutdown");
                    while (true) {}
                }
                else
                {   states.PrevState=states.State;
                    states.State = PowerDown;
                }
            }
            beep();
        }
        if((shutdownCounter==0) && (states.State==Idle))
        {
            GPIO off(PIN34);
            off.setState(false);
            QProcess *proc = new QProcess(this);
            qDebug() << "Shutdown!";
            proc->start("shutdown");
            while (true) {}
        }
    }
    lastPowerState = powerState;
}

void MainWindow::onOpenMod()
{
    beep();
    bool res = mb.Open(globals.TwidoSerialPort,B19200,8,SerialPort::PARITY_NONE,1);
    if(res) qDebug() << "Modbus open." ;
    else qDebug() << "failed opening modbus!";
}

void MainWindow::onFunc3()
{
    /*
    //четене от TWIDO
    beep();
QByteArray resp;
    bool r = mb.SendFc3(1,0,5,resp);

    if(r) ui->textBrowser->append("Func 3 : ok");
    else
    {
        ui->textBrowser->append("Func3 fail!");
        return;
    }

  ushort crc = mb.GetCRC(resp);
  ui->textBrowser->append(QString("response is %1 bytes. CRC=%2").arg(resp.count()).arg((int)crc));
  if(mb.CheckResponse(resp)) ui->textBrowser->append("CRC check OK");
  else ui->textBrowser->append("CRC check fail");
  QString str;
  for(int i=0 ; i<resp.count() ; i++)
  {
    str += QString("%1 ").arg((int)resp[i]);
  }
  ui->textBrowser->append(str);*/
}

void MainWindow::onFunc16a()
{
    /*
    beep();
    int err;
    QByteArray val;
    val.resize(2);
    val[0]=0x00;
    val[1]=0x01;
    bool res = mb.SendFc16(1,2,1,val,err);
    if(res) ui->textBrowser->append("Func 16 : ok");
    else ui->textBrowser->append(QString("Func16 fail. err=%1").arg(err)); */
}

void MainWindow::onFunc16b()
{/*
    beep();
    int err;
    QByteArray val;
    val.resize(2);
    val[0]=0x00;
    val[1]=0x02;
    bool res = mb.SendFc16(1,2,1,val,err);
    if(res) ui->textBrowser->append("Func 16 : ok");
    else ui->textBrowser->append(QString("Func16 fail. err=%1").arg(err));*/
}

void MainWindow::onCycleTimer()
{
//Независимо от състоянието четем везните и ги изобразяваме
    //тест за везна
    bool ok;
    bool fail = false; //Ако поне едно четене не успее тази променлива става true и

    double w;
    static double tmp;
    int pulses; //брой импулси от водомера

    //Ако сме излезнали от пауза трябва да се нулира флага MW7.8 във Twido
    //При влизане в пауза в Twido се вдига MW7.8

    if((states.PrevState == Paused) && (states.State!=Paused))
    {
        //В TWIDO се нулира  флаг за пауза MW7.8
        TwidoFlags &= 0xFEFF;
        qDebug() << "Clear TWIDO pause flag MW7.8" << TwidoFlags;
        int retry = 5;
        int err;
        do
        {
            retry--;
            if(retry == 0)
            {//изчерпан е броя опити за запис
                states.PrevState=states.State;
                states.State = Fail;
                qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                qDebug() << "STATE:Fail";
                QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                beep();
                cycleTimer.start(800);
                return;
            }
            val.resize(2);
            val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
            val[1]= (uchar)(TwidoFlags & 0xFF);// L
            ok = mb.SendFc16(1,7,1,val,err);
        }while(!ok);
    }


    //----------------------------------------------------------------------------------------------------------------------------------
    //СЕКЦИЯ ЧЕТЕНЕ ОТ УСТРОЙСТВАТА - четат се везните и twdo. Определя се кои механизми се движат и се вдигат флаговете им за анимиране.
    //Ако има проблем с четене то се минава в състояние на грешка
    //пясък
    w = scaleSand.getWeight(ok);
    if(ok) ui->lcdSandScale->display(w);
    else
    {
        ui->lcdSandScale->display(8888);        
        if(states.State != Fail) qDebug() << "ERROR!: Failed reading sand scale. MSG:" << scaleSand.getErrMessage();
        fail=true;
    }
    //чакъл
    w = scaleFrac.getWeight(ok);
    if(ok) ui->lcdFractScale->display(w);
    else
    {
        ui->lcdFractScale->display(8888);
        if(states.State != Fail) qDebug() << "ERROR!: Failed reading fraction scale. MSG:" << scaleFrac.getErrMessage();
        fail = true;
    }
    //цимент
    w = scaleCement.getWeight(ok);
    if(ok) ui->lcdCementScale->display(w);
    else
    {
        ui->lcdCementScale->display(8888);
        if(states.State != Fail) qDebug() << "ERROR!: Failed reading cement scale. MSG:" << scaleCement.getErrMessage();
        fail = true;
    }

    //четене на водомер от TWIDO
    ok = mb.SendFc3(1,0,9,resp);
    if(ok && mb.CheckResponse(resp))
    {
        //байтове 17 и 18 са MW7 в която пиша
        //Извличат се стойности и флагове
        //Моментна стойност на водомера
        pulses = (((int)resp[15])<<8) + (int)resp[16];               
        w = ((double)pulses) / globals.CoefVodomer;
        ui->lcdWater->display(w);

        int ewp  = (((int)resp[19])<<8)+(int)resp[20];
        currentRecepie.ExpWater =((double)ewp) / globals.CoefVodomer;

//            qDebug() << "[3]=" << (int)resp[3] << " [4]=" << (int)resp[4] << " [5]=" << (int)resp[5] << " [6]=" << (int)resp[6]<< " [7]=" << (int)resp[7] << " [8]=" << (int)resp[8];
//        qDebug() << bin << "MW7: [18]=" << (int)resp[18] <<  " [17]=" << (int)resp[17] << dec;
        //флагове за достигнати дози
        if(resp[4] & 0x02) states.fFracDose=true; else states.fFracDose=false;
        if(resp[4] & 0x08) states.fSandDose=true; else states.fSandDose=false;
        if(resp[4] & 0x20) states.fPepeDose=true; else states.fPepeDose=false;
        if(resp[4] & 0x40) states.fCementDose=true; else states.fCementDose=false;
        //Когато флаг за клапа е 1 то клапата е затворена
        if(resp[3] & 0x01) states.fMixer=true; else states.fMixer=false;
        if(resp[3] & 0x02) states.fMixerValve=true; else states.fMixerValve=false;
        if(resp[3] & 0x04) states.fEmergencyStop=true; else states.fEmergencyStop=false;

        if(resp[4] & 0x01) states.fAutomaticMode=true; else states.fAutomaticMode=false;
        if(resp[4] & 0x04) states.fFractionValve=true; else states.fFractionValve=false;
        if(resp[4] & 0x10) states.fSandValve=true; else states.fSandValve=false;
        if(resp[4] & 0x80) states.fCementValve=true; else states.fCementValve=false;

        if(resp[7] & 0x01) states.fBelt=true; else  states.fBelt=false;

        if(resp[7] & 0x02) states.fShnek1=true; else states.fShnek1=false;

        if(resp[8] & 0x01) states.fWater=true; else states.fWater=false;
        if(resp[8] & 0x20) states.fShnek2=true; else states.fShnek2=false;
        if(resp[8] & 0x40) states.fCementWheel=true; else states.fCementWheel=false;

        ui->lblFractionValve->setVisible(!states.fFractionValve);
        ui->lblSandValve->setVisible(!states.fSandValve);
        ui->lblMixerValve->setVisible(!states.fMixerValve);
        ui->lblCementValve->setVisible(!states.fCementValve);
        ui->lblAutomaticMode->setVisible(states.fAutomaticMode);
        ui->lblEmebrgencyStop->setVisible(states.fEmergencyStop);
    }
    else
    {
        if(states.State != Fail) qDebug() << "Failed reading TWIDO or CRC error!";
        ui->lcdWater->display(888);
        fail = true;
    }

    if(fail)
    {
        qDebug() << "\nfail=true. failCounter=" << states.failCounter;
        if(states.failCounter == globals.MaxReadFails)
        {
           if(states.State != Idle)
           {
               currentRecepie.Status = 2;
               finishCycle();
               states.PrevState=states.State;
               states.State = Idle;
               ui->lblProgess->setText(tr("ТЕХНИЧЕСКИ ПРОБЛЕМ!"));
               qDebug() <<" Cycle is over after Fail. failCounter=" << states.failCounter;
               qDebug() << "STATE:Idle";
               ui->btnChange->setEnabled(true);
               ui->btnStart->setText(tr("СТАРТ"));
               ui->btnSelectConcrete->setEnabled(true);
               QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Заявката не може да продължи.\nПрекъсната е връзката с външно устройство."));
               beep();
               cycleTimer.start(800);
               return;
           }
        }
        else  states.failCounter++;
    }
    else  states.failCounter=0; //Ако всички устройства са четени коректно в цикъла то възстановяваме брояча

    if(states.failCounter)
    {//Ако някое устройство е прочетено грешно то нататък пропускаме цикъла
        cycleTimer.start(800);
        return;
    }

    //Устройствата са прочетени. Влизаме в автомат на състоянията
    switch(states.State)
    {
    case Start:
        //От Idle е натиснат бутон СТАРТ. Записват се във везните нивата и в TWIDO вода и време. Ако всичко е успешно състоянието става Run.Ако възникне грешка - Fail.
            int LIV6,LIV2;
            int check2, check6;
            int retry;

            //Пясък
            retry=5; check2 = -1;
            LIV2 = currentRecepie.MixSand - globals.AdvScaleSand;
            LIV2 *= globals.SandLIV2multi;
            if(LIV2<0) LIV2=0;

            do
            {
                retry--;
                qDebug() << "\nWriting to sand scale LIV2=" << (LIV2) << " retry = " << retry;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed to store LIV2 to the sand scale." ;
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везната за пясък."));
                    cycleTimer.start(800);
                    return;
                }

                ok = scaleSand.scale_getResponse(resp); //само за изчистване на буфера
                scaleSand.scale_Write(QString("LIV2,%1;").arg(LIV2));
                ok = scaleSand.scale_getResponse(resp);
                if(!ok) continue;

                scaleSand.scale_Write(QString("TDD1;"));
                ok = scaleSand.scale_getResponse(resp);
                if(!ok) continue;

                //проверка на записа
                scaleSand.scale_Write(QString("LIV?2;"));
                ok = scaleSand.scale_getResponse(resp);
                if(!ok) continue;
                check2 = QString(resp).trimmed().toInt(&ok);
            } while(check2!=LIV2);

            //Фракция
            retry=5; check2 = -1;
            LIV2 = currentRecepie.MixFraction - globals.AdvScaleFraction;
            LIV2 *= globals.FractionLIV2multi;
            if(LIV2<0) LIV2=0;
            do
            {
                retry--;
                qDebug() << "Writing to fraction scale LIV2=" << (LIV2) << " retry = " << retry;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed to store LIV2 to the fraction scale." ;
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везна за фракция."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }

                ok = scaleFrac.scale_getResponse(resp); //само за изчистване на буфера
                scaleFrac.scale_Write(QString("LIV2,%1;").arg(LIV2));
                ok = scaleFrac.scale_getResponse(resp);
                if(!ok) continue;

                scaleFrac.scale_Write(QString("TDD1;"));
                ok = scaleFrac.scale_getResponse(resp);
                if(!ok) continue;

                //проверка на записа
                scaleFrac.scale_Write(QString("LIV?2;"));
                ok = scaleFrac.scale_getResponse(resp);
                if(!ok) continue;
                check2 = QString(resp).trimmed().toInt(&ok);
            } while(check2!=LIV2);

            //Цимент/Пепелина
            retry=5; check2 = -1; check6 = -1;
            LIV2 = currentRecepie.MixCement - globals.AdvScaleCement;
            LIV2 *= globals.CementLIV2multi;
            if(LIV2<0) LIV2=0;
            if(currentRecepie.MixPepelina==0) LIV6 = LIV2;
            else
            {
                LIV6 = currentRecepie.MixCement  - globals.AdvScaleCement + currentRecepie.MixPepelina - globals.AdvScalePepelina;
                LIV6 *= globals.CementLIV6multi;
            }
            if(LIV6<0) LIV6=0;
            do
            {
                retry--;
                qDebug() << "Writing to cement scale LIV6=" << LIV6 << " LIV2=" << LIV2 << "\n" ;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed to store LIV2/LIV6 to the cement scale." ;
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везната за цимент."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                ok = scaleCement.scale_getResponse(resp); //само за изчистване на буфера
                scaleCement.scale_Write(QString("LIV6,%1;").arg(LIV6));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;

                scaleCement.scale_Write(QString("LIV2,%1;").arg(LIV2));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;

                scaleCement.scale_Write(QString("TDD1;"));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;

                //проверка на записа
                scaleCement.scale_Write(QString("LIV?2;"));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;
                check2 = QString(resp).trimmed().toInt(&ok);

                scaleCement.scale_Write(QString("LIV?6;"));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;
                check6 = QString(resp).trimmed().toInt(&ok);
            }while((check2!=LIV2) || (check6!=LIV6));

            int err;

            qDebug() << "Writing to TWIDO Water=" << currentRecepie.MixWater << "liters /" << currentRecepie.MixWater * globals.CoefVodomer << " pulses Time=" << currentRecepie.TimeCor;
            retry = 5;
            do
            {//В TWIDO се записва водата - литри * 3 в дума MW4 и времето за бъркане в WM5
                retry--;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed writing TWIDO.";
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                val.resize(4);
                val[0]= (uchar)(((int)(currentRecepie.MixWater * globals.CoefVodomer) & 0xFF00)>>8); //Water H
                val[1]= (uchar)((int)(currentRecepie.MixWater * globals.CoefVodomer) & 0xFF);//Water L
                val[2]= (uchar)(((int)currentRecepie.TimeCor & 0xFF00)>>8);; //Time H
                val[3]= (uchar)((int)currentRecepie.TimeCor & 0xFF); //Time L
                ok = mb.SendFc16(1,4,2,val,err);
            }while(!ok);

            //В TWIDO се записва  флаг за старт MW7.0
            TwidoFlags |= 0x0001;
            qDebug() << "Writing to TWIDO start flag MW7.0" << TwidoFlags;
            retry = 5;
            do
            {
                retry--;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                val.resize(2);
                val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                val[1]= (uchar)(TwidoFlags & 0xFF);// L
                ok = mb.SendFc16(1,7,1,val,err);
            }while(!ok);

            //В TWIDO се записва  времето за разтоварване в MW3
            qDebug() << "Writing to TWIDO DumpTime MW3=" << globals.DumpTime ;
            retry = 5;
            do
            {
                retry--;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                val.resize(2);
                val[0]= (uchar)(( globals.DumpTime & 0xFF00)>>8); // H
                val[1]= (uchar)(globals.DumpTime & 0xFF);// L
                ok = mb.SendFc16(1,3,1,val,err);
            }while(!ok);

            MixLeft = currentRecepie.MixNumber;
            ui->lblProgess->setText(tr("ИЗПЪЛНЕНИЕ:") +QString::number(currentRecepie.MixNumber - MixLeft + 1) + tr(" OT ") + QString::number(currentRecepie.MixNumber));
            _fPepeDose=false; _fSandDose=false; _fFracDose=false; _fCementDose=false;
            states.PrevState=states.State;
            states.State = Run;
            qDebug() << "STATE:Run  Phase=0. Waiting scales to reach dose levels...";
            Phase=0;
        break;//sase Start:

    case Run:

        if(Phase==0)
        {//Вдигнат е флага за старт в Twido. Пълненето на везните е започнало. Чакам да се вдигнат флаговете за дозата за да отчета количествата.
         //Когато дадено количество е отчетено в twido се записва съответен вдигнат флаг.

            //достигната е дозата за пясък.
            if(states.fSandDose && scaleSand.scale_isStable())
            {
                if((TwidoFlags & 0x0008) == 0) //пише се само веднъж - при вдигането на флага
                {
                    qDebug() << "\nSand dose raeched. Actual Value:" << ui->lcdSandScale->value();
                    //Добавя се в брояча вложеното количество и се изчислява отклонението от зададеното за едно бъркало ниво
                    currentRecepie.ExpSand += ui->lcdSandScale->value();
                    currentRecepie.DevSand += (currentRecepie.MixSand - ui->lcdSandScale->value()); //тази стойност се прибавя към заданието за следващото бъркало.
                    qDebug() << "Deviation=" <<  currentRecepie.DevSand ;

                   TwidoFlags |= 0x0008;
                   _fSandDose = true;
                   qDebug() << "Writing to TWIDO  flag MW7.3 " ;
                   retry = 5;
                   do
                   {
                       retry--;
                       if(retry == 0)
                       {//изчерпан е броя опити за запис
                           states.PrevState=states.State;
                           states.State = Fail;
                           qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                           qDebug() << "STATE:Fail";
                           QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                           beep();
                           cycleTimer.start(800);
                           return;
                       }
                       val.resize(2);
                       val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                       val[1]= (uchar)(TwidoFlags & 0xFF);// L
                       ok = mb.SendFc16(1,7,1,val,err);
                   }while(!ok);
                }
            }//

            //достигната е дозата за фракция.
            if(states.fFracDose && scaleFrac.scale_isStable())
            {
                if((TwidoFlags & 0x0002) == 0) //пише се само веднъж - при вдигането на флага
                {
                    qDebug() << "\nFraction dose raeched. Actual Value:" << ui->lcdFractScale->value();
                    //Добавя се в брояча вложеното количество и се изчислява отклонението от зададеното за едно бъркало ниво
                    currentRecepie.ExpFraction += ui->lcdFractScale->value();
                    currentRecepie.DevFraction += (currentRecepie.MixFraction - ui->lcdFractScale->value()); //тази стойност се прибавя към заданието за следващото бъркало.
                    qDebug() << "Deviation=" <<  currentRecepie.DevFraction ;

                   TwidoFlags |= 0x0002;
                   _fFracDose = true;
                   qDebug() << "Writing to TWIDO flag MW7.1 ";
                   retry = 5;
                   do
                   {
                       retry--;
                       if(retry == 0)
                       {//изчерпан е броя опити за запис
                           states.PrevState=states.State;
                           states.State = Fail;
                           qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                           qDebug() << "STATE:Fail";
                           QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                           beep();
                           cycleTimer.start(800);
                           return;
                       }
                       val.resize(2);
                       val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                       val[1]= (uchar)(TwidoFlags & 0xFF);// L
                       ok = mb.SendFc16(1,7,1,val,err);
                   }while(!ok);
                }
            }//

            //достигната е дозата за цимент.
            if(states.fCementDose && scaleCement.scale_isStable())
            {
                if((TwidoFlags & 0x0040) == 0) //пише се само веднъж - при вдигането на флага
                {
                    qDebug() << "\nCement dose raeched. Actual Value:" << ui->lcdCementScale->value();
                    //Добавя се в брояча вложеното количество и се изчислява отклонението от зададеното за едно бъркало ниво
                    currentRecepie.ExpCement += ui->lcdCementScale->value();
                    tmp = ui->lcdCementScale->value(); // запазва се количеството цимент за да се извади от пепелината
                    currentRecepie.DevCement += (currentRecepie.MixCement - ui->lcdCementScale->value()); //тази стойност се прибавя към заданието за следващото бъркало.
                    qDebug() << "Deviation=" <<  currentRecepie.DevCement ;

                    //TODO: Да се преизчисли стойността за LIV6 и да се запише
                    //Цимент/Пепелина
                    retry=5; check6 = -1;
                    if(currentRecepie.MixPepelina !=0)
                    {
                        LIV6 = currentRecepie.MixPepelina - globals.AdvScalePepelina + currentRecepie.DevPepelina + tmp;
                        LIV6 *= globals.CementLIV6multi;
                        qDebug() << "Recalculating LIV6";
                        qDebug() << "MixPepelina=" << currentRecepie.MixPepelina << " - globals.AdvScalePepelina=" << globals.AdvScalePepelina << " + currentRecepie.DevPepelina=" <<currentRecepie.DevPepelina << "  +  cement=" <<tmp;

                        if(LIV6<0) LIV6=0;
                        do
                        {
                            retry--;
                            qDebug() << "\nWriting to cement scale LIV6=" << LIV6 ;
                            if(retry == 0)
                            {//изчерпан е броя опити за запис
                                states.PrevState=states.State;
                                states.State = Fail;
                                qDebug() << "\nERROR! Failed to store LIV6 to the cement scale." ;
                                qDebug() << "STATE:Fail";
                                QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везната за цимент."));
                                beep();
                                cycleTimer.start(800);
                                return;
                            }
                            ok = scaleCement.scale_getResponse(resp); //само за изчистване на буфера
                            scaleCement.scale_Write(QString("LIV6,%1;").arg(LIV6));
                            ok = scaleCement.scale_getResponse(resp);
                            if(!ok) continue;

                            scaleCement.scale_Write(QString("TDD1;"));
                            ok = scaleCement.scale_getResponse(resp);
                            if(!ok) continue;

                            //проверка на записа
                            scaleCement.scale_Write(QString("LIV?6;"));
                            ok = scaleCement.scale_getResponse(resp);
                            if(!ok) continue;
                            check6 = QString(resp).trimmed().toInt(&ok);
                        }while(check6!=LIV6);
                    }



                    //------------------------------------------------------------
                   TwidoFlags |= 0x0040;
                   _fCementDose = true;
                   qDebug() << "Writing to TWIDO start flag MW7.6 ";
                   retry = 5;
                   do
                   {
                       retry--;
                       if(retry == 0)
                       {//изчерпан е броя опити за запис
                           states.PrevState=states.State;
                           states.State = Fail;
                           qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                           qDebug() << "STATE:Fail";
                           QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                           beep();
                           cycleTimer.start(800);
                           return;
                       }
                       val.resize(2);
                       val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                       val[1]= (uchar)(TwidoFlags & 0xFF);// L
                       ok = mb.SendFc16(1,7,1,val,err);
                   }while(!ok);
                }
            }//

            //достигната е дозата за пепелина.
            if(states.fPepeDose && scaleCement.scale_isStable())
            {
                if((TwidoFlags & 0x0020) == 0) //пише се само веднъж - при вдигането на флага
                {
                    qDebug() << "\nPepelina dose raeched. Actual Value:" << ui->lcdCementScale->value() - tmp;
                    //Добавя се в брояча вложеното количество и се изчислява отклонението от зададеното за едно бъркало ниво
                    //Пепелината се добавя на везната заедно с цимента. Затова от показанието на везната трябва да се извади вложеното количество цимент
                    currentRecepie.ExpPepelina += (ui->lcdCementScale->value() - tmp);
                    currentRecepie.DevPepelina += (currentRecepie.MixPepelina - ui->lcdCementScale->value() + tmp); //тази стойност се прибавя към заданието за следващото бъркало.
                    qDebug() << "Deviation=" <<  currentRecepie.DevPepelina ;

                   TwidoFlags |= 0x0020;
                   _fPepeDose = true;
                   qDebug() << "Writing to TWIDO start flag MW7.5 ";
                   retry = 5;
                   do
                   {
                       retry--;
                       if(retry == 0)
                       {//изчерпан е броя опити за запис
                           states.PrevState=states.State;
                           states.State = Fail;
                           qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                           qDebug() << "STATE:Fail";
                           QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                           beep();
                           cycleTimer.start(800);
                           return;
                       }
                       val.resize(2);
                       val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                       val[1]= (uchar)(TwidoFlags & 0xFF);// L
                       ok = mb.SendFc16(1,7,1,val,err);
                   }while(!ok);
                }
            }//

           if(_fPepeDose && _fCementDose && _fSandDose && _fFracDose)
           {
               Phase=1 ;
               qDebug() << "PHASE=1";
           }
        } //Край на фаза 0        if(Phase==0)

        if(Phase==1) //В тази фаза проверявам дали имам още бъркала
        {
            MixLeft--;            

            if(MixLeft==0)
            {   //Ако няма повече бъркало чакам да се разтовари и записвам 0 в MW7 и минавам в състояние Idle.
                //Критерият за разтоварен миксер - чакам бит 9 на МW0 да стане 0 (fMixerValve) - клапата се отваря. Разтоварваме
                //миксера в камиона. След това се връща в 1 - миксера е затворен и цикъла е приключил
                //За излизане се минава през фаза 3 и 4.
                Phase=3 ;
                if(currentRecepie.MixNumber>1)   repeatValve = 3;
                else repeatValve = 1;
                qDebug() << "PHASE=3 MixLeft=0. Waiting mixer valve to open...";
            }
            else
            {
                Phase=5;
                ui->lblProgess->setText(tr("ИЗПЪЛНЕНИЕ:") +QString::number(currentRecepie.MixNumber - MixLeft + 1) + tr(" OT ") + QString::number(currentRecepie.MixNumber));
                qDebug() << "PHASE=5 MixLeft=" << MixLeft;
            }
        }

        if(Phase==3) //Отваряне на клапата на миксера
        {
            //Във фаза 3 чакам да се отвори клапата на миксера за разтоварване
            if(!states.fMixerValve)
            {
                qDebug() << "Mixer valve is open. repeatValve=" << repeatValve;
                switch(repeatValve)
                {
                case 3:
                    repeatValve=2;
                    Phase=4;
                    qDebug() << "PHASE=4. Waiting mixer valve to close";
                    break;
                case 1:
                    repeatValve = 0;
                    //това е второто отваряне на клапата. Цикъла трябва да завърши
                    //Добавя се в брояча вложеното количество вода след като всички
                    //currentRecepie.ExpWater += ui->lcdWater->value();
                    Phase=4 ;
                    currentRecepie.Status = 0; //Цикълът е нормално завършен
                    qDebug() << "PHASE=4. Waiting mixer valve to close to finish...";                  
                    break;
                }
            }
        }
        /*
        */
        if(Phase==4) //Край на цикъла
        {

            if(states.fMixerValve)
            {
                qDebug() << "Mixer valve is closed. repeatValve=" << repeatValve;
                switch(repeatValve)
                {
                case 2:
                    repeatValve = 1;
                    Phase = 3;
                    qDebug() << "PHASE=3. Waiting mixer valve to open again";
                    break;
                case 0:
                    //това е второ затваряне на клапата
                    //Цикълът завършва със затваряне на клапата на миксера
                    currentRecepie.Status = 0;
                    finishCycle();
                    states.PrevState=states.State;
                    states.State = Idle;
                    qDebug() <<" Cycle is over. Normal exit.";
                    ui->lblProgess->setText(tr("ЗАЯВКАТА Е ИЗПЪЛНЕНА"));
                    qDebug() << "STATE:Idle";
                    ui->btnChange->setEnabled(true);
                    ui->btnSelectConcrete->setEnabled(true);
                    ui->btnStart->setText(tr("СТАРТ"));
                    break;
                }
            }
        }

        if(Phase==5)//Чакам везните да си свалят флаговете за доза. Това означава, че са празни
        {            
            _fPepeDose=states.fPepeDose;
            _fSandDose=states.fSandDose;
            _fFracDose=states.fFracDose;
            _fCementDose=states.fCementDose;

            if(!(_fPepeDose || _fSandDose || _fFracDose ||_fCementDose))
            {
                Phase=6;
                qDebug() << "\nPHASE=6" ;
            }
        }

        if(Phase==6)//Подготвят се везните за следващото бъркало , нулират се флаговете в twido и се минава обратно във фаза 0
        {
            // Прави се корекция във везните
            int LIV6,LIV2;
            int check2, check6;
            int retry;

            //Пясък
            retry=5; check2 = -1;
            LIV2 = currentRecepie.MixSand - globals.AdvScaleSand + currentRecepie.DevSand;
            LIV2 *= globals.SandLIV2multi;
            if(LIV2<0) LIV2=0;

            do
            {
                retry--;
                qDebug() << "\nWriting to sand scale LIV2=" << (LIV2) << " retry = " << retry;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed to store LIV2 to the sand scale." ;
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везната за пясък."));
                    cycleTimer.start(800);
                    return;
                }

                ok = scaleSand.scale_getResponse(resp); //само за изчистване на буфера
                scaleSand.scale_Write(QString("LIV2,%1;").arg(LIV2));
                ok = scaleSand.scale_getResponse(resp);
                if(!ok) continue;

                scaleSand.scale_Write(QString("TDD1;"));
                ok = scaleSand.scale_getResponse(resp);
                if(!ok) continue;

                //проверка на записа
                scaleSand.scale_Write(QString("LIV?2;"));
                ok = scaleSand.scale_getResponse(resp);
                if(!ok) continue;
                check2 = QString(resp).trimmed().toInt(&ok);
            } while(check2!=LIV2);

            //Фракция
            retry=5; check2 = -1;
            LIV2 = currentRecepie.MixFraction - globals.AdvScaleFraction + currentRecepie.DevFraction;
            LIV2 *= globals.FractionLIV2multi;
            if(LIV2<0) LIV2=0;
            do
            {
                retry--;
                qDebug() << "\nWriting to fraction scale LIV2=" << (LIV2) << " retry = " << retry;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed to store LIV2 to the fraction scale." ;
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везна за фракция."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }

                ok = scaleFrac.scale_getResponse(resp); //само за изчистване на буфера
                scaleFrac.scale_Write(QString("LIV2,%1;").arg(LIV2));
                ok = scaleFrac.scale_getResponse(resp);
                if(!ok) continue;

                scaleFrac.scale_Write(QString("TDD1;"));
                ok = scaleFrac.scale_getResponse(resp);
                if(!ok) continue;

                //проверка на записа
                scaleFrac.scale_Write(QString("LIV?2;"));
                ok = scaleFrac.scale_getResponse(resp);
                if(!ok) continue;
                check2 = QString(resp).trimmed().toInt(&ok);
            } while(check2!=LIV2);

            //Цимент/Пепелина
            retry=5; check2 = -1; check6 = -1;
            LIV2 = currentRecepie.MixCement - globals.AdvScaleCement + currentRecepie.DevCement;
            LIV2 *= globals.CementLIV2multi;
            if(LIV2<0) LIV2=0;
            if(currentRecepie.MixPepelina==0) LIV6 = LIV2;
            else
            {
                LIV6 = currentRecepie.MixPepelina - globals.AdvScalePepelina + currentRecepie.DevPepelina;
                LIV6 *= globals.CementLIV6multi;
                LIV6 += LIV2;
            }

            qDebug() << "MixPepelina=" << currentRecepie.MixPepelina << " - globals.AdvScalePepelina=" << globals.AdvScalePepelina << " + currentRecepie.DevPepelina=" <<currentRecepie.DevPepelina;
            qDebug() << "MixCement=" << currentRecepie.MixCement << " - globals.AdvScaleCement=" << globals.AdvScaleCement << " + currentRecepie.DevCement=" <<currentRecepie.DevCement;

            if(LIV6<0) LIV6=0;
            do
            {
                retry--;
                qDebug() << "\nWriting to cement scale LIV6=" << LIV6 << " LIV2=" << LIV2 ;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed to store LIV2/LIV6 to the cement scale." ;
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с везната за цимент."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                ok = scaleCement.scale_getResponse(resp); //само за изчистване на буфера
                scaleCement.scale_Write(QString("LIV6,%1;").arg(LIV6));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;

                scaleCement.scale_Write(QString("LIV2,%1;").arg(LIV2));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;

                scaleCement.scale_Write(QString("TDD1;"));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;

                //проверка на записа
                scaleCement.scale_Write(QString("LIV?2;"));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;
                check2 = QString(resp).trimmed().toInt(&ok);

                scaleCement.scale_Write(QString("LIV?6;"));
                ok = scaleCement.scale_getResponse(resp);
                if(!ok) continue;
                check6 = QString(resp).trimmed().toInt(&ok);
            }while((check2!=LIV2) || (check6!=LIV6));

            // КРАЙ - Везните са коригирани.
            //нулирам  MW7.1 3 5 и 6
            TwidoFlags &= ~(0x02 + 0x08 + 0x20 + 0x40);
            qDebug() << "Writing to TWIDO. Clear MW7 bits 1,3,5 and 6" ;
            retry = 5;
            do
            {
                retry--;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                val.resize(2);
                val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                val[1]= (uchar)(TwidoFlags & 0xFF);// L
                ok = mb.SendFc16(1,7,1,val,err);
            }while(!ok);

            Phase=0 ;
            qDebug() << "PHASE=0 MixLeft=" << MixLeft;
        }

        break;//case Run

    case PowerDown:
        currentRecepie.Status = 3;
        finishCycle();
        states.PrevState=states.State;
        states.State = Idle;
        qDebug() <<" Cycle is over after PowerDown.";
        qDebug() << "STATE:Idle";
        break;

    case Fail:
        currentRecepie.Status = 2;
        finishCycle();
        states.PrevState=states.State;
        states.State = Idle;
        ui->lblProgess->setText(tr("ТЕХНИЧЕСКИ ПРОБЛЕМ"));
        qDebug() <<" Cycle is over after Fail.";
        qDebug() << "STATE:Idle";
        ui->btnChange->setEnabled(true);
        ui->btnSelectConcrete->setEnabled(true);
        ui->btnStart->setText(tr("СТАРТ"));
        break;

    case Abort:
        currentRecepie.Status = 1;
        finishCycle();
        states.PrevState=states.State;
        states.State = Idle;
        ui->lblProgess->setText(tr("ЗАЯВКАТА Е ПРЕКРАТЕНА"));
        qDebug() <<" Cycle is over after Abort.";
        qDebug() << "STATE:Idle";
        ui->btnChange->setEnabled(true);
        ui->btnSelectConcrete->setEnabled(true);
        ui->btnStart->setText(tr("СТАРТ"));
        break;
    case Paused:
        //При влизане в пауза в Twido се вдига MW7.8
        if(states.PrevState != Paused)
        {
            //В TWIDO се записва  флаг за пауза MW7.8
            TwidoFlags |= 0x0100;
            qDebug() << "Writing to TWIDO pause flag MW7.8" << TwidoFlags;
            retry = 5;
            do
            {
                retry--;
                if(retry == 0)
                {//изчерпан е броя опити за запис
                    states.PrevState=states.State;
                    states.State = Fail;
                    qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
                    qDebug() << "STATE:Fail";
                    QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
                    beep();
                    cycleTimer.start(800);
                    return;
                }
                val.resize(2);
                val[0]= (uchar)(( TwidoFlags & 0xFF00)>>8); // H
                val[1]= (uchar)(TwidoFlags & 0xFF);// L
                ok = mb.SendFc16(1,7,1,val,err);
            }while(!ok);
        }
        break;
    case Idle:
        break;
    }
    //Таймера се саморестартира за единичен цикъл след 600 мсек за да се гарантира че няма застъпване
    states.PrevState = states.State;
    cycleTimer.start(800);
}


void MainWindow::finishCycle()
{
    /* Запис в БД
        -Час начало / край
        -име на избрана рецепта
        -вложени материали
        -влажност
        -ръчна корекция на насипни материали
        -ръчна корекция на вода
        -статус завършена/прекъсната
         INSERT INTO log VALUES ('2012-04-10 10:10:10', '2012-04-10 20:10:10' , 'B1', 2,1, 400,1200, 200,150,250,1,0,2);
        */
    QSqlQuery qry;
    int cd,cw;
    bool ok;
    int retry, err;

    cd = (currentRecepie.CorrectionDry ? 1 : 0);
    cw = (currentRecepie.CorrectionWater ? 1 : 0);
    QString qryStr = QString("INSERT INTO log VALUES ('%1 %2','%3 %4', '%5',%6, %7,%8, %9,%10,%11,%12,%13, %14,%15,%16,%17,%18, %19,%20,%21);")
                     .arg(currentRecepie.StartDate.toString("yyyy-MM-dd")) //начало //1
                     .arg(currentRecepie.SatrtTime.toString("hh:mm:ss"))            //2
                     .arg( QDate::currentDate().toString("yyyy-MM-dd")) //край      //3
                     .arg(QTime::currentTime().toString("hh:mm:ss"))                //4

                     .arg(currentRecepie.Name)      //5
                     .arg(currentRecepie.Quantity)  //6

                     .arg(QString::number(globals.HumiditySand,'f',1))     //7
                     .arg(QString::number(globals.HumidityFraction,'f',1)) //8
                     //вложени материали в текущата заявка
                     .arg(currentRecepie.ExpSand)       //9
                     .arg(currentRecepie.ExpFraction)   //10
                     .arg(currentRecepie.ExpCement)     //11
                     .arg(currentRecepie.ExpPepelina)     //12
                     .arg(currentRecepie.ExpWater)      //13
                     //Материали по рецепта за зададеното количество
                     .arg(currentRecepie.Sand * currentRecepie.Quantity)    //14
                     .arg(currentRecepie.Fraction * currentRecepie.Quantity)//15
                     .arg(currentRecepie.Cement * currentRecepie.Quantity)  //16
                     .arg(currentRecepie.Pepelina * currentRecepie.Quantity)  //17
                     .arg(currentRecepie.Water * currentRecepie.Quantity)   //18

                     .arg(cd) //CorrectionDry 1-имало е ръчна корекция на насипните материали   //19
                     .arg(cw) //CorrectionWater 1-имало е ръчна корекция на количеството вода   //20
                     .arg(currentRecepie.Status); //Status 0-Завършена 1-Прекъсната ръчно 2-Прекъсната от състояние fail 3-Прекъсната заради отпадане на захранването   //21

    qDebug() << "\nDatabase operation:" ;
    qDebug() << qryStr ;

    qry.prepare(qryStr);
    if(!qry.exec())
    {
        QMessageBox::critical(this, tr("Грешка база данни"), tr("Не мога да изпълня SQL заявка\nза запис в БД "));
        beep();
    }

    //Нулират се броячите в текущата рецепта
    //нулиране на броячите на вложените материали
    currentRecepie.ExpCement=0;
    currentRecepie.ExpFraction=0;
    currentRecepie.ExpPepelina=0;
    currentRecepie.ExpSand=0;
    //currentRecepie.ExpWater=0;
    //Нулиране на отклоненията
    currentRecepie.DevCement=0;
    currentRecepie.DevFraction=0;
    currentRecepie.DevPepelina=0;
    currentRecepie.DevSand=0;
    //Нулирам МW7
    if( states.State == PowerDown) return; //при отпаднало захранване не се опитвам да пиша в Twido TODO:?????
    TwidoFlags=0;
    retry = 5;
    do
    {
        retry--;
        if(retry == 0)
        {//изчерпан е броя опити за запис
            states.PrevState=states.State;
            states.State = Fail;
            qDebug() << "\nERROR! Failed writing TwidoFlags to TWIDO.";
            qDebug() << "STATE:Fail";
            QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Програмата не може да продължи.\nПрекъсната е връзката с Twido."));
            beep();
            cycleTimer.start(800);
            return;
        }
        val.resize(2);
        val[0]= 0;
        val[1]= 0;
        ok = mb.SendFc16(1,7,1,val,err);
    }while(!ok);
}
//-------------------------------------------------------------------------
#ifdef TAKE_SCREENSHOTS
void MainWindow::takeScreenShot()
{
    QPixmap screen;
    QString format = "png";

    screen = QPixmap::grabWindow(QApplication::desktop()->winId());
    screen.save(QString("/sdcard/nainwindow.png"),format.toAscii());
}
#endif
