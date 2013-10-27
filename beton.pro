# -------------------------------------------------
# Project created by QtCreator 2012-03-06T13:05:35
# -------------------------------------------------
QT += network \
    sql
TARGET = beton
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    dialogmenu.cpp \
    serialport.cpp \
    scale.cpp \
    gpio.cpp \
    dialogdatetime.cpp \
    dialogselectconcrete.cpp \
    dictionary.cpp \
    iniparser.cpp \
    dialogrecepti.cpp \
    dialogselectfile.cpp \
    modbus.cpp \
    dialogdigitalkeyboard.cpp \
    dialogchangeingradients.cpp \
    dialogprogress.cpp \
    dialogreport.cpp
HEADERS += mainwindow.h \
    dialogmenu.h \
    serialport.h \
    scale.h \
    gpio.h \
    dialogdatetime.h \
    dialogselectconcrete.h \
    formula.h \
    iniparser.h \
    iniparser.h \
    dictionary.h \
    dialogrecepti.h \
    dialogselectfile.h \
    modbus.h \
    dialogdigitalkeyboard.h \
    beton.h \
    dialogchangeingradients.h \
    dialogprogress.h \
    dialogreport.h
FORMS += mainwindow.ui \
    dialogmenu.ui \
    dialogdatetime.ui \
    dialogselectconcrete.ui \
    dialogrecepti.ui \
    dialogselectfile.ui \
    dialogdigitalkeyboard.ui \
    dialogchangeingradients.ui \
    dialogprogress.ui \
    dialogreport.ui
RESOURCES += resources.qrc
OTHER_FILES += SQL.txt \
    beton.ini \
    recepti.bet \
    docs/history.txt
