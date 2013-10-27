#include "dialogselectconcrete.h"
#include "ui_dialogselectconcrete.h"




/*
//диалог за избор на рецепта на бетона. Появяа се след натискане на бутона "Заявка" от главното меню.
//Рецепштите са в папка /sdcard/recepti  Всяка рецепта е файл с разширение .bet, количествата в нея са за 1/2 кубик бетон. Има следния формат:

model=B0003
sand=122
cement=132
water=142
peplina=152
fraction=162
time=8

Водата е в литри. Останалите материали в килограми. времето на разбъркване е в минути
*/

DialogSelectConcrete::DialogSelectConcrete(QWidget *parent) :    QDialog(parent),    ui(new Ui::DialogSelectConcrete)
{
    ui->setupUi(this);

    sand=0,cement=0,water=0,pepelina=0,fraction=0,time=0, name="";

    quantity=0;
    //управление на количеството става с допълнителни бутони за да са удобни при натискане с пръсти
    connect(ui->btnEditVolume,SIGNAL(clicked()),this,SLOT(onEditVolume()));
    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(onOK()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(onCancel()));

    connect(ui->listWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(beep()));

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(listSelectionChanged(int)));

    // *** -= КИРИЛИЗАЦИЯ !!! =- ***
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //Скцията е за ползване на iniparser с един файл за всички рецепти
    char * fn = new char[40];
    strcpy(fn,"/sdcard/recepti/recepti.bet");
    dict = iniparser_load(fn);
    if(dict == NULL)
    {
        QMessageBox::information(this,"iniparser library",QString("Failed to load dictionary from file:\n%1").arg(fn));
        return;
    }

    int n = iniparser_getnsec(dict);
    //QMessageBox::information(this,QString("iniparser"),QString("%1 sections found from file: %2").arg(n).arg(fn));
    if(n>0)
    {
        for(int i =0 ; i<n ; i++)
        {
            QString str(iniparser_getsecname(dict,i));
            ui->listWidget->addItem(tr(str.toLatin1()));
        }
        ui->listWidget->item(0)->setSelected(true);
    }

    ui->lblHumiditySand->setText(QString(tr("Пясък: %1 %").arg(globals.HumiditySand)));
    ui->lblHumidityFraction->setText(QString(tr("Фракция: %1 %").arg(globals.HumidityFraction)));

}

DialogSelectConcrete::~DialogSelectConcrete()
{
    if(dict!=NULL)     iniparser_freedict(dict);
    delete ui;
}

void DialogSelectConcrete::changeEvent(QEvent *e)
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

void DialogSelectConcrete::listSelectionChanged(int row)
{//при избор на рецепта от списъка в десния екран се показва съдържанието и

    //тази секция е за ползване на iniparser и един файл за всички рецепти
    QString msg("");
    QString section(iniparser_getsecname(dict,row));
    name = section;

    QString key=QString("%1:sand").arg(section);
    sand=iniparser_getint(dict,key.toAscii().data(),0);
    if(sand<=0) msg += QString(tr("Некоректно количество пясък!\n"));

    key=QString("%1:pepelina").arg(section);
    pepelina=iniparser_getint(dict,key.toAscii().data(),0);
    if(pepelina<0) msg += QString(tr("Некоректно количество пепелина!\n"));

    key=QString("%1:fraction").arg(section);
    fraction=iniparser_getint(dict,key.toAscii().data(),0);
    if(fraction<=0) msg += QString(tr("Некоректно количество фракция!\n"));

    key=QString("%1:cement").arg(section);
    cement=iniparser_getint(dict,key.toAscii().data(),0);
    if(cement<=0) msg += QString(tr("Некоректно количество цимент!\n"));

    key=QString("%1:water").arg(section);
    water=iniparser_getint(dict,key.toAscii().data(),0);
    if(water<=0) msg += QString(tr("Некоректно количество вода!\n"));

    key=QString("%1:time").arg(section);
    time=iniparser_getint(dict,key.toAscii().data(),0);
    if(time<=0) msg += QString(tr("Некоректно време на разбъркване!\n"));

    if(msg.length())
    {
        beep();
        QMessageBox::critical(this,tr("ГРЕШКА!"),msg);
        beep();
    }

    ui->textBrowser->clear();
    ui->textBrowser->append(QString(tr("Модел бетон: %1")).arg(tr(section.toLatin1())));
    ui->textBrowser->append(QString(tr("Пясък    \t: %1").arg(sand)));
    ui->textBrowser->append(QString(tr("Цемент   \t: %1")).arg(cement));
    ui->textBrowser->append(QString(tr("Фракция  \t: %1")).arg(fraction));
    ui->textBrowser->append(QString(tr("Пепелина \t: %1")).arg(pepelina));
    ui->textBrowser->append(QString(tr("Вода     \t: %1")).arg(water));
    ui->textBrowser->append(QString(tr("Време    \t: %1")).arg(time));
}

void DialogSelectConcrete::onEditVolume()
{
    //screenshot
#ifdef TAKE_SCREENSHOTS
    takeScreenShot();
#endif

    beep();
    DialogDigitalKeyboard *dlg = new DialogDigitalKeyboard();
    if(dlg->exec())
    {
        ui->btnEditVolume->setText(QString(tr("%1 куб.").arg(dlg->getValue())));
        quantity = dlg->getValue();
    }

    delete dlg;
}

void DialogSelectConcrete::onCancel()
{
    beep();
    this->reject();
}

void DialogSelectConcrete::onOK()
{
    beep();

    if(quantity==0)
    {
        QMessageBox::critical(this,tr("ГРЕШКА!"),tr("Не е зададено количество."));
        return;
    }

    //Стойности от оригиналната рецепта за един кубик
    currentRecepie.Cement = (double) cement;
    currentRecepie.Fraction = (double) fraction;
    currentRecepie.Pepelina = (double) pepelina;
    currentRecepie.Sand = (double) sand;
    currentRecepie.Time = time;
    currentRecepie.Water = (double) water;
    currentRecepie.Quantity = quantity;
    currentRecepie.Name = name;

    currentRecepie.CementCor = currentRecepie.Cement;
    currentRecepie.PepelinaCor = currentRecepie.Pepelina;
    currentRecepie.TimeCor = currentRecepie.Time;

    currentRecepie.CorrectionDry = false;
    currentRecepie.CorrectionWater = false;

    //пресмятане на стойностите за едно бъркало
    //Разделя се количеството на обема на едно бъркало. Получава се брой цели бъркала N и остатък последно непълно бъркало M.
    //Правят равни N+1 бъркала с непълен обем.
    double N, Ni, M, U;
    N= (currentRecepie.Quantity / globals.MixerVolume);
    M = modf(N,&Ni); //в Ni се получава цялата част на N - броя на бъркалата
    if(M>0.05) Ni++;

    currentRecepie.MixNumber = (int) Ni;
    U = (currentRecepie.Quantity * 100) / (Ni * globals.MixerVolume); //Процентна запълненост на едно бъркало

    //Коригирани стойности - корекция с влажността.
    currentRecepie.FractionCor = (currentRecepie.Fraction*100) / (100 - globals.HumidityFraction);
    currentRecepie.SandCor = (currentRecepie.Sand*100) / (100 - globals.HumiditySand);
    currentRecepie.WaterCor = currentRecepie.Water
                              - (currentRecepie.FractionCor - currentRecepie.Fraction)
                              - (currentRecepie.SandCor - currentRecepie.Sand);
    //количество съставки за едно бъркало
    currentRecepie.MixCement = (currentRecepie.CementCor * currentRecepie.Quantity) / Ni;
    currentRecepie.MixPepelina = (currentRecepie.PepelinaCor * currentRecepie.Quantity) / Ni;
    currentRecepie.MixFraction = (currentRecepie.FractionCor * currentRecepie.Quantity) / Ni;
    currentRecepie.MixSand = (currentRecepie.SandCor * currentRecepie.Quantity) / Ni;
    currentRecepie.MixWater = (currentRecepie.WaterCor * currentRecepie.Quantity) / Ni;
    if(currentRecepie.MixWater < 2) currentRecepie.MixWater = 2;

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

    qDebug() << "\nSelected recepie: " << currentRecepie.Name << " for " << currentRecepie.Quantity << " m3";
    qDebug() << "Cement=" << currentRecepie.Cement << " Pepelina=" << currentRecepie.Pepelina << " Fraction=" << currentRecepie.Fraction << " Sand=" << currentRecepie.Sand << " Water=" << currentRecepie.Water <<" Time=" << currentRecepie.Time;
    qDebug() << "After humidity correction:" ;
    qDebug() << "Sand Humidity:" << globals.HumiditySand << "%   Fraction Humidity:"<< globals.HumidityFraction ;
    qDebug() << "Fraction=" << currentRecepie.FractionCor << " Sand=" << currentRecepie.SandCor << " Water=" << currentRecepie.WaterCor;
    qDebug() << "Mix Number=" << currentRecepie.MixNumber << " filled to " << U << "%";
    qDebug() << "Ingradients for one mix portion:" ;
    qDebug() << "Cement=" << currentRecepie.MixCement << " Pepelina=" << currentRecepie.MixPepelina
             << " Fraction=" << currentRecepie.MixFraction << " Sand=" << currentRecepie.MixSand
             << " Water=" << currentRecepie.MixWater <<"\n";

    this->accept();
}

void DialogSelectConcrete::beep()
{
    //qApp->beep();

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
void DialogSelectConcrete::takeScreenShot()
{
    QPixmap screen;
    QString format = "png";

    screen = QPixmap::grabWindow(QApplication::desktop()->winId());
    screen.save(QString("/sdcard/select.png"),format.toAscii());
}
#endif
