#include "platformcamera.h"

#include <QDebug>
#include <QDir>
#include <QFile>

#if defined(Q_OS_ANDROID)
#  include <QtAndroidExtras/QAndroidJniObject>
#  include <QtAndroidExtras/QtAndroid>
#endif

namespace il {

namespace {
enum ReceiverRequestCodes {
    CaptureImageReceiverRequestCode = 1
};
}

PlatformCamera::PlatformCamera(QObject *parent) : QObject(parent)
{
#if defined (Q_OS_ANDROID)
    QAndroidJniObject context = QtAndroid::androidContext();

    QAndroidJniObject DIRECTORY_PICTURES = QAndroidJniObject::getStaticObjectField<jstring>("android/os/Environment",
                                                                                            "DIRECTORY_PICTURES");
    if (!DIRECTORY_PICTURES.isValid()) {
        qWarning() << "invalid Environment.DIRECTORY_PICTURES";
    } else {
        QAndroidJniObject storageDir = context.callObjectMethod("getExternalFilesDir",
                                                                "(Ljava/lang/String;)Ljava/io/File;",
                                                                DIRECTORY_PICTURES.object<jstring>());
        if (!storageDir.isValid()) {
            qWarning() << "invalid storageDir";
        } else {
            QAndroidJniObject storageDirPath = storageDir.callObjectMethod("getAbsolutePath",
                                                                           "()Ljava/lang/String;");
            if (!storageDirPath.isValid()) {
                qWarning() << "invalid storageDirPath";
            } else {
                QDir dir(storageDirPath.toString());

                if (dir.exists() && !dir.isEmpty()) {
                    QFileInfoList infos = dir.entryInfoList(QStringList() << "*.jpg",
                                                             QDir::NoDotAndDotDot | QDir::Files,
                                                             QDir::Name);
                    QStringList images;
                    foreach(auto info, infos) {
                        images << info.absoluteFilePath();
                    }
                    setImagePaths(images);

                    qDebug() << "===";
                    qDebug() << m_imagePaths;
                    qDebug() << "===";
                }
            }
        }
    }
#endif
}

void PlatformCamera::captureImage()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject ACTION_IMAGE_CAPTURE = QAndroidJniObject::getStaticObjectField<jstring>("android/provider/MediaStore",
                                                                                              "ACTION_IMAGE_CAPTURE");
    if (!ACTION_IMAGE_CAPTURE.isValid()) {
        qWarning() << "invalid MediaStore.ACTION_IMAGE_CAPTURE";
        return;
    }

    QAndroidJniObject intent("android/content/Intent",
                             "(Ljava/lang/String;)V",
                             ACTION_IMAGE_CAPTURE.object<jstring>());
    if (!intent.isValid()) {
        qWarning() << "invalid intent";
        return;
    }

    QAndroidJniObject EXTRA_OUTPUT = QAndroidJniObject::getStaticObjectField<jstring>("android/provider/MediaStore",
                                                                                      "EXTRA_OUTPUT");
    if (!EXTRA_OUTPUT.isValid()) {
        qWarning() << "invalid MediaStore.EXTRA_OUTPUT";
        return;
    }

    QAndroidJniObject DIRECTORY_PICTURES = QAndroidJniObject::getStaticObjectField<jstring>("android/os/Environment",
                                                                                            "DIRECTORY_PICTURES");
    if (!DIRECTORY_PICTURES.isValid()) {
        qWarning() << "invalid Environment.DIRECTORY_PICTURES";
        return;
    }

    QAndroidJniObject context = QtAndroid::androidContext();

    QAndroidJniObject storageDir = context.callObjectMethod("getExternalFilesDir",
                                                            "(Ljava/lang/String;)Ljava/io/File;",
                                                            DIRECTORY_PICTURES.object<jstring>());
    if (!storageDir.isValid()) {
        qWarning() << "invalid storageDir";
        return;
    }

    QAndroidJniObject filename = QAndroidJniObject::fromString("camera");
    QAndroidJniObject extname = QAndroidJniObject::fromString(".jpg");
    QAndroidJniObject photo = QAndroidJniObject::callStaticObjectMethod("java/io/File",
                                                                        "createTempFile",
                                                                        "(Ljava/lang/String;Ljava/lang/String;Ljava/io/File;)Ljava/io/File;",
                                                                        filename.object<jstring>(),
                                                                        extname.object<jstring>(),
                                                                        storageDir.object<jobject>());
    if (!photo.isValid()) {
        qWarning() << "invalid photo";
        return;
    }

    QAndroidJniObject temporaryImagePath = photo.callObjectMethod("getAbsolutePath",
                                                  "()Ljava/lang/String;");
    if (!temporaryImagePath.isValid()) {
        m_temporaryImagePath.clear();
        qWarning() << "invalid temporaryImagePath";
    } else {
        m_temporaryImagePath = temporaryImagePath.toString();
        qDebug() << "m_temporaryImagePath:" << m_temporaryImagePath;
    }

    QAndroidJniObject authorithy = QAndroidJniObject::fromString("com.initiallights.demo_android_intents_camera.fileprovider");
    QAndroidJniObject capturedImageUri = QAndroidJniObject::callStaticObjectMethod("android/support/v4/content/FileProvider",
                                                                                   "getUriForFile",
                                                                                   "(Landroid/content/Context;Ljava/lang/String;Ljava/io/File;)Landroid/net/Uri;",
                                                                                   context.object(),
                                                                                   authorithy.object<jstring>(),
                                                                                   photo.object<jobject>());
    if (!capturedImageUri.isValid()) {
        qWarning() << "invalid capturedImageUri";
    }

    intent.callObjectMethod("putExtra",
                            "(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;",
                            EXTRA_OUTPUT.object<jstring>(),
                            capturedImageUri.object<jobject>());

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

    if (componentName.isValid()) {
        QtAndroid::startActivity(intent, CaptureImageReceiverRequestCode, this);
    } else {
        qWarning() << "Unable to resolve activity";
    }
#else
    qWarning() << "Not implemented on this platform";
#endif
}

void PlatformCamera::setImagePath(QString imagePath)
{
    if (m_imagePath == imagePath)
        return;

    m_imagePath = imagePath;
    emit imagePathChanged(m_imagePath);
}

void PlatformCamera::setImagePaths(QStringList imagePaths)
{
    if (m_imagePaths == imagePaths)
        return;

    m_imagePaths = imagePaths;
    emit imagePathsChanged(m_imagePaths);
}

#ifdef Q_OS_ANDROID
void PlatformCamera::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &)
{
    if (receiverRequestCode != CaptureImageReceiverRequestCode) {
        qWarning() << "wrong receiver request code";
        QFile::remove(m_temporaryImagePath);
        return;
    }

    jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android.app.Activity", "RESULT_OK");
    if (resultCode != RESULT_OK) {
        qWarning() << "activity failed";
        QFile::remove(m_temporaryImagePath);
        return;
    }

    qDebug() << "image acquired";
    setImagePath(m_temporaryImagePath);

    QStringList images = m_imagePaths;
    images.push_back(m_temporaryImagePath);
    images.sort();
    setImagePaths(images);
}
#endif

}
