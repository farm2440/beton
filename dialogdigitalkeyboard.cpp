#include "dialogdigitalkeyboard.h"
#include "ui_dialogdigitalkeyboard.h"

DialogDigitalKeyboard::DialogDigitalKeyboard(QWidget *parent) :   QDialog(parent),    ui(new Ui::DialogDigitalKeyboard)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();

    connect(ui->btn_0,SIGNAL(clicked()),this,SLOT(onBtn0()));
    connect(ui->btn_1,SIGNAL(clicked()),this,SLOT(onBtn1()));
    connect(ui->btn_2,SIGNAL(clicked()),this,SLOT(onBtn2()));
    connect(ui->btn_3,SIGNAL(clicked()),this,SLOT(onBtn3()));
    connect(ui->btn_4,SIGNAL(clicked()),this,SLOT(onBtn4()));
    connect(ui->btn_5,SIGNAL(clicked()),this,SLOT(onBtn5()));
    connect(ui->btn_6,SIGNAL(clicked()),this,SLOT(onBtn6()));
    connect(ui->btn_7,SIGNAL(clicked()),this,SLOT(onBtn7()));
    connect(ui->btn_8,SIGNAL(clicked()),this,SLOT(onBtn8()));
    connect(ui->btn_9,SIGNAL(clicked()),this,SLOT(onBtn9()));

    connect(ui->btn_dot,SIGNAL(clicked()),this,SLOT(onBtndot()));
    connect(ui->btn_Backspace,SIGNAL(clicked()),this,SLOT(onBtnbackspace()));
    connect(ui->btn_OK,SIGNAL(clicked()),this,SLOT(onBtnOK()));
    connect(ui->btn_Cancel,SIGNAL(clicked()),this,SLOT(onBtnCancel()));

}

DialogDigitalKeyboard::~DialogDigitalKeyboard()
{
    delete ui;
}

void DialogDigitalKeyboard::changeEvent(QEvent *e)
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

double DialogDigitalKeyboard::getValue()
{
    return _value;
}

void DialogDigitalKeyboard::onBtnOK()
{
    beep();
    bool ok;
    _value = ui->lineEdit->text().toDouble(&ok);
    if(ok)   this->accept();
    else QMessageBox::critical(this,tr("ГРЕШКА"),tr("Зададена е некоректна стойност!"));
}

void DialogDigitalKeyboard::onBtnCancel()
{
    beep();
    this->reject();
}

void DialogDigitalKeyboard::onBtndot()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text())
    {
        ui->lineEdit->setText("0.");; // Ако целия текст е селектиран изписва се 0.
        return;
    }
    if(ui->lineEdit->text().contains('.'))  return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_Comma,Qt::NoModifier,".");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_Comma,Qt::NoModifier, ".");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtnbackspace()
{
    beep();
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_Backspace,Qt::NoModifier,"");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_Backspace,Qt::NoModifier, "");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn0()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_0,Qt::NoModifier,"0");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_0,Qt::NoModifier, "0");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn1()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_1,Qt::NoModifier,"1");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_1,Qt::NoModifier, "1");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn2()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_2,Qt::NoModifier,"2");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_2,Qt::NoModifier, "2");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn3()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_3,Qt::NoModifier,"3");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_3,Qt::NoModifier, "3");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn4()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_4,Qt::NoModifier,"4");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_4,Qt::NoModifier, "4");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn5()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_5,Qt::NoModifier,"5");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_5,Qt::NoModifier, "5");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn6()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_6,Qt::NoModifier,"6");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_6,Qt::NoModifier, "6");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn7()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_7,Qt::NoModifier,"7");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_7,Qt::NoModifier, "7");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn8()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_8,Qt::NoModifier,"8");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_8,Qt::NoModifier, "8");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::onBtn9()
{
    beep();
    if(ui->lineEdit->selectedText() == ui->lineEdit->text()) ui->lineEdit->clear(); // Ако целия текст е селектиран той се изтрива
    if(ui->lineEdit->text().right(2).startsWith('.')) return;
    QWidget * widget =focusWidget();
    QKeyEvent evn_prs(QEvent::KeyPress,Qt::Key_9,Qt::NoModifier,"9");
    QApplication::sendEvent(widget,&evn_prs);
    QKeyEvent evn_rls(QEvent::KeyRelease,Qt::Key_9,Qt::NoModifier, "9");
    QApplication::sendEvent(widget,&evn_rls);
}

void DialogDigitalKeyboard::beep()
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
