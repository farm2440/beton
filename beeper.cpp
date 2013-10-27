#include "beeper.h"

Beeper::Beeper(QObject *parent) :  QObject(parent)
{
    buzzer = new GPIO(PIN31);
}

Beeper::~Beeper()
{

    delete buzzer;
}

void Beeper::beep(int milliseconds)
{
    buzzer->openPin();
    buzzer->setDirection(GPIO::Out);
    time.restart();
    buzzer->setState(true);
    while(time.elapsed()<milliseconds){qApp->processEvents();}
    buzzer->setState(false);
    buzzer->closePin();
}
