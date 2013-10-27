#ifndef DIALOGDIGITALKEYBOARD_H
#define DIALOGDIGITALKEYBOARD_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTime>

#include "gpio.h"

namespace Ui {
    class DialogDigitalKeyboard;
}

class DialogDigitalKeyboard : public QDialog {
    Q_OBJECT
public:
    DialogDigitalKeyboard(QWidget *parent = 0);
    ~DialogDigitalKeyboard();

    double getValue();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogDigitalKeyboard *ui;

    double _value;

private slots:
    void beep();

    void onBtn1();
    void onBtn2();
    void onBtn3();
    void onBtn4();
    void onBtn5();
    void onBtn6();
    void onBtn7();
    void onBtn8();
    void onBtn9();
    void onBtn0();
    void onBtnbackspace();
    void onBtndot();

    void onBtnOK();
    void onBtnCancel();
};

#endif // DIALOGDIGITALKEYBOARD_H
