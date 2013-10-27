#ifndef FORMULA_H
#define FORMULA_H

//структура за формула бетон
#include <QString>

struct FormulaConcrete
{
    QString modelName;
    int sand;
    int cement;
    int pepelina;
    int fraction;

    int water;
};

#endif // FORMULA_H
