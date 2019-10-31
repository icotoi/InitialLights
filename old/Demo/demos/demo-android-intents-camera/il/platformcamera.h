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
    Q_PROPERTY(QStringList imagePaths READ imagePaths WRITE setImagePaths NOTIFY imagePathsChanged)

public:
    explicit PlatformCamera(QObject *parent = nullptr);

    QString imagePath() const { return m_imagePath; }
    QStringList imagePaths() const { return m_imagePaths; }

signals:
    void imagePathChanged(QString imagePath);
    void imagePathsChanged(QStringList imagePaths);

public slots:
    void captureImage();
    void setImagePath(QString imagePath);
    void setImagePaths(QStringList imagePaths);

private:
#ifdef Q_OS_ANDROID
    QString m_temporaryImagePath; // location of the save image
    void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject& data) override;
#endif
    QString m_imagePath;
    QStringList m_imagePaths;
};

}
