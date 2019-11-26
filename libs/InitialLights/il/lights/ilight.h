#pragma once

#include "lightkind.h"
#include "QQmlAutoPropertyHelpers.h"

namespace il {

class Controller;

namespace lights {

class INITIALLIGHTSSHARED_EXPORT ILight : public QObject
{
private:
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(il::lights::LightKind::Kind, kind)
    QML_WRITABLE_AUTO_PROPERTY(QString, name)
    QML_READONLY_AUTO_PROPERTY(il::Controller*, controller)

public:
    ~ILight() override;

    virtual void read(const QJsonObject& json) = 0;
    virtual void write(QJsonObject& json) const = 0;

protected:
    explicit ILight(QObject* parent = nullptr);
};

} // namespace lights
} // namespace il
