#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>
#include <QByteArray>
#include <QApplication>
#include <QTime>

#include "serialport.h"

#define SP_RX_TIMEOUT 600  //timeot in milliseconds
class modbus : public QObject
{
    Q_OBJECT

private:
    SerialPort sp;
    QTime timeout;
    bool isOpened;

public:
    modbus();
    ~modbus();
    ushort GetCRC(QByteArray message);
    bool Open(QString portName, uint baudRate, int databits,  SerialPort::Parity parity , int stopBits);
    int Close();
    bool SendFc3(uchar address, ushort start, ushort registers, QByteArray &values);
    bool SendFc16(uchar address, ushort start, ushort registers, QByteArray &values, int &err);
    bool GetResponse(QByteArray &response);
    bool CheckResponse(QByteArray response);
    bool IsOpened();
};

#endif // MODBUS_H
