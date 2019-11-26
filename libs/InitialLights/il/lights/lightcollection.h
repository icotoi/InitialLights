#pragma once

#include "initiallights_global.h"
#include "lightkind.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class Controller;

namespace lights {

class ILight;

class LightCollection : public QObject
{
    Q_OBJECT

    QML_OBJMODEL_PROPERTY(il::lights::ILight, items)

public:
    explicit LightCollection(Controller* controller, QObject *parent = nullptr);
    ~LightCollection() override;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    void clearLocalData();

    ILight *appendNewLight(LightKind::Kind kind);

private:
    Controller* m_controller;
};

} // namespace lights
} // namespace il
