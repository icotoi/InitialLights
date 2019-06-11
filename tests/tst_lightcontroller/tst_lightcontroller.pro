QT += testlib qml
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17
DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

TEMPLATE = app

SOURCES +=  \
    ../../demos/demo-light-controllers/abstractlightcontroller.cpp \
    ../../demos/demo-light-controllers/dummylightcontroller.cpp \
    ../../demos/demo-light-controllers/lightcontrollerpwmchannel.cpp \
    ../../demos/demo-light-controllers/lightcontrollerrgbchannel.cpp \
    ../../demos/demo-light-controllers/lightcontrollervoltagechannel.cpp \
    tst_lightcontroller.cpp

HEADERS += \
    ../../demos/demo-light-controllers/abstractlightcontroller.h \
    ../../demos/demo-light-controllers/dummylightcontroller.h \
    ../../demos/demo-light-controllers/lightcontrollerpwmchannel.h \
    ../../demos/demo-light-controllers/lightcontrollerrgbchannel.h \
    ../../demos/demo-light-controllers/lightcontrollervoltagechannel.h

INCLUDEPATH += ../../demos/demo-light-controllers/
DEPENDPATH += ../../demos/demo-light-controllers/

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
