#-------------------------------------------------
#
# Project created by QtCreator 2016-02-30T14:59:26
# 
# AUTHOR: TEN@ECOLAB.COM
#-------------------------------------------------

QT       += core gui declarative multimedia
CONFIG   +=  mobility
MOBILITY = multimedia
TARGET = Garfunkel-ui
TEMPLATE = app

SOURCES += src/IPCCommand.cpp \
           src/abstractipcmessage.cpp \
           src/abstractcommandprocessor.cpp\
           src/GarfunkelCommandProcessor.cpp\
           src/GarfunkelCommThread.cpp\
           src/GarfunkelDiagnosticContext.cpp \
           src/GarfunkelIPC.cpp\
           src/GarfunkelSystemData.cpp\
           src/main.cpp

HEADERS += src/abstractcommandprocessor.h\
           src/abstractipcmessage.h\
           src/GarfunkelCommandProcessor.h\
           src/GarfunkelCommThread.h\
           src/GarfunkelDiagnosticContext.h\
           src/GarfunkelIPC.h\
           src/GarfunkelSystemData.h\
           src/IPCCommand.h\
           src/CommManager.h 

FORMS    +=

OTHER_FILES += 
RESOURCES += garfunkel-ui.qrc

LIBS += -lecolabplugin -L../../Condor/UI/ecolab-qt-components/com/ecolab/components -lutilities -L../../Condor/Utilities  -lpq -L../../Condor/ICU/Tools/armicu/lib -licudata -licui18n -licuuc
INCLUDEPATH += ../../Condor/Utilities /usr/local/boost_1_44_0 ../../Condor/UI/ecolab-qt-components/src ../../Condor/Common ../../Condor/ICU/Tools/icu/source/i18n ../../Condor/ICU/Tools/icu/source/i18n/unicode ../../Condor/ICU/Tools/icu/source/common/unicode ../../Condor/ICU/Tools/icu/source/common  
target.path = /usr/bin
INSTALLS += target

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
