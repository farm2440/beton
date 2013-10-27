#ifndef DIALOGCHANGEINGRADIENTS_H
#define DIALOGCHANGEINGRADIENTS_H

#include <QDialog>
#include <QTime>
#include <QDebug>



#include "math.h"

#include "gpio.h"
#include "beton.h"

#ifdef TAKE_SCREENSHOTS
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>
#endif

extern RecepieStruct currentRecepie;
extern GlobalStateStruct states;
extern GlobalSettingsStruct globals;

namespace Ui {
    class DialogChangeIngradients;
}

class DialogChangeIngradients : public QDialog {
    Q_OBJECT
public:
    DialogChangeIngradients(QWidget *parent = 0);
    ~DialogChangeIngradients();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogChangeIngradients *ui;

    //в тези променливи се запазват първоначалните стойности. При излизане ако има промяна се вдига съответния флаг в currentRecepie
    int _cement, _fraction, _sand, _pepelina, _water;

private slots:
    void onAccept();
    void onReject();
    void beep();

#ifdef TAKE_SCREENSHOTS
    void takeScreenShot();
#endif
};

#endif // DIALOGCHANGEINGRADIENTS_H
