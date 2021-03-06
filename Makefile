#############################################################################
# Makefile for building: beton
# Generated by qmake (2.01a) (Qt 4.6.2) on: Mon Sep 23 12:40:59 2013
# Project:  beton.pro
# Template: app
# Command: /usr/local/qtsdk-2010.02/qt/bin/qmake -spec /usr/local/qtsdk-2010.02/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile beton.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_SQL_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/local/qtsdk-2010.02/qt/mkspecs/linux-g++ -I. -I/usr/local/qtsdk-2010.02/qt/include/QtCore -I/usr/local/qtsdk-2010.02/qt/include/QtNetwork -I/usr/local/qtsdk-2010.02/qt/include/QtGui -I/usr/local/qtsdk-2010.02/qt/include/QtSql -I/usr/local/qtsdk-2010.02/qt/include -I. -I.
LINK          = g++
LFLAGS        = -Wl,-rpath,/usr/local/qtsdk-2010.02/qt/lib
LIBS          = $(SUBLIBS)  -L/usr/local/qtsdk-2010.02/qt/lib -lQtSql -L/usr/local/qtsdk-2010.02/qt/lib -lQtGui -L/usr/X11R6/lib -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/local/qtsdk-2010.02/qt/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
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
		dialogreport.cpp moc_mainwindow.cpp \
		moc_dialogmenu.cpp \
		moc_serialport.cpp \
		moc_scale.cpp \
		moc_gpio.cpp \
		moc_dialogdatetime.cpp \
		moc_dialogselectconcrete.cpp \
		moc_dialogrecepti.cpp \
		moc_dialogselectfile.cpp \
		moc_modbus.cpp \
		moc_dialogdigitalkeyboard.cpp \
		moc_dialogchangeingradients.cpp \
		moc_dialogprogress.cpp \
		moc_dialogreport.cpp \
		qrc_resources.cpp
OBJECTS       = main.o \
		mainwindow.o \
		dialogmenu.o \
		serialport.o \
		scale.o \
		gpio.o \
		dialogdatetime.o \
		dialogselectconcrete.o \
		dictionary.o \
		iniparser.o \
		dialogrecepti.o \
		dialogselectfile.o \
		modbus.o \
		dialogdigitalkeyboard.o \
		dialogchangeingradients.o \
		dialogprogress.o \
		dialogreport.o \
		moc_mainwindow.o \
		moc_dialogmenu.o \
		moc_serialport.o \
		moc_scale.o \
		moc_gpio.o \
		moc_dialogdatetime.o \
		moc_dialogselectconcrete.o \
		moc_dialogrecepti.o \
		moc_dialogselectfile.o \
		moc_modbus.o \
		moc_dialogdigitalkeyboard.o \
		moc_dialogchangeingradients.o \
		moc_dialogprogress.o \
		moc_dialogreport.o \
		qrc_resources.o
DIST          = /usr/local/qtsdk-2010.02/qt/mkspecs/common/g++.conf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/common/unix.conf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/common/linux.conf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/qconfig.pri \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt_functions.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt_config.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/exclusive_builds.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/default_pre.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/debug.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/default_post.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/warn_on.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/unix/thread.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/moc.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/resources.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/uic.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/yacc.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/lex.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/include_source_dir.prf \
		beton.pro
QMAKE_TARGET  = beton
DESTDIR       = 
TARGET        = beton

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_dialogmenu.h ui_dialogdatetime.h ui_dialogselectconcrete.h ui_dialogrecepti.h ui_dialogselectfile.h ui_dialogdigitalkeyboard.h ui_dialogchangeingradients.h ui_dialogprogress.h ui_dialogreport.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: beton.pro  /usr/local/qtsdk-2010.02/qt/mkspecs/linux-g++/qmake.conf /usr/local/qtsdk-2010.02/qt/mkspecs/common/g++.conf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/common/unix.conf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/common/linux.conf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/qconfig.pri \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt_functions.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt_config.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/exclusive_builds.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/default_pre.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/debug.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/default_post.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/warn_on.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/unix/thread.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/moc.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/resources.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/uic.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/yacc.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/lex.prf \
		/usr/local/qtsdk-2010.02/qt/mkspecs/features/include_source_dir.prf \
		/usr/local/qtsdk-2010.02/qt/lib/libQtSql.prl \
		/usr/local/qtsdk-2010.02/qt/lib/libQtCore.prl \
		/usr/local/qtsdk-2010.02/qt/lib/libQtGui.prl \
		/usr/local/qtsdk-2010.02/qt/lib/libQtNetwork.prl
	$(QMAKE) -spec /usr/local/qtsdk-2010.02/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile beton.pro
/usr/local/qtsdk-2010.02/qt/mkspecs/common/g++.conf:
/usr/local/qtsdk-2010.02/qt/mkspecs/common/unix.conf:
/usr/local/qtsdk-2010.02/qt/mkspecs/common/linux.conf:
/usr/local/qtsdk-2010.02/qt/mkspecs/qconfig.pri:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt_functions.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt_config.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/exclusive_builds.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/default_pre.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/debug.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/default_post.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/warn_on.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/qt.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/unix/thread.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/moc.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/resources.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/uic.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/yacc.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/lex.prf:
/usr/local/qtsdk-2010.02/qt/mkspecs/features/include_source_dir.prf:
/usr/local/qtsdk-2010.02/qt/lib/libQtSql.prl:
/usr/local/qtsdk-2010.02/qt/lib/libQtCore.prl:
/usr/local/qtsdk-2010.02/qt/lib/libQtGui.prl:
/usr/local/qtsdk-2010.02/qt/lib/libQtNetwork.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/qtsdk-2010.02/qt/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile beton.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/beton1.0.0 || $(MKDIR) .tmp/beton1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/beton1.0.0/ && $(COPY_FILE) --parents mainwindow.h dialogmenu.h serialport.h scale.h gpio.h dialogdatetime.h dialogselectconcrete.h formula.h iniparser.h iniparser.h dictionary.h dialogrecepti.h dialogselectfile.h modbus.h dialogdigitalkeyboard.h beton.h dialogchangeingradients.h dialogprogress.h dialogreport.h .tmp/beton1.0.0/ && $(COPY_FILE) --parents resources.qrc .tmp/beton1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp dialogmenu.cpp serialport.cpp scale.cpp gpio.cpp dialogdatetime.cpp dialogselectconcrete.cpp dictionary.cpp iniparser.cpp dialogrecepti.cpp dialogselectfile.cpp modbus.cpp dialogdigitalkeyboard.cpp dialogchangeingradients.cpp dialogprogress.cpp dialogreport.cpp .tmp/beton1.0.0/ && $(COPY_FILE) --parents mainwindow.ui dialogmenu.ui dialogdatetime.ui dialogselectconcrete.ui dialogrecepti.ui dialogselectfile.ui dialogdigitalkeyboard.ui dialogchangeingradients.ui dialogprogress.ui dialogreport.ui .tmp/beton1.0.0/ && (cd `dirname .tmp/beton1.0.0` && $(TAR) beton1.0.0.tar beton1.0.0 && $(COMPRESS) beton1.0.0.tar) && $(MOVE) `dirname .tmp/beton1.0.0`/beton1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/beton1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_dialogmenu.cpp moc_serialport.cpp moc_scale.cpp moc_gpio.cpp moc_dialogdatetime.cpp moc_dialogselectconcrete.cpp moc_dialogrecepti.cpp moc_dialogselectfile.cpp moc_modbus.cpp moc_dialogdigitalkeyboard.cpp moc_dialogchangeingradients.cpp moc_dialogprogress.cpp moc_dialogreport.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_dialogmenu.cpp moc_serialport.cpp moc_scale.cpp moc_gpio.cpp moc_dialogdatetime.cpp moc_dialogselectconcrete.cpp moc_dialogrecepti.cpp moc_dialogselectfile.cpp moc_modbus.cpp moc_dialogdigitalkeyboard.cpp moc_dialogchangeingradients.cpp moc_dialogprogress.cpp moc_dialogreport.cpp
moc_mainwindow.cpp: beton.h \
		dialogmenu.h \
		dialogdatetime.h \
		gpio.h \
		formula.h \
		dialogrecepti.h \
		dictionary.h \
		iniparser.h \
		dialogselectfile.h \
		dialogreport.h \
		dialogselectconcrete.h \
		dialogdigitalkeyboard.h \
		dialogchangeingradients.h \
		serialport.h \
		scale.h \
		modbus.h \
		mainwindow.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_dialogmenu.cpp: beton.h \
		dialogdatetime.h \
		gpio.h \
		formula.h \
		dialogrecepti.h \
		dictionary.h \
		iniparser.h \
		dialogselectfile.h \
		dialogreport.h \
		dialogmenu.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogmenu.h -o moc_dialogmenu.cpp

moc_serialport.cpp: serialport.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) serialport.h -o moc_serialport.cpp

moc_scale.cpp: serialport.h \
		scale.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) scale.h -o moc_scale.cpp

moc_gpio.cpp: gpio.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) gpio.h -o moc_gpio.cpp

moc_dialogdatetime.cpp: gpio.h \
		formula.h \
		dialogdatetime.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogdatetime.h -o moc_dialogdatetime.cpp

moc_dialogselectconcrete.cpp: gpio.h \
		formula.h \
		dictionary.h \
		iniparser.h \
		dialogdigitalkeyboard.h \
		beton.h \
		dialogselectconcrete.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogselectconcrete.h -o moc_dialogselectconcrete.cpp

moc_dialogrecepti.cpp: dictionary.h \
		iniparser.h \
		gpio.h \
		dialogrecepti.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogrecepti.h -o moc_dialogrecepti.cpp

moc_dialogselectfile.cpp: gpio.h \
		dialogselectfile.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogselectfile.h -o moc_dialogselectfile.cpp

moc_modbus.cpp: serialport.h \
		modbus.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) modbus.h -o moc_modbus.cpp

moc_dialogdigitalkeyboard.cpp: gpio.h \
		dialogdigitalkeyboard.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogdigitalkeyboard.h -o moc_dialogdigitalkeyboard.cpp

moc_dialogchangeingradients.cpp: gpio.h \
		beton.h \
		dialogchangeingradients.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogchangeingradients.h -o moc_dialogchangeingradients.cpp

moc_dialogprogress.cpp: dialogprogress.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogprogress.h -o moc_dialogprogress.cpp

moc_dialogreport.cpp: gpio.h \
		beton.h \
		dialogreport.h
	/usr/local/qtsdk-2010.02/qt/bin/moc $(DEFINES) $(INCPATH) dialogreport.h -o moc_dialogreport.cpp

compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: resources.qrc \
		res/shnek-h-4.png \
		res/wheel-0.png \
		res/logo.png \
		res/waterV4.png \
		res/waterV0.png \
		res/shnek-h-3.png \
		res/wheel-270.png \
		res/green-dot.png \
		res/shnek-h-7.png \
		res/waterV3.png \
		res/shnek-h-2.png \
		res/wheel-315.png \
		res/wheel-90.png \
		res/shnek-h-6.png \
		res/wheel-180.png \
		res/waterV2.png \
		res/nowater.png \
		res/shnek-h-5.png \
		res/waterV6.png \
		res/shnek-h-1.png \
		res/wheel-45.png \
		res/wheel-135.png \
		res/background.bmp \
		res/wheel-225.png \
		res/waterV5.png \
		res/waterV1.png
	/usr/local/qtsdk-2010.02/qt/bin/rcc -name resources resources.qrc -o qrc_resources.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_dialogmenu.h ui_dialogdatetime.h ui_dialogselectconcrete.h ui_dialogrecepti.h ui_dialogselectfile.h ui_dialogdigitalkeyboard.h ui_dialogchangeingradients.h ui_dialogprogress.h ui_dialogreport.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_dialogmenu.h ui_dialogdatetime.h ui_dialogselectconcrete.h ui_dialogrecepti.h ui_dialogselectfile.h ui_dialogdigitalkeyboard.h ui_dialogchangeingradients.h ui_dialogprogress.h ui_dialogreport.h
ui_mainwindow.h: mainwindow.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_dialogmenu.h: dialogmenu.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogmenu.ui -o ui_dialogmenu.h

ui_dialogdatetime.h: dialogdatetime.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogdatetime.ui -o ui_dialogdatetime.h

ui_dialogselectconcrete.h: dialogselectconcrete.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogselectconcrete.ui -o ui_dialogselectconcrete.h

ui_dialogrecepti.h: dialogrecepti.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogrecepti.ui -o ui_dialogrecepti.h

ui_dialogselectfile.h: dialogselectfile.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogselectfile.ui -o ui_dialogselectfile.h

ui_dialogdigitalkeyboard.h: dialogdigitalkeyboard.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogdigitalkeyboard.ui -o ui_dialogdigitalkeyboard.h

ui_dialogchangeingradients.h: dialogchangeingradients.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogchangeingradients.ui -o ui_dialogchangeingradients.h

ui_dialogprogress.h: dialogprogress.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogprogress.ui -o ui_dialogprogress.h

ui_dialogreport.h: dialogreport.ui
	/usr/local/qtsdk-2010.02/qt/bin/uic dialogreport.ui -o ui_dialogreport.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		beton.h \
		dialogmenu.h \
		dialogdatetime.h \
		gpio.h \
		formula.h \
		dialogrecepti.h \
		dictionary.h \
		iniparser.h \
		dialogselectfile.h \
		dialogreport.h \
		dialogselectconcrete.h \
		dialogdigitalkeyboard.h \
		dialogchangeingradients.h \
		serialport.h \
		scale.h \
		modbus.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		beton.h \
		dialogmenu.h \
		dialogdatetime.h \
		gpio.h \
		formula.h \
		dialogrecepti.h \
		dictionary.h \
		iniparser.h \
		dialogselectfile.h \
		dialogreport.h \
		dialogselectconcrete.h \
		dialogdigitalkeyboard.h \
		dialogchangeingradients.h \
		serialport.h \
		scale.h \
		modbus.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

dialogmenu.o: dialogmenu.cpp dialogmenu.h \
		beton.h \
		dialogdatetime.h \
		gpio.h \
		formula.h \
		dialogrecepti.h \
		dictionary.h \
		iniparser.h \
		dialogselectfile.h \
		dialogreport.h \
		ui_dialogmenu.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogmenu.o dialogmenu.cpp

serialport.o: serialport.cpp serialport.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o serialport.o serialport.cpp

scale.o: scale.cpp scale.h \
		serialport.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scale.o scale.cpp

gpio.o: gpio.cpp gpio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gpio.o gpio.cpp

dialogdatetime.o: dialogdatetime.cpp dialogdatetime.h \
		gpio.h \
		formula.h \
		ui_dialogdatetime.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogdatetime.o dialogdatetime.cpp

dialogselectconcrete.o: dialogselectconcrete.cpp dialogselectconcrete.h \
		gpio.h \
		formula.h \
		dictionary.h \
		iniparser.h \
		dialogdigitalkeyboard.h \
		beton.h \
		ui_dialogselectconcrete.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogselectconcrete.o dialogselectconcrete.cpp

dictionary.o: dictionary.cpp dictionary.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dictionary.o dictionary.cpp

iniparser.o: iniparser.cpp iniparser.h \
		dictionary.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o iniparser.o iniparser.cpp

dialogrecepti.o: dialogrecepti.cpp dialogrecepti.h \
		dictionary.h \
		iniparser.h \
		gpio.h \
		ui_dialogrecepti.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogrecepti.o dialogrecepti.cpp

dialogselectfile.o: dialogselectfile.cpp dialogselectfile.h \
		gpio.h \
		ui_dialogselectfile.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogselectfile.o dialogselectfile.cpp

modbus.o: modbus.cpp modbus.h \
		serialport.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o modbus.o modbus.cpp

dialogdigitalkeyboard.o: dialogdigitalkeyboard.cpp dialogdigitalkeyboard.h \
		gpio.h \
		ui_dialogdigitalkeyboard.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogdigitalkeyboard.o dialogdigitalkeyboard.cpp

dialogchangeingradients.o: dialogchangeingradients.cpp dialogchangeingradients.h \
		gpio.h \
		beton.h \
		ui_dialogchangeingradients.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogchangeingradients.o dialogchangeingradients.cpp

dialogprogress.o: dialogprogress.cpp dialogprogress.h \
		ui_dialogprogress.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogprogress.o dialogprogress.cpp

dialogreport.o: dialogreport.cpp dialogreport.h \
		gpio.h \
		beton.h \
		ui_dialogreport.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialogreport.o dialogreport.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_dialogmenu.o: moc_dialogmenu.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogmenu.o moc_dialogmenu.cpp

moc_serialport.o: moc_serialport.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_serialport.o moc_serialport.cpp

moc_scale.o: moc_scale.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scale.o moc_scale.cpp

moc_gpio.o: moc_gpio.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gpio.o moc_gpio.cpp

moc_dialogdatetime.o: moc_dialogdatetime.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogdatetime.o moc_dialogdatetime.cpp

moc_dialogselectconcrete.o: moc_dialogselectconcrete.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogselectconcrete.o moc_dialogselectconcrete.cpp

moc_dialogrecepti.o: moc_dialogrecepti.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogrecepti.o moc_dialogrecepti.cpp

moc_dialogselectfile.o: moc_dialogselectfile.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogselectfile.o moc_dialogselectfile.cpp

moc_modbus.o: moc_modbus.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_modbus.o moc_modbus.cpp

moc_dialogdigitalkeyboard.o: moc_dialogdigitalkeyboard.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogdigitalkeyboard.o moc_dialogdigitalkeyboard.cpp

moc_dialogchangeingradients.o: moc_dialogchangeingradients.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogchangeingradients.o moc_dialogchangeingradients.cpp

moc_dialogprogress.o: moc_dialogprogress.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogprogress.o moc_dialogprogress.cpp

moc_dialogreport.o: moc_dialogreport.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialogreport.o moc_dialogreport.cpp

qrc_resources.o: qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resources.o qrc_resources.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

