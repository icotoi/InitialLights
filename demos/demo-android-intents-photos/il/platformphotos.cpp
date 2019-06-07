#include "platformphotos.h"

#include <QDebug>

#if defined(Q_OS_ANDROID)
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QDir>
#endif

namespace il {

namespace {
enum ReceiverRequestCodes {
    SelectImageReceiverRequestCode = 2
};

#if defined(Q_OS_ANDROID)
QString getPicturesFolder() {
    QAndroidJniObject context = QtAndroid::androidContext();
    QAndroidJniObject DIRECTORY_PICTURES = QAndroidJniObject::getStaticObjectField<jstring>("android/os/Environment",
                                                                                            "DIRECTORY_PICTURES");
    if (!DIRECTORY_PICTURES.isValid()) {
        qWarning() << "invalid Environment.DIRECTORY_PICTURES";
        return QString();
    }

    QAndroidJniObject storageDir = context.callObjectMethod("getExternalFilesDir",
                                                            "(Ljava/lang/String;)Ljava/io/File;",
                                                            DIRECTORY_PICTURES.object<jstring>());
    if (!storageDir.isValid()) {
        qWarning() << "invalid storageDir";
        return QString();
    }

    QAndroidJniObject storageDirPath = storageDir.callObjectMethod("getAbsolutePath",
                                                                   "()Ljava/lang/String;");
    if (!storageDirPath.isValid()) {
        qWarning() << "invalid storageDirPath";
        return QString();
    }

    return storageDirPath.toString();
}

struct ImageExtractor {
    QImage image;

    bool extract(const QAndroidJniObject& uri) {
        if (!uri.isValid()) {
            qWarning() << "invalid uri";
            return false;
        }

        QAndroidJniObject context = QtAndroid::androidContext();
        QAndroidJniObject contentResolver = context.callObjectMethod("getContentResolver",
                                                                     "()Landroid/content/ContentResolver;");

        if (!contentResolver.isValid()) {
            qWarning() << "invalid resolver";
            return false;
        }

        QAndroidJniObject inputStream = contentResolver.callObjectMethod("openInputStream",
                                                                         "(Landroid/net/Uri;)Ljava/io/InputStream;",
                                                                         uri.object<jobject>());
        if (!inputStream.isValid()) {
            qWarning() << "invalid input stream";
        }

        qDebug() << "preparing to read";

        jint bufferSize = 8 * 1024;
        QByteArray qtBuffer;
        QAndroidJniEnvironment env;
        jbyteArray jniBuffer = env->NewByteArray(bufferSize);
        char* nativeBuffer = new char[bufferSize];

        jint read;
        while ((read = inputStream.callMethod<jint>("read", "([B)I", jniBuffer)) != -1 ) {
            qDebug() << "read:" << read;
            int len = env->GetArrayLength (jniBuffer);
            env->GetByteArrayRegion (jniBuffer, 0, len, reinterpret_cast<jbyte*>(nativeBuffer));
            qtBuffer.append(nativeBuffer, len);
        }

        return image.loadFromData(qtBuffer);
    }
};
#endif
}

PlatformPhotos::PlatformPhotos(QObject *parent) : QObject(parent)
{

}

void PlatformPhotos::selectImage()
{
    // for simplicity, we unset the image when we're going to select a new one
    // this should not be done in the final code
    setImagePath("");

#if defined (Q_OS_ANDROID)
    QAndroidJniObject ACTION_GET_CONTENT = QAndroidJniObject::getStaticObjectField<jstring>("android/content/Intent",
                                                                                            "ACTION_GET_CONTENT");
    if (!ACTION_GET_CONTENT.isValid()) {
        qWarning() << "invalid Intent.ACTION_GET_CONTENT";
        return;
    }

    QAndroidJniObject intent("android/content/Intent",
                             "(Ljava/lang/String;)V",
                             ACTION_GET_CONTENT.object<jstring>());
    if (!intent.isValid()) {
        qWarning() << "invalid intent";
        return;
    }

    QAndroidJniObject intentMimeType = QAndroidJniObject::fromString("image/*");

    intent.callObjectMethod("setType",
                            "(Ljava/lang/String;)Landroid/content/Intent;",
                            intentMimeType.object<jstring>());

    if (!intent.isValid()) {
        qWarning() << "failed to set mime type";
        return;
    }

    QAndroidJniObject activity = QtAndroid::androidActivity();
    QAndroidJniObject packageManager = activity.callObjectMethod("getPackageManager",
                                                                 "()Landroid/content/pm/PackageManager;");
    QAndroidJniObject componentName = intent.callObjectMethod("resolveActivity",
                                                              "(Landroid/content/pm/PackageManager;)Landroid/content/ComponentName;",
                                                              packageManager.object());

    if (componentName.isValid()) {
        QtAndroid::startActivity(intent, SelectImageReceiverRequestCode, this);
    } else {
        qWarning() << "Unable to resolve activity";
    }

#else
    qWarning() << "Not implemented on this platform";
#endif
}

void PlatformPhotos::setImagePath(QString imagePath)
{
    if (m_imagePath == imagePath)
        return;

    m_imagePath = imagePath;
    emit imagePathChanged(m_imagePath);
}

#if defined (Q_OS_ANDROID)
void PlatformPhotos::handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data)
{
    if (receiverRequestCode != SelectImageReceiverRequestCode) {
        qWarning() << "wrong receiver request code";
        return;
    }

    jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android.app.Activity", "RESULT_OK");
    if (resultCode != RESULT_OK) {
        qWarning() << "activity failed";
        return;
    }

    auto uri = data.callObjectMethod("getData",
                                     "()Landroid/net/Uri;");
    if (!uri.isValid()) {
        qWarning() << "no uri found...";
        return;
    }

    auto imageExtractor = ImageExtractor();
    if (!imageExtractor.extract(uri)) {
        qWarning() << "could not extract the image";
        return;
    }

    QString picturesFolderPath = getPicturesFolder();
    QDir dir(picturesFolderPath);
    dir.mkpath(picturesFolderPath);
    QFileInfo info(dir, "foo.jpg");
    QString path = info.absoluteFilePath();
    imageExtractor.image.save(path);

    qDebug() << "image saved to:" << path;

    setImagePath("file://" + path);
}
#endif

} // namespace il
