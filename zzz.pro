QT       += core
QT       -= gui

TARGET = zzz

configUNZZZ {
    TARGET = unzzz
    DEFINES += UNZZZ
}

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    arguments.cpp \
    observer.cpp \
    zzz.cpp \
    zzzfile.cpp \
    zzztoc.cpp

HEADERS += \
    arguments.h \
    observer.h \
    zzz.h \
    zzzfile.h \
    zzztoc.h

OTHER_FILES += README.md \
    deploy.bat
