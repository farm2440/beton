#ifndef DIALOGSELECTCONCRETE_H
#define DIALOGSELECTCONCRETE_H

#include <QDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>


#include <math.h>

#include "gpio.h"
#include "formula.h"
#include "dictionary.h"
#include "iniparser.h"
#include "dialogdigitalkeyboard.h"

#include "beton.h"

//за screenshot-a
#ifdef TAKE_SCREENSHOTS
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#endif

extern RecepieStruct currentRecepie;
extern GlobalSettingsStruct globals;

/*
//диалог за избор на рецепта на бетона. Появяа се след натискане на бутона "Заявка" от главното меню.
//Рецепштите са в папка /sdcard/recepti  Всяка рецепта е файл с разширение .bet, количествата в нея са за 1/2 кубик бетон. Има следния формат:

model=B0003
sand=122
cement=132
water=142
peplina=152
fraction=162

Водата е в литри. Останалите материали в килограми.

*/

namespace Ui {
    class DialogSelectConcrete;
}

class DialogSelectConcrete : public QDialog {
    Q_OBJECT
public:
    DialogSelectConcrete(QWidget *parent = 0);
    ~DialogSelectConcrete();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogSelectConcrete *ui;
    dictionary *dict; //ползва се от iniparser. в него се зарежда съдържанието на отворения ini файл

    int sand,cement,water,pepelina,fraction,time;
    QString name;
    double quantity;

private slots:
    void beep();
    void listSelectionChanged(int row);
    void onEditVolume();
    void onOK();
    void onCancel();
#ifdef TAKE_SCREENSHOTS
    void takeScreenShot();
#endif
};

#endif // DIALOGSELECTCONCRETE_H
