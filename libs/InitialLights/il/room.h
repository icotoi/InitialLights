#pragma once

#include "icodable.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class ControllerList;
class Light;

class INITIALLIGHTSSHARED_EXPORT Room : public QObject, public ICodable
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(QString, name)
    QML_OBJMODEL_PROPERTY(il::Light, lights)

public:
    explicit Room(ControllerList* controllerList, QObject *parent = nullptr);
    ~Room() override;

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    void turnLights(bool on);

private:
    ControllerList* m_controllerList;
};

} // namespace il
