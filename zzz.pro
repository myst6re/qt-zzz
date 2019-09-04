QT       += core
QT       -= gui

TARGET = zzz

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    arguments.cpp \
    observer.cpp \
    zzz.cpp \
    zzzfile.cpp \
    zzztocentry.cpp

HEADERS += \
    arguments.h \
    observer.h \
    zzz.h \
    zzzfile.h \
    zzztocentry.h

OTHER_FILES += README.md \
    deploy.bat
