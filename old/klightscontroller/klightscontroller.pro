TEMPLATE = app
TARGET = klightscontroller

QT += quick bluetooth

HEADERS += \
    deviceinfo.h \
    light_uart_protocol.h \
    lightsuart.h

SOURCES += \
    deviceinfo.cpp \
    light_uart_protocol.cpp \
    lightsuart.cpp \
    main.cpp

RESOURCES += \
    resources.qrc

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

