#include "scale.h"

Scale::Scale()
{
        isOpen=false;
        isStable = false;
        type = Scale::SCALE_TYPE_UNKNOWN;
	unit="";
        errMessage="Port not opened";
	dataOK = false;
        timeout = 300;
}
//--------------------------------------------------------------------------------------------------
Scale::~Scale()
{
	sp.sp_close();
}
//--------------------------------------------------------------------------------------------------
bool Scale::scale_isOpen() { return isOpen; }
//--------------------------------------------------------------------------------------------------
bool Scale::scale_Open(QString portName, uint baudRate, int databits, SerialPort::Parity parity, int stopBits, ScaleType scaleType, int timeoutmsec)
{
    if(isOpen) return false; //ако порта вече е отворен

    type= scaleType;
    timeout = timeoutmsec;

    int h = sp.sp_open(portName.toLocal8Bit().data());
    if(h==-1)
    {   errMessage = QString("scale_Open: Failed to open %1").arg(portName);
        return  false;
    }

    h = sp.sp_setPort(baudRate,databits,parity,stopBits);
    if(h==-1)
    {   errMessage = QString("scale_Open: Failed to set parameters %1").arg(portName);
        return false;
    }
    //int sp_setCanonical(bool canonical, bool ignoreCR, bool mapCRtoNL, bool mapNLtoCR);
    if(type==SCALE_TYPE_BIMCO) sp.sp_setCanonical(false,false,false,false); //бимко дава 3 байта. Първите 2 са старша и младша част на int със знак. третия байт дава къде да се сложи десетичната точка
    else sp.sp_setCanonical(true,false,false,false); //всички други везни дават теглото като низ. затова са каноникал

    sp.sp_startRxTimer();

    isOpen=true;
    return isOpen;
}

//--------------------------------------------------------------------------------------------------

double Scale::getWeight(bool &OK)
{	//функцията изпраща запитване

        QByteArray response;

        if(!sp.sp_isOpen())
        {
            errMessage="getWeight: Port not opened";
            OK=false;
            return 0;
        }

	char ELICOM_ETS_RQ_WEIGHT[]={4,13,20,107,21,101,189,3};

        qApp->processEvents();
	dataFlag=false;
	weight = 0;

	errMessage="";
	//изпраща запитване към везната
	switch(type)
	{
	case SCALE_TYPE_FI6:
		break;
	case SCALE_TYPE_PUE:
		sp.sp_write(QString("SI\r\n"));
		break;
	case SCALE_TYPE_BIMCO:
		sp.sp_write(0x36);
		break;
	case SCALE_TYPE_ELICOM:
		sp.sp_write(0xf1);
		break;
	case SCALE_TYPE_BIZERBA_ST:
		sp.sp_write(QString("q$\r\n"));
		break;
	case SCALE_TYPE_VEDIA:
		sp.sp_write(0xaa);
		break;
	case SCALE_TYPE_ELICOM_ETS:
		sp.sp_write(QString("TRANZIT\r\n"));
		sp.sp_write(QString("TRANZIT\r\n"));
		sp.sp_write(ELICOM_ETS_RQ_WEIGHT,8);
                break;
        case SCALE_TYPE_WE2108:
                sp.sp_write(QString("MSV?\r\n"));
                break;
	case SCALE_TYPE_UNKNOWN:
                errMessage = "getWeight: Unknown scale type";
                OK=false;
                return 0;
		break;
	}
        //чакаме резултата
        OK = scale_getResponse(response);
        if(!OK) return 0;

        OK = scale_ParseWeight(response,weight,isStable,unit);
        if(!OK) return 0;

	return weight;
}

Scale::ScaleType Scale::getTypeByString( char * typeName)
{//функцията приема низ с името на везната и връща ScaleType
	if(strcmp(typeName,"FI.6")==0) return SCALE_TYPE_FI6;
	if(strcmp(typeName,"PUE")==0) return SCALE_TYPE_PUE;
	if(strcmp(typeName,"Bimco")==0) return SCALE_TYPE_BIMCO;
	if(strcmp(typeName,"Elicom")==0) return SCALE_TYPE_ELICOM;
	if(strcmp(typeName,"Vedia")==0) return SCALE_TYPE_VEDIA;
        if(strcmp(typeName,"WE2108")==0) return SCALE_TYPE_WE2108;
	return SCALE_TYPE_UNKNOWN;	
}
//--------------------------------------------------------------------------------------------------
QString Scale::getUnit() { return unit; }
QString Scale::getErrMessage() { return errMessage; }
bool Scale::isDataOK() { return dataOK; }

/*-------------------------------------------------------------------------*/
/**
  @brief    Приема отговор от везната на предварително пратено запитване
  @param    QByteArray response е отговора върнат от везната се записва тук.
  @param    int timeout Максимално веме за което се чака отговор
  @return   bool При успех дава true. Ако върне false, то е настъпил таймаут

    Функцията чака отговор на предварително изпратена заявка. В зависимост от типа на везната
    има различен критерии за край на отговора. Това може да е символ за край на ред например.
    При липса на отговор настъпва таймаут и се излиза с false

    Таймера  за приемане на SerialPort е спрян. Четенето на приемния буфер става в тази функция.
    Функцията чете от серииния порт байтове до <CR><LF> ако везната работи със запитване.
    Ако везната хвърля постоянно данни то чакаме да мине <LF> (<CR>) и тогава започва приемането на
    данните до достигане на <CR><LF>

    Везни:
    SCALE_TYPE_WE2108 - ОК
 */
/*--------------------------------------------------------------------------*/
bool Scale::scale_getResponse(QByteArray &response)
{
    /*

       Ако времето надхвърли timeout то функцията връща false

       След излизане остават резултати - теглото във weight, errMessage,
        scaleMessage - отговора на везната така кактоп е получен,
        isStable - дали показанието на везната е стабилно
        unit - единици
*/

    if(!isOpen) return false; //порта не е отворен.

    char c[1];
    response.resize(0);
    weight =  -1;
    time.restart();

    do
    {
        qApp->processEvents();
        if(sp.sp_read(c,1)==1)
        {
            switch(type)
            {
            case SCALE_TYPE_FI6:
                //тазои везна хвърля данни постоянно. Трябва да се направи
                    break;
            case SCALE_TYPE_PUE:
                    break;
            case SCALE_TYPE_BIMCO:
                    break;
            case SCALE_TYPE_ELICOM:
                    break;
            case SCALE_TYPE_BIZERBA_ST:
                    break;
            case SCALE_TYPE_VEDIA:
                    break;
            case SCALE_TYPE_ELICOM_ETS:
                    break;
            case SCALE_TYPE_WE2108:
                    if(c[0]==0x0A) break;
                    if(c[0]==0x0D) return true;
                    else response.append(c[0]);
                    break;
            case SCALE_TYPE_UNKNOWN:
                    return false;
                    break;
            }            
        }
    }while(time.elapsed()<timeout);
    errMessage = "scale_getResponse: Connection timeout";
    return false; //има timeout!
}

/*-------------------------------------------------------------------------*/
/**
  @brief    Извлича теглото от отговора от везната
  @param    QByteArray response е отговора върнат от везната
  @param    weight Параметъра се предава с псевдоним. В него ще се върне резултата за тегло
  @param    bool stable true - показанието на везната е стабилно
  @param    QString units - единици тегло
  @return   bool При успех дава true иначе false

    Функцията получава масив с байтове response - данните върнати от везната които са хванати с
    scale_getResponse като резултат от запитване или от изчакване за везни които предават периодично.
    Опитва се да извлече от тях тегло и информация за мерни единици, стабилност на показание и др.
    При неуспех функцията не променя параметрите предадени с псевдоним и връща false

    Везни:
    SCALE_TYPE_WE2108 - ОК
 */
/*--------------------------------------------------------------------------*/
bool Scale::scale_ParseWeight(QByteArray response, double &weight, bool &stable ,QString &units)
{
    QString str;
    double tmp;
    bool ok;
    errMessage="";

    switch(type)
    {
    case SCALE_TYPE_FI6:
        //тазои везна хвърля данни постоянно. Трябва да се направи
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_PUE:
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_BIMCO:
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_ELICOM:
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_BIZERBA_ST:
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_VEDIA:
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_ELICOM_ETS:
        errMessage = "scale_ParseWeight: Scale not implemented";
        return false; //този модел още не е имплементиран
        break;
    case SCALE_TYPE_WE2108:
        //везната трябва да е в режим COF10
        //когато накрая има kg показанието на везната е стабилно
        //първия символ е буква G или N (Gross/Netto)
        if(response.count()>0)   str = QString(response);        
        if(response.count()<12) { errMessage = "scale_ParseWeight: Incorrect response length"; return false; }
        if(str.right(2)!="  ")
        {
            units = str.right(2); //ако показанието на везната е стабилно, то след теглото се изписват и мерните единици
            stable = true;
        }
        else stable = false;
        str = str.mid(1,8);
        str = str.trimmed();
        tmp = str.toDouble(&ok);
        if(ok)
        {
            weight = tmp;            
            return true;
        }
        else
        {
            errMessage = QString("scale_ParseWeight: Error parsing weight. resplen=%1 str=%2 ").arg(response.count()).arg(str);
            return false;
        }
        break;
    case SCALE_TYPE_UNKNOWN:
        errMessage = "scale_ParseWeight: Scale type unknown";
        return false;
        break;
    }
    errMessage = "scale_ParseWeight: Unexpected function exit";
    return false;
}

//--------------------------------------------------------------------------------------------------
bool Scale::scale_isStable() { return isStable; }
//--------------------------------------------------------------------------------------------------
bool Scale::scale_Write(QString str)
{
    int r;
    if(!sp.sp_isOpen())
    {
        errMessage="scale_Write: Port not opened";
        return false;
    }
    r = sp.sp_write(str);
    if(r== -1)
    {
        errMessage="scale_Write: failed to write";
        return false;
    }
    else return true;
}
//--------------------------------------------------------------------------------------------------
bool Scale::scale_Write(QByteArray arr)
{
    int r;
    if(!sp.sp_isOpen())
    {
        errMessage="scale_Write: Port not opened";
        return false;
    }
    r = sp.sp_write(arr.data(), arr.count());
    if(r== -1)
    {
        errMessage="scale_Write: failed to write";
        return false;
    }
    else return true;
}
