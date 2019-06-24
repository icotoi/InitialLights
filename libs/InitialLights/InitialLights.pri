QT += qml bluetooth
CONFIG += c++17

DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

INCLUDEPATH += \
    $$top_srcdir/3rdparty/QtQmlModels \
    $$top_srcdir/3rdparty/QtSuperMacros \
    $$top_srcdir/libs/InitialLights

DEPENDPATH += \
    $$top_srcdir/3rdparty/QtQmlModels \
    $$top_srcdir/3rdparty/QtSuperMacros \
    $$top_srcdir/libs/InitialLights

# libs/InitialLights
win32:CONFIG(release, debug|release): LIBS += -L$$top_builddir/libs/InitialLights/release/ -lInitialLights
else:win32:CONFIG(debug, debug|release): LIBS += -L$$$$top_builddir/libs/InitialLights/debug/ -lInitialLights
else:unix: LIBS += -L$$top_builddir/libs/InitialLights/ -lInitialLights

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$top_builddir/libs/InitialLights/release/libInitialLights.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$top_builddir/libs/InitialLights/debug/libInitialLights.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$top_builddir/libs/InitialLights/release/InitialLights.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$top_builddir/libs/InitialLights/debug/InitialLights.lib
else:unix: PRE_TARGETDEPS += $$top_builddir/libs/InitialLights/libInitialLights.a

# 3rdparty/QtQmlModels
win32:CONFIG(release, debug|release): LIBS += -L$$top_builddir/3rdparty/QtQmlModels/release/ -lQtQmlModels
else:win32:CONFIG(debug, debug|release): LIBS += -L$$top_builddir/3rdparty/QtQmlModels/debug/ -lQtQmlModels
else:unix: LIBS += -L$$top_builddir/3rdparty/QtQmlModels/ -lQtQmlModels

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtQmlModels/release/libQtQmlModels.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtQmlModels/debug/libQtQmlModels.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtQmlModels/release/QtQmlModels.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtQmlModels/debug/QtQmlModels.lib
else:unix: PRE_TARGETDEPS += $$top_builddir/3rdparty/QtQmlModels/libQtQmlModels.a

# 3rdparty/QtSuperMacros

win32:CONFIG(release, debug|release): LIBS += -L$$top_builddir/3rdparty/QtSuperMacros/release/ -lQtSuperMacros
else:win32:CONFIG(debug, debug|release): LIBS += -L$$top_builddir/3rdparty/QtSuperMacros/debug/ -lQtSuperMacros
else:unix: LIBS += -L$$top_builddir/3rdparty/QtSuperMacros/ -lQtSuperMacros

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtSuperMacros/release/libQtSuperMacros.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtSuperMacros/debug/libQtSuperMacros.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtSuperMacros/release/QtSuperMacros.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$top_builddir/3rdparty/QtSuperMacros/debug/QtSuperMacros.lib
else:unix: PRE_TARGETDEPS += $$top_builddir/3rdparty/QtSuperMacros/libQtSuperMacros.a
