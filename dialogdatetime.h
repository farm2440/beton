#ifndef DIALOGDATETIME_H
#define DIALOGDATETIME_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <QProcess>
#include <QStringList>
#include <QMessageBox>

#include "gpio.h"
#include "formula.h"

namespace Ui {
    class DialogDateTime;
}

class DialogDateTime : public QDialog {
    Q_OBJECT
public:
    DialogDateTime(QWidget *parent = 0);
    ~DialogDateTime();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DialogDateTime *ui;

    //other
    QTimer clockTimer; //таймер за обновяване на часовника
    QProcess *proc;


private slots:
    void clockTick(); //Date/Time update
public slots:
    void updateEditTime(QTime time, QDate date);
    void onAccept();
    void onReject();
    void beep();
};

#endif // DIALOGDATETIME_H
