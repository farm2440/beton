#include "dialogrecepti.h"
#include "ui_dialogrecepti.h"

DialogRecepti::DialogRecepti(QWidget *parent) :    QDialog(parent),    ui(new Ui::DialogRecepti)
{
    ui->setupUi(this);

    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->btnOpenFile,SIGNAL(clicked()),this,SLOT(onOpenFile()));
    connect(ui->btnExit,SIGNAL(clicked()),this,SLOT(onExit()));

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
            ui->listWidget->addItem(str.toUpper());
        }
        ui->listWidget->item(0)->setSelected(true);
    }
}

void DialogRecepti::onOpenFile()
{
    beep();
    // *** -= КИРИЛИЗАЦИЯ !!! =- ***
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    QFileDialog *dlg= new QFileDialog(this,QString(tr("Избор на файл")),"/udisk",QString("File(*.bet)"));
    dlg->setWindowIcon(QIcon(":/res/wheel-0.png"));
    dlg->exec();
    beep();
    delete dlg;

    //QString fileName = QFileDialog::getOpenFileName(this,tr("Избор на файл"),"/udisk",QString("File(*.bet)"));
}

DialogRecepti::~DialogRecepti()
{
    delete ui;
}

void DialogRecepti::changeEvent(QEvent *e)
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

void DialogRecepti::onExit()
{
    beep();
    accept();
}

void DialogRecepti::beep()
{//функция за звук при натискане на бутон
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
