#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

namespace lights {
class ILight;
class LightCollection;
}

class INITIALLIGHTSSHARED_EXPORT Controller : public QObject
{
public:
    enum Kind {
        RGBW,
        Analogic,
        Unknown
    };

private:
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(QString, name)
    QML_WRITABLE_AUTO_PROPERTY(QString, address)
    QML_WRITABLE_AUTO_PROPERTY(bool, isOnline)

    QML_WRITABLE_AUTO_PROPERTY(bool, isEnabled)

    Q_ENUM(Kind)
    Q_PROPERTY(il::Controller::Kind kind READ kind WRITE set_kind NOTIFY kindChanged)

    Q_PROPERTY(il::lights::LightCollection* lights READ lights CONSTANT)

public:
    explicit Controller(QObject *parent = nullptr);
    virtual ~Controller();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    il::Controller::Kind kind() const { return m_kind; }
    lights::LightCollection* lights() const { return m_lights; }

signals:
    void kindChanged(il::Controller::Kind kind);

public slots:
    void set_kind(il::Controller::Kind kind);

private:
    il::Controller::Kind m_kind;
    lights::LightCollection* m_lights;
};

} // namespace il
