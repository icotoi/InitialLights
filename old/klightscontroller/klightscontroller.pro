TEMPLATE = app
TARGET = klightscontroller

QT += quick bluetooth

# Input
HEADERS += deviceinfo.h \
    light_uart_protocol.h \
    lightsuart.h
SOURCES += deviceinfo.cpp \
           light_uart_protocol.cpp \
           lightsuart.cpp \
           main.cpp

OTHER_FILES += assets/*.qml \
               assets/*.js

RESOURCES += \
             resources.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/bluetooth/heartlistener
INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

