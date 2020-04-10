QT -= gui
QT += core network websockets

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    serverhttp.cpp \
    serverweb.cpp

HEADERS += \
    serverhttp.h \
    serverweb.h

RESOURCES += \
    res.qrc
