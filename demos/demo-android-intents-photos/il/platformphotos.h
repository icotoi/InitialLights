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
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

public:
    explicit PlatformPhotos(QObject *parent = nullptr);

    QImage image() const { return m_image; }

signals:

    void imageChanged(QImage image);

public slots:
    void selectImage();
    void setImage(QImage image);

private:
#ifdef Q_OS_ANDROID
    void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject& data) override;
#endif
    QImage m_image;
};

} // namespace il
