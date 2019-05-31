#pragma once

#include <QObject>
#include <QImage>

#ifdef Q_OS_ANDROID
    #include <QAndroidActivityResultReceiver>
#endif

namespace il {

#ifdef Q_OS_ANDROID
class PlatformPhotos : public QObject, QAndroidActivityResultReceiver
#else
class PlatformPhotos : public QObject
#endif
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)

public:
    explicit PlatformPhotos(QObject *parent = nullptr);

    QString imagePath() const { return m_imagePath; }

signals:

    void imagePathChanged(QString imagePath);

public slots:
    void selectImage();
    void setImagePath(QString imagePath);

private:
#ifdef Q_OS_ANDROID
    void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject& data) override;
#endif
    QString m_imagePath;
};

} // namespace il
