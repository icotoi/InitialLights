#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class ControllerList;
class Light;

class INITIALLIGHTSSHARED_EXPORT Room : public QObject
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(QString, name)
    QML_OBJMODEL_PROPERTY(il::Light, lights)

public:
    explicit Room(ControllerList* controllerList, QObject *parent = nullptr);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    ControllerList* m_controllerList;
};

} // namespace il
