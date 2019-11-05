include($$top_srcdir/libs/InitialLights/InitialLights.pri)

QT += testlib qml

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

TEMPLATE = app

SOURCES +=  \
    tst_roomcollection.cpp
