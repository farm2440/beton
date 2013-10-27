#include "dialogchangeingradients.h"
#include "ui_dialogchangeingradients.h"

DialogChangeIngradients::DialogChangeIngradients(QWidget *parent) : QDialog(parent), ui(new Ui::DialogChangeIngradients)
{
    ui->setupUi(this);

    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(onReject()));
    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(onAccept()));

    connect(ui->btnCementDwn,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnCementUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnFractionDwn,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnFractionUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnPepelinaDwn,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnPepelinUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnSandDwn,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnSandUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnTimeDwn,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnTimeUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnWaterDwn,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnWaterUp,SIGNAL(clicked()),this,SLOT(beep()));

    connect(ui->btnCementDwn,SIGNAL(clicked()),ui->spinCement,SLOT(stepDown()));
    connect(ui->btnCementUp,SIGNAL(clicked()),ui->spinCement,SLOT(stepUp()));
    connect(ui->btnFractionDwn,SIGNAL(clicked()),ui->spinFraction,SLOT(stepDown()));
    connect(ui->btnFractionUp,SIGNAL(clicked()),ui->spinFraction,SLOT(stepUp()));
    connect(ui->btnPepelinaDwn,SIGNAL(clicked()),ui->spinPepelina,SLOT(stepDown()));
    connect(ui->btnPepelinUp,SIGNAL(clicked()),ui->spinPepelina,SLOT(stepUp()));
    connect(ui->btnSandDwn,SIGNAL(clicked()),ui->spinSand,SLOT(stepDown()));
    connect(ui->btnSandUp,SIGNAL(clicked()),ui->spinSand,SLOT(stepUp()));
    connect(ui->btnTimeDwn,SIGNAL(clicked()),ui->spinTime,SLOT(stepDown()));
    connect(ui->btnTimeUp,SIGNAL(clicked()),ui->spinTime,SLOT(stepUp()));
    connect(ui->btnWaterDwn,SIGNAL(clicked()),ui->spinWater,SLOT(stepDown()));
    connect(ui->btnWaterUp,SIGNAL(clicked()),ui->spinWater,SLOT(stepUp()));

    ui->lblTimeMinmax->setText(QString(tr("%1/%2 сек.")).arg(globals.MinTime).arg(globals.MaxTime));
    ui->lblSandMinmax->setText(QString("%1/%2").arg(globals.MinSand).arg(globals.MaxSand));
    ui->lblWaterMinmax->setText(QString("%1/%2").arg(globals.MinWater).arg(globals.MaxWater));
    ui->lblCementMinmax->setText(QString("%1/%2").arg(globals.MinCement).arg(globals.MaxCement));
    ui->lblFractionMinmax->setText(QString("%1/%2").arg(globals.MinFraction).arg(globals.MaxFraction));
    ui->lblPepelinaMinmax->setText(QString("%1/%2").arg(globals.MinPepelina).arg(globals.MaxPepelina));

    ui->spinSand->setMinimum(globals.MinSand);     ui->spinSand->setMaximum(globals.MaxSand);    ui->spinSand->setValue((int)currentRecepie.SandCor);
    ui->spinTime->setMinimum(globals.MinTime);     ui->spinTime->setMaximum(globals.MaxTime);    ui->spinTime->setValue((int)currentRecepie.TimeCor);
    ui->spinWater->setMinimum(globals.MinWater);   ui->spinWater->setMaximum(globals.MaxWater);  ui->spinWater->setValue((int)currentRecepie.WaterCor);
    ui->spinCement->setMinimum(globals.MinCement);     ui->spinCement->setMaximum(globals.MaxCement);      ui->spinCement->setValue((int)currentRecepie.CementCor);
    ui->spinFraction->setMinimum(globals.MinFraction); ui->spinFraction->setMaximum(globals.MaxFraction);  ui->spinFraction->setValue((int)currentRecepie.FractionCor);
    ui->spinPepelina->setMinimum(globals.MinPepelina); ui->spinPepelina->setMaximum(globals.MaxPepelina);  ui->spinPepelina->setValue((int)currentRecepie.PepelinaCor);

    _cement = (int)currentRecepie.CementCor;
    _pepelina = (int)currentRecepie.PepelinaCor;
    _fraction = (int)currentRecepie.FractionCor;
    _sand = (int)currentRecepie.SandCor;
    _water = (int)currentRecepie.WaterCor;

    if(states.State != Idle)
    {
        ui->btnSandUp->setEnabled(false); ui->btnSandDwn->setEnabled(false);
        ui->btnCementUp->setEnabled(false); ui->btnCementDwn->setEnabled(false);        
        ui->btnPepelinUp->setEnabled(false); ui->btnPepelinaDwn->setEnabled(false);
        ui->btnFractionUp->setEnabled(false); ui->btnFractionDwn->setEnabled(false);

        ui->spinSand->setEnabled(false);
        ui->spinCement->setEnabled(false);
        ui->spinPepelina->setEnabled(false);
        ui->spinFraction->setEnabled(false);
    }
/*
    switch(states.State)
    {
    case Idle:
    case Paused:
    case Abort:
    case Fail:
    case Start:
    case Run:
    } */
}

DialogChangeIngradients::~DialogChangeIngradients()
{
    delete ui;
}

void DialogChangeIngradients::changeEvent(QEvent *e)
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

void DialogChangeIngradients::onReject()
{
    beep();
    this->reject();
}

void DialogChangeIngradients::onAccept()
{
#ifdef TAKE_SCREENSHOTS
    takeScreenShot();
#endif

    beep();
    bool change = false;

    //В currentRecepie се записват новите коригирани стойности. Ако е имало корекция на влажността то това вече не е валидно.
    currentRecepie.CementCor = (double) ui->spinCement->value();
    currentRecepie.FractionCor = (double) ui->spinFraction->value();
    currentRecepie.PepelinaCor = (double) ui->spinPepelina->value();
    currentRecepie.SandCor = (double) ui->spinSand->value();
    currentRecepie.TimeCor = ui->spinTime->value();
    currentRecepie.WaterCor = ui->spinWater->value();

    //проверка дали има извършени промени
    if(_cement != ui->spinCement->value()) change=true;
    if(_sand != ui->spinSand->value()) change = true;
    if(_pepelina != ui->spinPepelina->value()) change = true;
    if(_fraction != ui->spinFraction->value()) change = true;

    if(change)
    {
        qDebug() << "\nDry ingradients quantity changed!";
        currentRecepie.CorrectionDry = true;
    }

    if(_water != ui->spinWater->value())
    {
        change = true;
        currentRecepie.CorrectionWater = true;
        qDebug() << "\nWater quantity changed!";
    }

    if(!change)
    {
        qDebug() << "\nNo change has been made.";
    }
    else
    {
        //пресмятане на стойностите за едно бъркало
        //Разделя се количеството на обема на едно бъркало. Получава се брой цели бъркала N и остатък последно непълно бъркало M.
        //Правят равни N+1 бъркала с непълен обем.
        double N, Ni, M, U;
        N= (currentRecepie.Quantity / globals.MixerVolume);
        M = modf(N,&Ni); //в Ni се получава цялата част на N - броя на бъркалата
        if(M>0.05) Ni++;

        currentRecepie.MixNumber = (int) Ni;
        U = (currentRecepie.Quantity * 100) / (Ni * globals.MixerVolume); //Процентна запълненост на едно бъркало
        //количество съставки за едно бъркало
        currentRecepie.MixCement = (currentRecepie.CementCor * currentRecepie.Quantity) / Ni;
        currentRecepie.MixPepelina = (currentRecepie.PepelinaCor * currentRecepie.Quantity) / Ni;
        currentRecepie.MixFraction = (currentRecepie.FractionCor * currentRecepie.Quantity) / Ni;
        currentRecepie.MixSand = (currentRecepie.SandCor * currentRecepie.Quantity) / Ni;
        currentRecepie.MixWater = (currentRecepie.WaterCor * currentRecepie.Quantity) / Ni;


        qDebug() << "Recalculating ingradients:" ;
        qDebug() << "Selected recepie: " << currentRecepie.Name << " for " << currentRecepie.Quantity << " m3";
        qDebug() << "Cement=" << currentRecepie.Cement << " Pepelina=" << currentRecepie.Pepelina << " Fraction=" << currentRecepie.Fraction << " Sand=" << currentRecepie.Sand << " Water=" << currentRecepie.Water <<" Time=" << currentRecepie.Time;
        qDebug() << "After manual correction:" ;
        qDebug() << "Cement=" << currentRecepie.CementCor << " Pepelina=" << currentRecepie.PepelinaCor << " Fraction=" << currentRecepie.FractionCor << " Sand=" << currentRecepie.SandCor << " Water=" << currentRecepie.WaterCor <<" Time=" << currentRecepie.TimeCor;
        qDebug() << "Mix Number=" << currentRecepie.MixNumber << " filled to " << U << "%";
        qDebug() << "Ingradients for one mix portion:" ;
        qDebug() << "Cement=" << currentRecepie.MixCement << " Pepelina=" << currentRecepie.MixPepelina
                 << " Fraction=" << currentRecepie.MixFraction << " Sand=" << currentRecepie.MixSand
                 << " Water=" << currentRecepie.MixWater ;
    }
    this->accept();
}

void DialogChangeIngradients::beep()
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
void DialogChangeIngradients::takeScreenShot()
{
    QPixmap screen;
    QString format = "png";

    screen = QPixmap::grabWindow(QApplication::desktop()->winId());
    screen.save(QString("/sdcard/correction.png"),format.toAscii());
}
#endif
