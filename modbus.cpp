#include "modbus.h"

modbus::modbus()
{
    isOpened=false;
}

modbus::~modbus()
{

}

unsigned short modbus::GetCRC(QByteArray message)
{
    //Function expects a modbus message of any length
    // 2 byte CRC returned src-h crc-l
    ushort CRCFull=0xFFFF;
    uchar CRCLSB;

    for(int i = 0 ; i<message.count() - 2 ; i++)
    {
        CRCFull = (ushort)(CRCFull ^ message[i]);

        for(int j=0 ; j<8 ; j++)
        {
            CRCLSB = (uchar)(CRCFull & 0x0001);
            CRCFull = (ushort)((CRCFull>>1) & 0x7FFF);
            if(CRCLSB==1) CRCFull = (ushort)(CRCFull ^ 0xA001);
        }
    }
    return CRCFull;
}

bool modbus::Open(QString portName, uint baudRate, int databits, SerialPort::Parity parity, int stopBits)
{//отваря и настройва серииния порт за modbus. При успех връща true иначе false.
    int h = sp.sp_open(portName.toLocal8Bit().data());
    if(h==-1) return false;

    h = sp.sp_setPort(baudRate,databits,parity,stopBits);
    if(h==-1) return false;

    sp.sp_stopRxTimer();
    isOpened=true;
    return true;
}

int modbus::Close()
{
    isOpened=sp.sp_close();
    return isOpened;
}

bool modbus::SendFc3(uchar address, ushort start, ushort registers, QByteArray &values)
{//Function 3 - Read Registers
    //Изпраща се запитване за стойност на регистрите в устройство  address.
    //Броят е посоченв registers а номера на началния регистър е start
    //Резултатът се връща във values
    if(!isOpened) return false; //порта не е отворен.

    bool to;
    unsigned short crc;
    QByteArray message;
    //Function 3 request is always 8 bytes:
    message.resize(8);
    //Function 3 response buffer:
    values.resize(5+2*registers);
    //Build outgoing modbus message:
    message[0] =address;
    message[1] = 3;
    message[2] = (uchar)(start >> 8);
    message[3] = (uchar)start;
    message[4] = (uchar)(registers >> 8);
    message[5] = (uchar)registers;

    crc=GetCRC(message);
    message[message.count()-2] = (ushort) (crc & 0xFF);
    message[message.count()-1] = (ushort) ((crc>>8)&0xFF);

    //Send modbus message to Serial Port:
    sp.sp_clearRxBuffer();
    sp.sp_write(message.data(),8);

    to = GetResponse(values);

    return to;
}

bool modbus::SendFc16(uchar address, ushort start, ushort registers, QByteArray &values, int &err)
{//Function 16 - write to registers
    /*Изпраща се съобщение:
      address 1 + func 1 + start 2 + reg 2 + count 1 + values N + crc 2
      address е адреса на устройство в modbus. func=16 - писане.
      В registers броя регистри започвайки от start се записват стойностите от values.
      Трябва да се има предвид, че modbus регистрите са 16 битови така,че
      броя байтове във values трябва да е 2 пъти по-голям от registers

      Във err се записва евентуален код на грешка. 0-ОК, 1-портът не е отворен, 2- некоректни данни, 3 - таймаут
      */
    err=0;
    if(!isOpened)  { err=1 ;  return false; }; //порта не е отворен.
    if(values.count() != (registers * 2) ) { err=2; return false; }

    bool to;
    unsigned short crc;
    QByteArray message,response;
    response.resize(8);
    message.resize(9+values.count());
    message[0] =address;
    message[1] = 16;
    message[2] = (uchar)(start >> 8);
    message[3] = (uchar)start;
    message[4] = (uchar)(registers >> 8);
    message[5] = (uchar)registers;
    message[6] = (uchar) values.count();
    message.replace(7,values.count(),values);

    crc=GetCRC(message);
    message[message.count()-2] = (ushort) (crc & 0xFF);
    message[message.count()-1] = (ushort) ((crc>>8)&0xFF);

    //Send modbus message to Serial Port:
    sp.sp_clearRxBuffer();
    sp.sp_write(message.data(),message.count());

    to= GetResponse(response);
    if(!to) err = 3;
    return to;
}

bool modbus::GetResponse(QByteArray &response)
{
    /*Функцията чете от серииния порт байтове до размера на response и ги записва в него и връща true.
      Таймера  за приемане на SerialPort е спрян. Четенето на приемния буфер става в тази функция.
      Ако времето надхвърли SP_RX_TIMEOUT то функцията връща false а в response остават байтовете
      приети до този момент. */
    if(!isOpened) return false; //порта не е отворен.

    char c[1];
    int count = 0;
    timeout.restart();

    do
    {
        qApp->processEvents();
        if(sp.sp_read(c,1)==1)
        {
            response[count]=c[0];
            count++;
            if(count==response.count()) return true; //буферът е запълнен. излизаме
        }
    }while(timeout.elapsed()<SP_RX_TIMEOUT);
    return false; //има timeout!
}

bool modbus::CheckResponse(QByteArray response)
{
    ushort crc, rcrc;
    crc = GetCRC(response);
    rcrc=(((ushort) response[response.count()-1]) <<8) + (ushort)response[response.count()-2];
    return (crc==rcrc);
}

bool modbus::IsOpened()
{
    return isOpened;
}
