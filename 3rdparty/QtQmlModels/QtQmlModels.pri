
# Qt QML Models

QT += core qml

CONFIG += c++17

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../QtSuperMacros
INCLUDEPATH += $$PWD/../../libs/InitialLights

HEADERS += \
    $$PWD/QQmlObjectListModel.h \
    $$PWD/QQmlVariantListModel.h \
    $$PWD/QtQmlTricksPlugin_SmartDataModels.h

SOURCES += \
    $$PWD/QQmlObjectListModel.cpp \
    $$PWD/QQmlVariantListModel.cpp

