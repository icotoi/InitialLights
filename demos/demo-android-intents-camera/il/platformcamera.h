#pragma once
#include <QObject>

namespace il {

class PlatformCamera : public QObject
{
    Q_OBJECT

public:
    explicit PlatformCamera(QObject *parent = nullptr);

signals:

public slots:
    void launch();

private:
};

}
