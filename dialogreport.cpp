#include "dialogreport.h"
#include "ui_dialogreport.h"

DialogReport::DialogReport(QWidget *parent) :    QDialog(parent),    ui(new Ui::DialogReport)
{
    ui->setupUi(this);
    // *** -= КИРИЛИЗАЦИЯ !!! =- ***
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    this->setCursor(QCursor(Qt::BlankCursor));

    ui->textEdit->setVisible(false);
    showReport=false;

    connect(ui->btnExit,SIGNAL(clicked()),this,SLOT(onExit()));
    connect(ui->btnSave,SIGNAL(clicked()),this,SLOT(onSave()));
    connect(ui->btnShow,SIGNAL(clicked()),this,SLOT(onShowReport()));

    connect(ui->btnEndTimeDown,SIGNAL(clicked()),ui->timeEditEnd,SLOT(stepDown()));
    connect(ui->btnEndTimeUp,SIGNAL(clicked()),ui->timeEditEnd,SLOT(stepUp()));

    connect(ui->btnStartTimeDown,SIGNAL(clicked()),ui->timeEditStart,SLOT(stepDown()));
    connect(ui->btnStartTimeUp,SIGNAL(clicked()),ui->timeEditStart,SLOT(stepUp()));

    connect(ui->btnEndTimeDown,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnEndTimeUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnStartTimeDown,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnStartTimeUp,SIGNAL(clicked()),this,SLOT(beep()));

    connect(ui->calendarWidgetEnd,SIGNAL(clicked(QDate)),this,SLOT(beep()));
    connect(ui->calendarWidgetStart,SIGNAL(clicked(QDate)),this,SLOT(beep()));

    ui->btnSave->setEnabled(false);
}

DialogReport::~DialogReport()
{
    delete ui;
}

void DialogReport::changeEvent(QEvent *e)
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

void DialogReport::onSave()
{
    beep();

    bool ready = false;
    QString strUmount("umount /dev/udisk");
    QString strMount("mount /dev/udisk /udisk");
    int exitCode;
    QTime time;
    bool fileWriOK=false;
    bool fileTxtOK=false;

    QMessageBox::StandardButton choice;
    choice = QMessageBox::information(this,tr("Запис на файл"),tr("Моля, поставете външна памент в USB и натиснете ОК."),QMessageBox::Ok,QMessageBox::Cancel);
    beep();
    if(choice==QMessageBox::Cancel) return;

    QProcess *proc = new QProcess(this);
    time.restart();
    //диалог с прогрес бар излиза докато се сканира за флашка
    QProgressDialog pdlg(tr("Запис на справка"),tr("Търсене на устройство..."),0,56,this);
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
    QString wriFileName  = QString("report-%1%2%3%4.wri").arg(QDate::currentDate().day())
                                                         .arg(QTime::currentTime().hour())
                                                         .arg(QTime::currentTime().minute())
                                                         .arg(QTime::currentTime().second());

    QString tabFileName  = QString("report-%1%2%3%4.txt").arg(QDate::currentDate().day())
                                                         .arg(QTime::currentTime().hour())
                                                         .arg(QTime::currentTime().minute())
                                                         .arg(QTime::currentTime().second());

    QFile wriFile("/udisk/" + wriFileName);
    QFile tabFile("/udisk/" + tabFileName);

    //Записва се файл с разширение .wri и съдържанието му е това на textEdit

    if(wriFile.open(QIODevice::WriteOnly))
    {
        QTextStream wriStream(&wriFile);
        QTextCodec *cyrCodec = QTextCodec::codecForName("Windows-1251");
        wriStream.setCodec(cyrCodec);

        wriStream << QString(tr("Справка за изпълнените заявки за периода от %2 на %1 до %4 на %3 \n\n"))
                    .arg(ui->calendarWidgetStart->selectedDate().toString("yyyy-MM-dd"))
                    .arg(ui->timeEditStart->time().toString("hh:mm:ss"))
                    .arg(ui->calendarWidgetEnd->selectedDate().toString("yyyy-MM-dd"))
                    .arg(ui->timeEditEnd->time().toString("hh:mm:ss"));;
        wriStream << ui->textEdit->toPlainText();
        qDebug() <<  ui->textEdit->toPlainText();
        wriFile.close();
        fileWriOK=true;
    }

    //Записва се файл с разширение .txt в който данните са разделени с табове
    if(tabFile.open(QIODevice::WriteOnly))
    {
        QTextStream tabStream(&tabFile);
        QTextCodec *cyrCodec = QTextCodec::codecForName("Windows-1251");
        tabStream.setCodec(cyrCodec);

        tabStream << QString(tr("Справка за изпълнените заявки за периода от %2 на %1 до %4 на %3 \n\n"))
                    .arg(ui->calendarWidgetStart->selectedDate().toString("yyyy-MM-dd"))
                    .arg(ui->timeEditStart->time().toString("hh:mm:ss"))
                    .arg(ui->calendarWidgetEnd->selectedDate().toString("yyyy-MM-dd"))
                    .arg(ui->timeEditEnd->time().toString("hh:mm:ss"));;
        tabStream << table;
        qDebug() << table;
        tabFile.close();
        fileTxtOK=true;
    }

    proc->execute(strUmount);
    qDebug() << "unmount:" << strUmount;

    if(fileWriOK && fileTxtOK)  QMessageBox::information(this,tr("Запис на файл"),tr("Файлoвете ") + wriFileName + tr(" и ") + tabFileName + tr(" са записани.\nМожете да извадите паметта от USB."));
    else  QMessageBox::critical(this,tr("ГРЕШКА"),tr("Гршка при опит да бъде записан файла\nвърху външна USB памет."));

    beep();
    if(proc!=NULL) delete proc;
}

void DialogReport::onShowReport()
{

    bool ok;
    QSqlQuery qry;
    QString str;

    beep();
    if(showReport)
    {
        ui->btnEndTimeDown->setVisible(true);
        ui->btnEndTimeUp->setVisible(true);
        ui->btnStartTimeDown->setVisible(true);
        ui->btnStartTimeUp->setVisible(true);
        ui->calendarWidgetEnd->setVisible(true);
        ui->calendarWidgetStart->setVisible(true);
        ui->lblEnd->setVisible(true);
        ui->lblStart->setVisible(true);
        ui->timeEditStart->setVisible(true);
        ui->timeEditEnd->setVisible(true);

        ui->btnSave->setEnabled(false);
        ui->textEdit->setVisible(false);
        ui->btnShow->setText(tr("ПОКАЖИ"));
    }
    else
    {
        this->setCursor(QCursor(Qt::WaitCursor));
        ui->btnEndTimeDown->setVisible(false);
        ui->btnEndTimeUp->setVisible(false);
        ui->btnStartTimeDown->setVisible(false);
        ui->btnStartTimeUp->setVisible(false);
        ui->calendarWidgetEnd->setVisible(false);
        ui->calendarWidgetStart->setVisible(false);
        ui->lblEnd->setVisible(false);
        ui->lblStart->setVisible(false);
        ui->timeEditStart->setVisible(false);
        ui->timeEditEnd->setVisible(false);

        ui->textEdit->setVisible(true);
        ui->textEdit->clear();
        ui->btnShow->setText(tr("СКРИЙ"));

        str = QString("select * from log where StartTime >= '%1 %2' and EndTime <= '%3 %4';")
                        .arg(ui->calendarWidgetStart->selectedDate().toString("yyyy-MM-dd"))
                        .arg(ui->timeEditStart->time().toString("hh:mm:ss"))
                        .arg(ui->calendarWidgetEnd->selectedDate().toString("yyyy-MM-dd"))
                        .arg(ui->timeEditEnd->time().toString("hh:mm:ss"));
        //qDebug() << str;

        qry.prepare(str);
        if(!qry.exec())
        {
            this->setCursor(QCursor(Qt::BlankCursor));
            QMessageBox::critical(this, tr("Грешка база данни"), tr("Не мога да изпълня SQL заявка SELECT"));
            beep();
            return;
        }

        table = "LOG REPORT: \r\n" ;                         //             -       -       -       -       -       -       -       -       -       -       -       -       -       -       -       -
        table += " START\tEND\tmodel\tQuantity\tSH%\tFH%\tSand\tFraction\tCement\tDust\tWater\tR.Sand\tR.Fraction\tR.Cement\tR.Dust\tR.Water\tCorDry\tCorWat\tExitStatus \r\n";
        //DEMO ДЕМО
        while(qry.next())
        {
            QString name;
            QString qs;
            name =  qry.value(2).toString().leftJustified(12,' ');  //име

            //в този низ се подготвя съдържанието на файла с табличен вид
            table += qry.value(0).toString() //start
                 +'\t' + qry.value(1).toString() //stop
                 +'\t' + name
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

   //              +'\t'  + qry.value(10).toString() //корекция материали
  //          +'\t'  + qry.value(11).toString() //корекция вода
  //          +'\t'  + qry.value(12).toString(); //статус

                ////Коригирани материали

                 if(qry.value(16)==1) table += "\tY";
                 else table+= "\tN";
                 //коригирана вода
                 if(qry.value(17)==1) table += "\tY";
                 else table+= "\tN";

                 switch(qry.value(18).toInt(&ok))
                 {
                 case 0:
                     table+="\tNormal exit";
                     break;
                 case 1:
                     table+="\tManual abort";
                     break;
                 case 2:
                     table+="\tHardware Failure";
                     break;
                 case 3:
                     table+="\tPower down";
                     break;
                 default:
                     table+="\tUnknown";
                     break;
                 }
                 table += "\r\n";
/////////////////////////////////////////////////////////////////////////////////////////////////
                //Запълва се текстовото поле
                 ui->textEdit->append(tr("Заявка от: ") + qry.value(0).toString() + tr("  Приключена:") + qry.value(1).toString());
                 ui->textEdit->append(QString(tr("Бетон %1  %2 м3. ")).arg(name).arg(qry.value(3).toString()));
                 ui->textEdit->append(QString(tr("Влажност на пясъка %1%. Влажност на фракция %2%")).arg(qry.value(4).toString()).arg(qry.value(5).toString()));
                 qs = tr("Корекция на материали:");
                 if(qry.value(16)==1) qs += tr("ДА");
                 else qs+= tr("НЕ");
                 qs += tr("   Корекция на вода:");
                 if(qry.value(17)==1) qs += tr("ДА");
                 else qs+= tr("НЕ");
                 ui->textEdit->append(qs);
                 qs=tr("Статус:");
                 switch(qry.value(18).toInt(&ok))
                 {
                 case 0:
                     qs +=tr("Нормално завършена");
                     break;
                 case 1:
                     qs+=tr("Прекратена");
                     break;
                 case 2:
                     qs+=tr("Технически проблем");
                     break;
                 case 3:
                     qs+=tr("Прекъснато ел.захранване");
                     break;
                 default:
                     qs+=tr("Неизвестен");
                     break;
                 }
                 ui->textEdit->append(qs);
                 ui->textEdit->append(QString(tr("Вложени материали:   Пясък:%1  Фракция:%2  Цимент:%3  Пепелина:%4  Вода:%5"))
                                      .arg(qry.value(6).toString()) //пясък
                                      .arg(qry.value(7).toString()) //фракция
                                      .arg(qry.value(8).toString()) //цилмент
                                      .arg(qry.value(9).toString()) //пепелина
                                      .arg(qry.value(10).toString()) //вода
                                      );
                 ui->textEdit->append(QString(tr("Материали по задание:Пясък:%1  Фракция:%2  Цимент:%3  Пепелина:%4  Вода:%5"))
                                      .arg(qry.value(11).toString()) //пясък
                                      .arg(qry.value(12).toString()) //фракция
                                      .arg(qry.value(13).toString()) //цилмент
                                      .arg(qry.value(14).toString()) //пепелина
                                      .arg(qry.value(15).toString()) //вода
                                      );
                 ui->textEdit->append("-----------------------------------------------------------------------------------------");
             }

        if(ui->textEdit->toPlainText() == "") ui->btnSave->setEnabled(false);
        else ui->btnSave->setEnabled(true);

    }

    showReport= !showReport;
    this->setCursor(QCursor(Qt::BlankCursor));
}

void DialogReport::onExit()
{
#ifdef TAKE_SCREENSHOTS
    takeScreenShot();
#endif

    beep();
    this->accept();
}

void DialogReport::beep()
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

#ifdef TAKE_SCREENSHOTS
void DialogReport::takeScreenShot()
{
    QPixmap screen;
    QString format = "png";

    screen = QPixmap::grabWindow(QApplication::desktop()->winId());
    screen.save(QString("/sdcard/report.png"),format.toAscii());
}
#endif
