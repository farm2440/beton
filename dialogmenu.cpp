#include "dialogmenu.h"
#include "ui_dialogmenu.h"

DialogMenu::DialogMenu(QWidget *parent) :    QDialog(parent),    ui(new Ui::DialogMenu)
{
    ui->setupUi(this);
    // *** -= КИРИЛИЗАЦИЯ !!! =- ***
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    //без курсор
    this->setCursor(QCursor(Qt::BlankCursor));
    //connect buttons handlers
    connect(ui->btnMenuExit,SIGNAL(clicked()),this,SLOT(exitMenu()));
    connect(ui->btnSetDateTime,SIGNAL(clicked()),this,SLOT(setDateTime()));
    connect(ui->btnLoadRecipies,SIGNAL(clicked()),this,SLOT(loadRecipies()));
    connect(ui->btnSaveRecepies,SIGNAL(clicked()),this,SLOT(saveRecepies()));    
    connect(ui->btnAbort,SIGNAL(clicked()),this,SLOT(onAbort()));
    connect(ui->btnReport,SIGNAL(clicked()),this,SLOT(Report()));

    connect(ui->btnHumiditySandUp,SIGNAL(clicked()),this,SLOT(onHumiditySandUp()));
    connect(ui->btnHumiditySandDwn,SIGNAL(clicked()),this,SLOT(onHumiditySandDown()));
    connect(ui->btnHumidityFractionUp,SIGNAL(clicked()),this,SLOT(onHumidityFractionUp()));
    connect(ui->btnHumidityFractionDwn,SIGNAL(clicked()),this,SLOT(onHumidityFractionDown()));
    connect(ui->btnDumpTimeUp,SIGNAL(clicked()),this,SLOT(onDumpTimeUp()));
    connect(ui->btnDumpTimeDwn,SIGNAL(clicked()),this,SLOT(onDumpTimeDown()));

    connect(ui->btnAdvCementUp,SIGNAL(clicked()),this,SLOT(onCementAdvUp()));
    connect(ui->btnAdvCementDwn,SIGNAL(clicked()),this,SLOT(onCementAdvDwn()));

    connect(ui->btnAdvFractUp,SIGNAL(clicked()),this,SLOT(onFractAdvUp()));
    connect(ui->btnAdvFracDwn,SIGNAL(clicked()),this,SLOT(onFractAdvDwn()));

    connect(ui->btnAdvSandUp,SIGNAL(clicked()),this,SLOT(onSandAdvUp()));
    connect(ui->btnAdvSandDwn,SIGNAL(clicked()),this,SLOT(onSandAdvDwn()));

    connect(ui->btnAdvPepelUp,SIGNAL(clicked()),this,SLOT(onPepelAdvUp()));
    connect(ui->btnAdvPepelDwn,SIGNAL(clicked()),this,SLOT(onPepelAdvDwn()));

    //Date/Time update
    connect(&clockTimer,SIGNAL(timeout()),this,SLOT(clockTick()));
    clockTimer.start(1000);

    ui->lineHumidityFraction->setText(QString("%1").arg(globals.HumidityFraction));
    ui->lineHumiditySand->setText(QString("%1").arg(globals.HumiditySand));
    ui->lineDumpTime->setText(QString("%1").arg(globals.DumpTime));

    ui->lineAdvCement->setText(QString::number(globals.AdvScaleCement,'f',0));
    ui->lineAdvFraction->setText(QString::number(globals.AdvScaleFraction,'f',0));
    ui->lineAdvPepel->setText(QString::number(globals.AdvScalePepelina,'f',0));
    ui->lineAdvSand->setText(QString::number(globals.AdvScaleSand,'f',0));

    humidityChanged=false;

    //В зависимост от текущото състояние някои корекции могат да бъдат забранени.
    switch(states.State)
    {
    case Idle:
        //в това състояние всички бутони за достъпни освен ПРЕКРАТИ ЗАЯВКА
        ui->btnHumidityFractionDwn->setEnabled(true);
        ui->btnHumidityFractionUp->setEnabled(true);
        ui->lineHumidityFraction->setEnabled(true);

        ui->btnHumiditySandUp->setEnabled(true);
        ui->btnHumiditySandDwn->setEnabled(true);
        ui->lineHumiditySand->setEnabled(true);

        ui->btnDumpTimeUp->setEnabled(true);
        ui->btnDumpTimeDwn->setEnabled(true);
        ui->lineDumpTime->setEnabled(true);

        ui->btnAbort->setEnabled(false);
        ui->btnLoadRecipies->setEnabled(true);
        ui->btnSaveRecepies->setEnabled(true);
        ui->btnSetDateTime->setEnabled(true);

        ui->btnAdvCementUp->setEnabled(true);
        ui->btnAdvCementDwn->setEnabled(true);
        ui->lineAdvCement->setEnabled(true);

        ui->btnAdvFractUp->setEnabled(true);
        ui->btnAdvFracDwn->setEnabled(true);
        ui->lineAdvFraction->setEnabled(true);

        ui->btnAdvPepelUp->setEnabled(true);
        ui->btnAdvPepelDwn->setEnabled(true);
        ui->lineAdvPepel->setEnabled(true);

        ui->btnAdvSandUp->setEnabled(true);
        ui->btnAdvSandDwn->setEnabled(true);
        ui->lineAdvSand->setEnabled(true);

        break;

    case Fail:
    case Start:
    case Run:
    case Abort:
    case PowerDown:
        ui->btnHumidityFractionDwn->setEnabled(false);
        ui->btnHumidityFractionUp->setEnabled(false);
        ui->lineHumidityFraction->setEnabled(false);

        ui->btnHumiditySandUp->setEnabled(false);
        ui->btnHumiditySandDwn->setEnabled(false);
        ui->lineHumiditySand->setEnabled(false);

        ui->btnDumpTimeUp->setEnabled(false);
        ui->btnDumpTimeDwn->setEnabled(false);
        ui->lineDumpTime->setEnabled(false);

        ui->btnAbort->setEnabled(false);
        ui->btnLoadRecipies->setEnabled(false);
        ui->btnSaveRecepies->setEnabled(false);
        ui->btnSetDateTime->setEnabled(false);

        ui->btnAdvCementUp->setEnabled(false);
        ui->btnAdvCementDwn->setEnabled(false);
        ui->lineAdvCement->setEnabled(false);

        ui->btnAdvFractUp->setEnabled(false);
        ui->btnAdvFracDwn->setEnabled(false);
        ui->lineAdvFraction->setEnabled(false);

        ui->btnAdvPepelUp->setEnabled(false);
        ui->btnAdvPepelDwn->setEnabled(false);
        ui->lineAdvPepel->setEnabled(false);

        ui->btnAdvSandUp->setEnabled(false);
        ui->btnAdvSandDwn->setEnabled(false);
        ui->lineAdvSand->setEnabled(false);

        break;

    case Paused:       
        ui->btnHumidityFractionDwn->setEnabled(false);
        ui->btnHumidityFractionUp->setEnabled(false);
        ui->lineHumidityFraction->setEnabled(false);

        ui->btnHumiditySandUp->setEnabled(false);
        ui->btnHumiditySandDwn->setEnabled(false);
        ui->lineHumiditySand->setEnabled(false);

        ui->btnDumpTimeUp->setEnabled(false);
        ui->btnDumpTimeDwn->setEnabled(false);
        ui->lineDumpTime->setEnabled(false);

        ui->btnAbort->setEnabled(true);
        ui->btnLoadRecipies->setEnabled(false);
        ui->btnSaveRecepies->setEnabled(false);
        ui->btnSetDateTime->setEnabled(false);

        ui->btnAdvCementUp->setEnabled(false);
        ui->btnAdvCementDwn->setEnabled(false);
        ui->lineAdvCement->setEnabled(false);

        ui->btnAdvFractUp->setEnabled(false);
        ui->btnAdvFracDwn->setEnabled(false);
        ui->lineAdvFraction->setEnabled(false);

        ui->btnAdvPepelUp->setEnabled(false);
        ui->btnAdvPepelDwn->setEnabled(false);
        ui->lineAdvPepel->setEnabled(false);

        ui->btnAdvSandUp->setEnabled(false);
        ui->btnAdvSandDwn->setEnabled(false);
        ui->lineAdvSand->setEnabled(false);
        break;
    }
}

void DialogMenu::loadRecipies()
{
    bool ready = false;
    QString strUmount("umount /dev/udisk");
    QString strMount("mount /dev/udisk /udisk");
    QString strCopy;

    int exitCode;
    QProcess *proc = new QProcess(this);
    QTime time;

    beep();
    QMessageBox::StandardButton choice;
    choice = QMessageBox::information(this,tr("Запис на файл"),tr("ВНИМАНИЕ! Старите рецепти ще бъдат изтрити.\nНов файл с рецепти ще бъде копиран от външна памет.\nМоля, поставете външна памент в USB и натиснете ОК."),QMessageBox::Ok,QMessageBox::Cancel);
    this->setCursor(QCursor(Qt::BlankCursor));
    beep();
    if(choice==QMessageBox::Cancel) return;
    time.restart();

    //диалог с прогрес бар излиза докато се сканира за флашка
    QProgressDialog pdlg(tr("Зареждане на рецепти"),tr("Търсене на устройство..."),0,56,this);
    pdlg.setWindowModality(Qt::WindowModal);
    pdlg.show();
    int val = 0;

    while(!ready)
    {
        //демонтирам и отново монтирам флашката във файловата система.Така ако последната операция е успешна
        //се уверявам, че флашката е поставена.
        //unmount
        exitCode = proc->execute(strUmount);
        //mount and check the  exit code
        exitCode = proc->execute(strMount);
        //придвижва се прогрес бара
        pdlg.setValue(val);
        pdlg.setCursor(QCursor(Qt::BlankCursor));
        if(val<56) val++;

        if(exitCode==0){ ready=true; }
        else
        {
            if(time.elapsed()>6000)
            {//проверка за таймаут
                QMessageBox::critical(this,tr("ГРЕШКА"),tr("Външна USB памет не може да бъде открита"));
                beep();
                if(proc!=NULL) delete proc;
                pdlg.hide();
                this->setCursor(QCursor(Qt::BlankCursor));
                return;
            }
        }
        qApp->processEvents();
    }
    pdlg.close();

    QDir dir("/udisk");
    QStringList filter;
    QStringList files;
    filter<<"*.bet";
    dir.setNameFilters(filter);
    files = dir.entryList();

    DialogSelectFile *dlg = new DialogSelectFile(this,&files);
    if(dlg->exec()==QDialog::Accepted)
    {
        strCopy = QString("cp /udisk/%1 /sdcard/recepti/recepti.bet").arg(dlg->getSelectedFileName());
        exitCode =  proc->execute(strCopy);
    }
    if(proc!=NULL) delete proc;
    if(dlg!=NULL) delete dlg;
}

void DialogMenu::saveRecepies()
{
    /* файлът /sdcard/recepti/recepti.bet се записва на usb памет */
    bool ready = false;
    QString strUmount("umount /dev/udisk");
    QString strMount("mount /dev/udisk /udisk");
    int exitCode;
    QTime time;

    beep();

    QMessageBox::StandardButton choice;
    choice = QMessageBox::information(this,tr("Запис на файл"),tr("Файлът с рецептите ще бъде копиран към външна памет.\nМоля, поставете външна памент в USB и натиснете ОК."),QMessageBox::Ok,QMessageBox::Cancel);
    this->setCursor(QCursor(Qt::BlankCursor));
    beep();
    if(choice==QMessageBox::Cancel) return;

    QProcess *proc = new QProcess(this);
    time.restart();
    //диалог с прогрес бар излиза докато се сканира за флашка
    QProgressDialog pdlg(tr("Запис на рецепти"),tr("Търсене на устройство..."),0,56,this);
    pdlg.setWindowModality(Qt::WindowModal);
    pdlg.show();
    int val = 0;

    while(!ready)
    {
        //демонтирам и отново монтирам флашката във файловата система.Така ако последната операция е успешна
        //се уверявам, че флашката е поставена.
        //unmount
        exitCode = proc->execute(strUmount);
        //mount and check the  exit code
        exitCode = proc->execute(strMount);
        //придвижва се прогрес бара
        pdlg.setValue(val);
        pdlg.setCursor(QCursor(Qt::BlankCursor));
        if(val<56) val++;

        if(exitCode==0){ ready=true; }
        else
        {
            if(time.elapsed()>6000)
            {//проверка за таймаут
                QMessageBox::critical(this,tr("ГРЕШКА"),tr("Външна USB памет не може да бъде открита"));
                beep();
                if(proc!=NULL) delete proc;
                pdlg.hide();
                return;
            }
        }
        qApp->processEvents();
    }
    pdlg.close();
    //създава се уникално име нафайл
    QString newFileName = QString("recepti-%1%2%3%4.bet").arg(QDate::currentDate().day())
                                                         .arg(QTime::currentTime().hour())
                                                         .arg(QTime::currentTime().minute())
                                                         .arg(QTime::currentTime().second());
    QString copyCommand = QString("cp /sdcard/recepti/recepti.bet /udisk/%1").arg(newFileName);
    exitCode = proc->execute(copyCommand);
    proc->execute(strUmount);
    if(exitCode) QMessageBox::critical(this,tr("ГРЕШКА"),tr("Гршка при опит да бъде записан файла с рецептите\nвърху външна USB памет."));
    else QMessageBox::information(this,tr("Запис на файл"),tr("Файлът ") + newFileName + tr(" е записан.\nМожете да извадите паметта от USB."));

    beep();
    if(proc!=NULL) delete proc;
}

void DialogMenu::setDateTime()
{
    beep();
    DialogDateTime *dlg = new DialogDateTime(this);
    dlg->setModal(true);
    dlg->updateEditTime(QTime::currentTime(),QDate::currentDate());
    dlg->exec();
    delete dlg;
}

DialogMenu::~DialogMenu()
{
    delete ui;
}

void DialogMenu::exitMenu()
{
#ifdef TAKE_SCREENSHOTS
    takeScreenShot();
#endif
    beep();
    if(humidityChanged)
    {
        qDebug() << "\nHumidityChanged!" ;
        qDebug() << "Sand Humidity:" << globals.HumiditySand << "%   Fraction Humidity:"<< globals.HumidityFraction ;
        qDebug() << "New values will take part in next recepie selection.\n";
    }
    this->accept();
}

void DialogMenu::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

/* Актуализиране на текущото време показвано в диалога. */
void DialogMenu::clockTick()
{
    QDate dt;
    QTime tm;
    tm=QTime::currentTime();
    dt=QDate::currentDate();
    ui->lblDateTime->setText(dt.toString() +"  " + tm.toString());
}

void DialogMenu::beep()
{
 //  qApp->beep();

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

/* Прекратява изпълнението на текущата заявка.
   Записва се изпълненото и изчистването на материалите става в ръчен режим */
void DialogMenu::onAbort()
{

    beep();
    QMessageBox::StandardButton res = QMessageBox::warning(this,
                                                           tr("ВНИМАНИЕ!"),
                                                           tr("ТЕКУЩАТА ЗАЯВКА ЩЕ БЪДЕ ПРЕКРАТЕНА!\nСИГУРНИ ЛИ СТЕ?"),
                                                           QMessageBox::Ok | QMessageBox::Cancel);
    beep();
    if(res==QMessageBox::Ok)
    {
        states.PrevState = states.State;
        states.State = Abort;
        qDebug() << "STATE:Abort";
        ui->btnAbort->setEnabled(false);

        ui->btnHumidityFractionDwn->setEnabled(false);
        ui->btnHumidityFractionUp->setEnabled(false);
        ui->lineHumidityFraction->setEnabled(false);
        ui->btnHumiditySandUp->setEnabled(false);
        ui->btnHumiditySandDwn->setEnabled(false);
        ui->lineHumiditySand->setEnabled(false);
    }
}

/* Стойността на влажност се използва за корекция на количеството вложени инертни материали */
void DialogMenu::onDumpTimeUp()
{
    beep();
    if(globals.DumpTime<180) globals.DumpTime++;
    ui->lineDumpTime->setText(QString("%1").arg(globals.DumpTime));
}

void DialogMenu::onDumpTimeDown()
{
    beep();
    if(globals.DumpTime>0) globals.DumpTime--;
    ui->lineDumpTime->setText(QString("%1").arg(globals.DumpTime));
}

void DialogMenu::onHumidityFractionUp()
{
    beep();
    if(globals.HumidityFraction<30) globals.HumidityFraction+=0.1;
    ui->lineHumidityFraction->setText(QString::number(globals.HumidityFraction,'f',1));
    humidityChanged=true;
}

void DialogMenu::onHumidityFractionDown()
{
    beep();
    if(globals.HumidityFraction >=0.1) globals.HumidityFraction-=0.1;
    ui->lineHumidityFraction->setText(QString::number(globals.HumidityFraction,'f',1));
    humidityChanged=true;
}

void DialogMenu::onHumiditySandUp()
{
    beep();
    if(globals.HumiditySand<30) globals.HumiditySand+=0.1;
    ui->lineHumiditySand->setText(QString::number(globals.HumiditySand,'f',1));
    humidityChanged=true;
}

void DialogMenu::onHumiditySandDown()
{
    beep();
    if(globals.HumiditySand >= 0.1) globals.HumiditySand-=0.1;
    ui->lineHumiditySand->setText(QString::number(globals.HumiditySand,'f',1));
    humidityChanged=true;
}

void DialogMenu::onSandAdvUp()
{
    beep();
    if(globals.AdvScaleSand<300) globals.AdvScaleSand+=1;
    ui->lineAdvSand->setText(QString::number(globals.AdvScaleSand,'f',0));
}

void DialogMenu::onSandAdvDwn()
{
    beep();
    if(globals.AdvScaleSand>0) globals.AdvScaleSand-=1;
    ui->lineAdvSand->setText(QString::number(globals.AdvScaleSand,'f',0));
}

void DialogMenu::onCementAdvUp()
{
    beep();
    if(globals.AdvScaleCement<30) globals.AdvScaleCement+=1;
    ui->lineAdvCement->setText(QString::number(globals.AdvScaleCement,'f',0));
}

void DialogMenu::onCementAdvDwn()
{
    beep();
    if(globals.AdvScaleCement>0) globals.AdvScaleCement-=1;
    ui->lineAdvCement->setText(QString::number(globals.AdvScaleCement,'f',0));
}

void DialogMenu::onFractAdvUp()
{
    beep();
    if(globals.AdvScaleFraction<300) globals.AdvScaleFraction+=1;
    ui->lineAdvFraction->setText(QString::number(globals.AdvScaleFraction,'f',0));
}

void DialogMenu::onFractAdvDwn()
{
    beep();
    if(globals.AdvScaleFraction>0) globals.AdvScaleFraction-=1;
    ui->lineAdvFraction->setText(QString::number(globals.AdvScaleFraction,'f',0));
}

void DialogMenu::onPepelAdvUp()
{
    beep();
    if(globals.AdvScalePepelina<30) globals.AdvScalePepelina+=1;
    ui->lineAdvPepel->setText(QString::number(globals.AdvScalePepelina,'f',0));
}

void DialogMenu::onPepelAdvDwn()
{
    beep();
    if(globals.AdvScalePepelina>0) globals.AdvScalePepelina-=1;
    ui->lineAdvPepel->setText(QString::number(globals.AdvScalePepelina,'f',0));
}


void DialogMenu::Report()
{
    //bool ok;
    //QSqlQuery qry;

    beep();    
    DialogReport *dlg = new DialogReport(this);
    dlg->setModal(true);
    dlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog) ; //скривам рамката на диалоговия прозор
    dlg->exec();
    delete dlg;

    /*
    qry.prepare("SELECT * FROM log;");
    if(!qry.exec())
    {
        QMessageBox::critical(this, tr("Грешка база данни"), tr("Не мога да изпълня SQL заявка SELECT"));
        beep();
        return;
    }

    qDebug() << "\nLOG REPORT:" ;                         //             -       -       -       -       -       -       -       -       -       -       -       -       -       -       -       -
    qDebug() << " START               END                 model          Quant.  SH%     FH%     Sand    Fract   Cement  Pepel   Water   R.Sand  R.Frac  R.Cem   R.Pepel R.Water CorDry  CorWat  ExitStatus ";
    //DEMO ДЕМО
    while(qry.next())
    {
        QString qs;
        QString name;
        name =  qry.value(2).toString().leftJustified(8,' ');  //име

        qs = qry.value(0).toString() //start
             +' ' + qry.value(1).toString() //stop
             +' ' + name

             +'\t'  + qry.value(3).toString() //количество
             +'\t'  + qry.value(4).toString() //влажност пясък
             +'\t'  + qry.value(5).toString() //влажност фракция
             //Реално вложени материали
             +'\t'  + qry.value(6).toString() //пясък
             +'\t'  + qry.value(7).toString() //фракция
             +'\t'  + qry.value(8).toString() //цилмент
             +'\t'  + qry.value(9).toString() //пепелина
             +'\t'  + qry.value(10).toString() //вода
             //Материали зададени в оригиналната рецепта
             +'\t'  + qry.value(11).toString() //пясък
             +'\t'  + qry.value(12).toString() //фракция
             +'\t'  + qry.value(13).toString() //цилмент
             +'\t'  + qry.value(14).toString() //пепелина
             +'\t'  + qry.value(15).toString(); //вода

//             +'\t'  + qry.value(10).toString() //корекция материали
//        +'\t'  + qry.value(11).toString() //корекция вода
//        +'\t'  + qry.value(12).toString(); //статус
            ////Коригирани материали

             if(qry.value(16)==1) qs += "\tY";
             else qs+= "\tN";
             //коригирана вода
             if(qry.value(17)==1) qs += "\tY";
             else qs+= "\tN";

             switch(qry.value(18).toInt(&ok))
             {
             case 0:
                 qs+="\tNormal exit";
                 break;
             case 1:
                 qs+="\tManual abort";
                 break;
             case 2:
                 qs+="\tHardware Failure";
                 break;
             case 3:
                 qs+="\tPower down";
                 break;
             default:
                 qs+="\tUnknown";
                 break;
             }

             qDebug() << qs;
    } */
}

#ifdef TAKE_SCREENSHOTS
void DialogMenu::takeScreenShot()
{
    QPixmap screen;
    QString format = "png";

    screen = QPixmap::grabWindow(QApplication::desktop()->winId());
    screen.save(QString("/sdcard/menu.png"),format.toAscii());
}
#endif
