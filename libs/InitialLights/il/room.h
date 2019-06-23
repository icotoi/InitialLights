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
    Q_PROPERTY(bool isOn READ isOn WRITE setIsOn NOTIFY isOnChanged)

public:
    explicit Room(ControllerList* controllerList, QObject *parent = nullptr);
    ~Room() override;

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    bool isOn() const { return m_isOn; }

    void storeIsOnAsPreviousIsOn() { m_previousIsOn = m_isOn; }
    bool previousIsOn() const { return m_previousIsOn; }

public slots:
    void setIsOn(bool isOn);

signals:
    void isOnChanged(bool isOn);

private:
    ControllerList* m_controllerList;
    bool m_isOn { false };
    bool m_previousIsOn { false };
};

} // namespace il
