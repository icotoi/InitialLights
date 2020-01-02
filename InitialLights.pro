TEMPLATE = subdirs
CONFIG += ordered
CONFIG += sdk_no_version_check
CONFIG += c++17

SUBDIRS = \
    3rdparty \
    libs \
    app

macos|linux:!android {
    SUBDIRS += \
        tests
}
