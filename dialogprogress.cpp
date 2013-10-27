#include "dialogprogress.h"
#include "ui_dialogprogress.h"

DialogProgress::DialogProgress(QWidget *parent) :  QDialog(parent),  ui(new Ui::DialogProgress)
{
    ui->setupUi(this);

    bool ready = false;
    QString strUmount("umount /dev/udisk");
    QString strMount("mount /dev/udisk /udisk");

    int exitCode;
    QProcess *proc = new QProcess(this);
    QTime time;

    while(!ready)
    {
        //демонтирам и отново монтирам флашката във файловата система.Така ако последната операция е успешна
        //се уверявам, че флашката е поставена.
        //unmount
        exitCode = proc->execute(strUmount);
        //mount and check the  exit code
        exitCode = proc->execute(strMount);

        if(exitCode==0){ ready=true; }
        else
        {
            if(time.elapsed()>6000)
            {//проверка за таймаут
                QMessageBox::critical(this,tr("ГРЕШКА"),tr("Външна USB памет не може да бъде открита"));
                //beep();
                if(proc!=NULL) delete proc;
                return;
            }
        }
//!!!!!!
        qApp->processEvents();
    }
}

DialogProgress::~DialogProgress()
{
    delete ui;
}

void DialogProgress::changeEvent(QEvent *e)
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
