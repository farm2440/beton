#include "dialogdatetime.h"
#include "ui_dialogdatetime.h"

DialogDateTime::DialogDateTime(QWidget *parent) :    QDialog(parent),    ui(new Ui::DialogDateTime)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint); //no resize, minimize buttons

    connect(ui->btnTimeUp,SIGNAL(clicked()),ui->timeEdit,SLOT(stepUp()));
    connect(ui->btnTimeUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnTimeDown,SIGNAL(clicked()),ui->timeEdit,SLOT(stepDown()));
    connect(ui->btnTimeDown,SIGNAL(clicked()),this,SLOT(beep()));

    connect(ui->btnDateUp,SIGNAL(clicked()),ui->dateEdit,SLOT(stepUp()));
    connect(ui->btnDateUp,SIGNAL(clicked()),this,SLOT(beep()));
    connect(ui->btnDateDown,SIGNAL(clicked()),ui->dateEdit,SLOT(stepDown()));
    connect(ui->btnDateDown,SIGNAL(clicked()),this,SLOT(beep()));

    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(onAccept()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(onReject()));
    //Date/Time update
    connect(&clockTimer,SIGNAL(timeout()),this,SLOT(clockTick()));
    clockTimer.start(1000);

     proc = new QProcess(this);
}

DialogDateTime::~DialogDateTime()
{
    if(proc!=NULL) delete proc;
    delete ui;
}

void DialogDateTime::changeEvent(QEvent *e)
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

void DialogDateTime::clockTick()
{
    QDate dt;
    QTime tm;
    tm=QTime::currentTime();
    dt=QDate::currentDate();
    ui->lblDateTime->setText(dt.toString() +"  " + tm.toString());
}


void DialogDateTime::updateEditTime(QTime time, QDate date)
{
    //функцията се вика преди показване на диалога за да са актуални показанията в контролите за редактиране
    ui->timeEdit->setTime(time);
    ui->dateEdit->setDate(date);
}

void DialogDateTime::onAccept()
{//Set system time using QProcess and /bin/date
    beep();

    int M,D,Y,Hour,Min,Sec;
    QString str;

    D=ui->dateEdit->date().day();
    M=ui->dateEdit->date().month();
    Y=ui->dateEdit->date().year();

    Hour=ui->timeEdit->time().hour();
    Min=ui->timeEdit->time().minute();
    Sec=ui->timeEdit->time().second();

    //YYYY-MM-DD hh:mm[:ss]  /opt/Qtopia/bin/systemtime
    //настройва се системното време
    str = QString("date -s %1.%2.%3-%4:%5:%6").arg(Y).arg(M).arg(D).arg(Hour).arg(Min).arg(Sec);
    //proc->start(str);
    proc->execute(str);
    //хардуерния часовник се настройва по системното време. Това се прави за да се запази часа след рестарт
    str = "hwclock -w";
    proc->execute(str);

    this->accept();
}

void DialogDateTime::onReject()
{
    beep();
    this->reject();
}

void DialogDateTime::beep()
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
