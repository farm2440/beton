/****************************************************************************
** Scale class
**
** Created: 26 JUL 2010
**      by:  Svilen Stavrev
**
** This class performs communication to various types of scales defined in ScaleType enum.
** call getWeight(). Then check isDataOK(). If it returns false getErrMessage() will return
** explanation of the failure. If it returns true the value for weight is correct. getUnit returns
** mesurement units as reported from the scale.
** 
** History:
** 	05 Dec 2010: added new scale type SCALE_TYPE_WE2108
****************************************************************************/
#ifndef SCALE_H
#define SCALE_H

#include <qobject.h>
#include <qstring.h>
#include <qdatetime.h>
#include <qlabel.h>
#include <qapplication.h>
#include <qstringlist.h>
#include "serialport.h"
#include <termios.h>
#include <qtextcodec.h>

class Scale : public QObject
{
	
    Q_OBJECT
public:
	enum ScaleType {SCALE_TYPE_FI6, SCALE_TYPE_PUE, SCALE_TYPE_BIMCO, SCALE_TYPE_ELICOM, SCALE_TYPE_BIZERBA_ST, SCALE_TYPE_VEDIA, SCALE_TYPE_ELICOM_ETS, SCALE_TYPE_WE2108, SCALE_TYPE_UNKNOWN};
	
        Scale();
	~Scale();
	
        double getWeight(bool &OK); //return the weight in units. return -1 on error
	QString getUnit(); //return units. empty string on err
	QString getErrMessage(); 

        //Извлича теглото от отговора от везната
        bool scale_ParseWeight(QByteArray response, double &weight, bool &stable ,QString &units);

        bool    scale_Write(QString str);
        bool    scale_Write(QByteArray arr); //write data to scale. Return true on success else return false

        //TODO: Да се преработи с qstring!
	static ScaleType getTypeByString(char * typeName); //функцията приема низ с името на везната и връща ScaleType. ако не разпознае типа връща SCALE_TYPE_UNKNOWN

	bool isDataOK(); //are weight and unit values correct
	
        bool scale_isOpen();
        bool scale_Open(QString portName, uint baudRate, int databits, SerialPort::Parity parity, int stopBits, ScaleType scaleType, int timeoutmsec);
        bool scale_getResponse(QByteArray & response);
        bool scale_isStable();

private:
        SerialPort sp;
	QTime time;  //used for timeout control
	QString errMessage; //if communication error occure this string gives extensive explanation
	QString unit; //unit - kg,g,lb etc.
	ScaleType type;
        int timeout; //in milliseconds
	bool dataFlag; //cleared when data expected. set by dataRecieved when data with weight is available
	bool dataOK; //correct data flag
	
	double weight; 
	QStringList strList;

        bool isOpen;
        bool isStable;
};
#endif //SCALE_H
