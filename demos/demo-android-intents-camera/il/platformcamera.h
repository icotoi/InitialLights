#pragma once
#include <QObject>

#ifdef Q_OS_ANDROID
    #include <QAndroidActivityResultReceiver>
#endif

namespace il {

#ifdef Q_OS_ANDROID
class PlatformCamera : public QObject, QAndroidActivityResultReceiver
#else
class PlatformCamera : public QObject
#endif
{
    Q_OBJECT

    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)

public:
    explicit PlatformCamera(QObject *parent = nullptr);

    QString imagePath() const { return m_imagePath; }

signals:
    void imagePathChanged(QString imagePath);

public slots:
    void captureImage();
    void setImagePath(QString imagePath);

private:
#ifdef Q_OS_ANDROID
    QString m_temporaryImagePath; // location of the save image
    void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject& data) override;
#endif
    QString m_imagePath;
};

}
