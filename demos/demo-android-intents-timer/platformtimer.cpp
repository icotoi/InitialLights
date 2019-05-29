#include "platformtimer.h"

#include <QDebug>

#if defined(Q_OS_ANDROID)
#  include <QtAndroidExtras/QAndroidJniObject>
#  include <QtAndroidExtras/QtAndroid>
#endif

PlatformTimer::PlatformTimer(QObject *parent)
    : QObject(parent)
{
}

#if defined(Q_OS_ANDROID)
void PlatformTimer::createTimer(const QString &message, double duration, bool showUI) const
{
    // Retrieve the action
    QAndroidJniObject ACTION_SET_TIMER = QAndroidJniObject::getStaticObjectField<jstring>("android/provider/AlarmClock",
                                                                                          "ACTION_SET_TIMER");
    QAndroidJniObject intent("android/content/Intent",
                             "(Ljava/lang/String;)V",
                             ACTION_SET_TIMER.object<jstring>());

    // Set optional parameters
    QAndroidJniObject EXTRA_MESSAGE = QAndroidJniObject::getStaticObjectField<jstring>("android/provider/AlarmClock",
                                                                                       "EXTRA_MESSAGE");
    QAndroidJniObject messageObject = QAndroidJniObject::fromString(message);
    intent.callObjectMethod("putExtra",
                            "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
                            EXTRA_MESSAGE.object<jstring>(),
                            messageObject.object<jstring>());

    QAndroidJniObject EXTRA_LENGTH = QAndroidJniObject::getStaticObjectField<jstring>("android/provider/AlarmClock",
                                                                                      "EXTRA_LENGTH");
    intent.callObjectMethod("putExtra",
                            "(Ljava/lang/String;I)Landroid/content/Intent;",
                            EXTRA_LENGTH.object<jstring>(),
                            jint(duration * 60));

    QAndroidJniObject EXTRA_SKIP_UI = QAndroidJniObject::getStaticObjectField<jstring>("android/provider/AlarmClock",
                                                                                       "EXTRA_SKIP_UI");
    intent.callObjectMethod("putExtra",
                            "(Ljava/lang/String;Z)Landroid/content/Intent;",
                            EXTRA_SKIP_UI.object<jstring>(),
                            jboolean(!showUI));

    // Resolve the activity (check if there is an application available to handle our action)
    // 1. get a reference to our current activity
    // 2. get the appropriate package manager
    // 3. resolve the activity
    QAndroidJniObject activity = QtAndroid::androidActivity(); // 1.
    QAndroidJniObject packageManager = activity.callObjectMethod("getPackageManager",
                                                                 "()Landroid/content/pm/PackageManager;"); // 2.
    QAndroidJniObject componentName = intent.callObjectMethod("resolveActivity",
                                                              "(Landroid/content/pm/PackageManager;)Landroid/content/ComponentName;",
                                                              packageManager.object()); // 3.
    if (componentName.isValid())
        QtAndroid::startActivity(intent, 0);
    else
        qWarning() << "Unable to resolve activity";
}
#else
void PlatformTimer::createTimer(const QString &, double, bool) const
{
    qWarning() << "Not implemented on this platform";
}
#endif
