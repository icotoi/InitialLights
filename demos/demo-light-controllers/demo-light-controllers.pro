TEMPLATE = app

DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

QT += quick bluetooth svg
CONFIG += c++17

HEADERS += \
    deviceinfo.h \
    lightcontroller.h \
    lightcontrollerlist.h \
    lightcontrollerpwmchannel.h \
    lightuartprotocol.h

SOURCES += \
    deviceinfo.cpp \
    lightcontroller.cpp \
    lightcontrollerlist.cpp \
    lightcontrollerpwmchannel.cpp \
    lightuartprotocol.cpp \
    main.cpp

RESOURCES += \
    qml/qml.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

    DISTFILES += \
        android/AndroidManifest.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/gradlew.bat \
        android/res/values/libs.xml
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
