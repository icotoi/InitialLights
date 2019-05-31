#pragma once

#include <QObject>

namespace il {

class PlatformPhotos : public QObject
{
    Q_OBJECT
public:
    explicit PlatformPhotos(QObject *parent = nullptr);

signals:

public slots:
};

} // namespace il
