TEMPLATE = app
TARGET = klightscontroller

DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

QT += quick bluetooth svg
CONFIG += c++17

HEADERS += \
    deviceinfo.h \
    lightcontroller.h \
    lightsuart.h \
    lightuartprotocol.h

SOURCES += \
    deviceinfo.cpp \
    lightcontroller.cpp \
    lightsuart.cpp \
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
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/release/ -lQtQmlModels
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/debug/ -lQtQmlModels
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/ -lQtQmlModels

INCLUDEPATH += $$PWD/../../3rdparty
DEPENDPATH += $$PWD/../../3rdparty

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/release/libQtQmlModels.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/debug/libQtQmlModels.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/release/QtQmlModels.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/debug/QtQmlModels.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/libQtQmlModels.a

# QtSuperMacros
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/release/ -lQtSuperMacros
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/debug/ -lQtSuperMacros
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/ -lQtSuperMacros

INCLUDEPATH += $$PWD/../../3rdparty
DEPENDPATH += $$PWD/../../3rdparty

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/release/libQtSuperMacros.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/debug/libQtSuperMacros.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/release/QtSuperMacros.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/debug/QtSuperMacros.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/libQtSuperMacros.a
