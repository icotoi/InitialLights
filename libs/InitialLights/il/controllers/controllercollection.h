#pragma once

#include "initiallights_global.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"
#include "controller.h"

namespace il {

namespace bluetooth {
class IBluetoothController;
}

namespace controllers {

class INITIALLIGHTSSHARED_EXPORT ControllerCollection : public QObject
{
    Q_OBJECT

    QML_OBJMODEL_PROPERTY(il::controllers::Controller, items)

public:
    explicit ControllerCollection(QObject *parent = nullptr);
    ~ControllerCollection() override;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    void clearLocalData();

    Controller* appendNewController(bluetooth::IBluetoothController* bluetoothController);

signals:
    void controllerKindChanged(Controller* controller);

private:
    void onControllerKindChanged();
};

} // controllers
} // namespace il
