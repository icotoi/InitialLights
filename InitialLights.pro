TEMPLATE = subdirs
CONFIG += ordered
CONFIG+=sdk_no_version_check
SUBDIRS = \
    3rdparty \
    libs \
    app

macos|linux:!android|win32 {
    SUBDIRS += \
        tests
}
