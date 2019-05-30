#include "platformcamera.h"

#include <QDebug>

#if defined(Q_OS_ANDROID)
#  include <QtAndroidExtras/QAndroidJniObject>
#  include <QtAndroidExtras/QtAndroid>
#endif

namespace il {

PlatformCamera::PlatformCamera(QObject *parent) : QObject(parent)
{

}

void PlatformCamera::launch()
{
#if defined(Q_OS_ANDROID)
#else
    qWarning() << "Not implemented on this platform";
#endif
}

}
