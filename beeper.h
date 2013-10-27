#ifndef BEEPER_H
#define BEEPER_H

#include <QObject>
#include <QApplication>
#include <QTime>
#include "gpio.h"

class Beeper : public QObject
{
Q_OBJECT
public:
    explicit  Beeper(QObject *parent = 0);
    ~Beeper();

private:
    QTime time;
    GPIO *buzzer;


signals:

public slots:
    void beep(int milliseconds = 25);
};

#endif // BEEPER_H
