TEMPLATE = lib

QT += qml
QT -= gui

TARGET = InitialLights
CONFIG += c++17

# we're using static libs for easy deploy on mobile platforms
CONFIG += static

DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

DEFINES += INITIALLIGHTS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        il/backend.cpp \
        il/room.cpp

HEADERS += \
        il/backend.h \
        il/room.h \
        initiallights_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# QtQmlModels

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/QtQmlModels/release/ -lQtQmlModels
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/QtQmlModels/debug/ -lQtQmlModels
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/QtQmlModels/ -lQtQmlModels

INCLUDEPATH += $$PWD/../../3rdparty/QtQmlModels
DEPENDPATH += $$PWD/../../3rdparty/QtQmlModels

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtQmlModels/release/libQtQmlModels.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtQmlModels/debug/libQtQmlModels.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtQmlModels/release/QtQmlModels.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtQmlModels/debug/QtQmlModels.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtQmlModels/libQtQmlModels.a

# QtSuperMacros

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/QtSuperMacros/release/ -lQtSuperMacros
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/QtSuperMacros/debug/ -lQtSuperMacros
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/QtSuperMacros/ -lQtSuperMacros

INCLUDEPATH += $$PWD/../../3rdparty/QtSuperMacros
DEPENDPATH += $$PWD/../../3rdparty/QtSuperMacros

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtSuperMacros/release/libQtSuperMacros.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtSuperMacros/debug/libQtSuperMacros.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtSuperMacros/release/QtSuperMacros.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtSuperMacros/debug/QtSuperMacros.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/QtSuperMacros/libQtSuperMacros.a
