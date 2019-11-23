#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class BluetoothExplorer;
class ControllerCollection;
class RoomCollection;
class User;

class INITIALLIGHTSSHARED_EXPORT BackEnd : public QObject
{
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(int, version)

    QML_WRITABLE_AUTO_PROPERTY(bool, showOnboarding)
    QML_WRITABLE_AUTO_PROPERTY(bool, showInitialSetup)

    Q_PROPERTY(il::BluetoothExplorer* bluetoothExplorer READ bluetoothExplorer CONSTANT)
    Q_PROPERTY(il::ControllerCollection* controllers READ controllers CONSTANT)
    Q_PROPERTY(il::RoomCollection* rooms READ rooms CONSTANT)
    Q_PROPERTY(il::User* user READ user CONSTANT)

public:
    explicit BackEnd(QObject *parent = nullptr);
    ~BackEnd() override;

public slots:
    void clearLocalData();
    void loadLocalData();
    void saveLocalData();

    BluetoothExplorer* bluetoothExplorer() const { return m_bluetoothExplorer; }
    ControllerCollection* controllers() const { return m_controllers; }
    RoomCollection* rooms() const { return m_rooms; }
    User* user() const { return m_user; }

private:
    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    BluetoothExplorer* m_bluetoothExplorer;
    ControllerCollection* m_controllers;
    RoomCollection* m_rooms;
    User* m_user;
};

} // namespace il
