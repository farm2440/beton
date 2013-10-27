#ifndef BETON_H
#define BETON_H

//#define TAKE_SCREENSHOTS


/* тип за състоянието на текущо изпълняваната заявка */
enum CycleState { Idle, Start ,Run, Paused, Abort , Fail, PowerDown};

/* Структура за съхранение на всички глобални променливи. Повечето се зареждат от beton.ini при стартиране
   променливата
        GlobalSettingsStruct globals;
   е дефинирана в mainwindow.cpp като глобална
 */
struct GlobalSettingsStruct
{
    //времето в секунди след което при спиране на 220В захранване започва затваряне на приложението и гасене на модула
    //зареждат се от beton.ini
    int ShutdownTimeout;
    double CoefVodomer; //От TWIDO се четат импулсите на водомера. Разделени на тоси коефициент дава литрите вода

    QString TwidoSerialPort;
    QString ScaleSandPort;
    QString ScaleFractionPort;
    QString ScaleCementPort;

    //гранични стойности на съставките на бетона . Зареждат се от beton.ini
    double MaxSand, MinSand;
    double MaxFraction, MinFraction;
    double MaxCement, MinCement;
    double MaxWater, MinWater;
    double MaxPepelina, MinPepelina;
    int MaxTime, MinTime;

    int MaxReadFails; // Максимален брой неуспешни прочитания от везна след които минава в състояние Fail

    double HumiditySand;      //Процент на влажност за корекция на количеството пясък,фракция и вода на кубик.
    double HumidityFraction;  //винаги при стартиране е 0. След това от МЕНЮ може да се промени.

    double MixerVolume; //Обем на миксера в кубични метри. Зарежда се от beton.ini
    int DumpTime; //Време за разтоварване

    double AdvScaleCement, AdvScaleSand, AdvScaleFraction, AdvScalePepelina; //предварение на везните. Тези количества се вадят от сметнатото за едно бърркало количество и резултата се зарежда във везните.

    //това са множители на нивата които се задават във везните
    int SandLIV2multi, FractionLIV2multi, CementLIV2multi, CementLIV6multi;
};

//В тази структура са всички променливи които касаят текущото състояние на изпълнение на заявката
struct GlobalStateStruct
{       //текущо състояние на изпълнението на заявката
        CycleState State;
        CycleState PrevState;
        //при четене от TWIDO се определя състоянието на механизмите и ако се движат съответния флаг се вдига за да се анимират
        // механизми
        bool fWater;
        bool fCementWheel;
        bool fBelt; //лентата работи
        bool fShnek1; //долния на картинката
        bool fShnek2; //шнековете въртят
        bool fMixer; //миксера върти
        //клапи
        bool fFractionValve;
        bool fSandValve;
        bool fCementValve;
        bool fMixerValve;
        bool fEmergencyStop;
        bool fWaterValve;
        bool fAutomaticMode; //включен автоматичен режим от ключа на таблото
        //флагове за достигнати дози
        bool fSandDose, fFracDose,fPepeDose, fCementDose;

        int failCounter; //Този брояч отчита поредните неуспешни четения от везна/twido. При достигане на критчна стойност състоянието става Fail
};

/* Структура за съставките на бетон. Водата е в литри. Насиипните материали в килограми. */
struct RecepieStruct
{
    QString Name;

    //Ори
    double Water;
    double Sand;
    double Fraction;
    double Pepelina;
    double Cement;
    int Time; //ВРЕМЕ на разбъркване в минути.

    double Quantity; //кубици бетон

    //коригираните стойности на вода,фракция и пясък се изчисляват при избора на рецепта в зависимост влажността.
    //Преди старт съставките могат да се коригират ръчно.
    //водата и вренето могат да се коригират по време на пауза
    double WaterCor; //коригирана стойност на водата
    double SandCor;
    double FractionCor;
    double PepelinaCor;
    double CementCor;
    int TimeCor;

    //стойности на материалите за едно бъркало
    int MixNumber; //брой бъркала
    double MixWater;
    double MixSand;
    double MixFraction;
    double MixPepelina;
    double MixCement;

    //брояч на вложените материали в изпълняваната рецепта
    double ExpWater;
    double ExpSand;
    double ExpFraction;
    double ExpPepelina;
    double ExpCement;

    //натрупано отклонение. Тук е разликата между зададения и вложения материал. Тази разлика се добавя към следващото бъркало за корекция.
    double DevWater;
    double DevSand;
    double DevFraction;
    double DevPepelina;
    double DevCement;

    //дата и час на начало на изпълнение на заявката
    QDate StartDate;
    QTime SatrtTime;

    //флагове
    bool CorrectionDry; //CorrectionDry true-имало е ръчна корекция на насипните материали
    bool CorrectionWater;//CorrectionWater true-имало е ръчна корекция на количеството вода
    int Status; //Status 0-Завършена 1-Прекъсната ръчно 2-Прекъсната от състояние fail 3-Прекъсната заради отпадане на захранването

};

#endif // BETON_H
