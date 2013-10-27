#include "dialogselectfile.h"
#include "ui_dialogselectfile.h"

DialogSelectFile::DialogSelectFile(QWidget *parent, QStringList *fileList) :  QDialog(parent),  ui(new Ui::DialogSelectFile)
{
    ui->setupUi(this);

    ui->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(selectedFileChanged(int)));
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(beep()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(onCancel()));
    connect(ui->btnOK,SIGNAL(clicked()),this,SLOT(onOK()));
    list = fileList;
    if(fileList==NULL) return;
    foreach(QString str, *fileList)
    {
        ui->listWidget->addItem(str);
    }
    if(fileList->count())
    {
        ui->listWidget->item(0)->setSelected(true);
        selectedFileName = ui->listWidget->item(0)->text();
    }
    else selectedFileName="";
}

DialogSelectFile::~DialogSelectFile()
{
    delete ui;
}

void DialogSelectFile::onCancel()
{
    beep();
    this->reject();
}

void DialogSelectFile::onOK()
{
    beep();
    this->accept();
}

void DialogSelectFile::changeEvent(QEvent *e)
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

void DialogSelectFile::setFileList(QStringList *fileList)
{
    list=fileList;
    if(fileList==NULL) return;
    foreach(QString str, *fileList)
    {
        ui->listWidget->addItem(str);
    }

    if(fileList->count())
    {
        ui->listWidget->item(0)->setSelected(true);
        selectedFileName = ui->listWidget->item(0)->text();
    }
    else selectedFileName="";
}

QString DialogSelectFile::getSelectedFileName()
{
    return selectedFileName;
}

void DialogSelectFile::selectedFileChanged(int row)
{
    selectedFileName=ui->listWidget->item(row)->text();
}

void DialogSelectFile::beep()
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

