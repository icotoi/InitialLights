#pragma once

#include "icodable.h"

#include "QQmlAutoPropertyHelpers.h"
#include <QColor>

namespace il {

class Controller;
class Room;

class INITIALLIGHTSSHARED_EXPORT Light : public QObject, public ICodable
{
public:
    enum LightType {
        UndefinedLightType,
        Analogic,
        PWM,
        RGB,
    };
    Q_ENUM(LightType)

private:
    Q_OBJECT

    QML_READONLY_AUTO_PROPERTY(il::Light::LightType, lightType)

    QML_WRITABLE_AUTO_PROPERTY(QString, name)

    QML_READONLY_AUTO_PROPERTY(int, minValue)
    QML_READONLY_AUTO_PROPERTY(int, maxValue)
    QML_READONLY_AUTO_PROPERTY(int, valueIncrement)

    QML_WRITABLE_AUTO_PROPERTY(int, redValue)
    QML_WRITABLE_AUTO_PROPERTY(int, greenValue)
    QML_WRITABLE_AUTO_PROPERTY(int, blueValue)

    QML_WRITABLE_AUTO_PROPERTY(double, sideX)
    QML_WRITABLE_AUTO_PROPERTY(double, sideY)

    Q_PROPERTY(QString lightTypeName READ lightTypeName NOTIFY lightTypeChanged)
    Q_PROPERTY(il::Controller* controller READ controller CONSTANT)
    Q_PROPERTY(il::Room* room READ room WRITE setRoom NOTIFY roomChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool isOn READ isOn WRITE setIsOn NOTIFY isOnChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit Light(QObject* parent = nullptr);
    explicit Light(LightType lightType, const QString& name, QObject* parent = nullptr);
    ~Light() override;

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    QString lightTypeName() const;
    Controller* controller() const;
    Room* room() const { return m_room; }
    QColor color() const { return m_color; }
    bool isOn() const { return m_isOn; }
    int value() const { return m_value; }

    void updateColorValue();

    // values that take into account the isOn state
    int actualValue();
    int actualRedValue();
    int actualGreenValue();
    int actualBlueValue();

public slots:
    void setRoom(il::Room* room);
    void setColor(QColor color);
    void blink(int offset);
    void setIsOn(bool isOn);
    void setValue(int value);

signals:
    void lightTypeChanged(QString lightTypeName);
    void roomChanged(il::Room* room);
    void colorChanged(QColor color);
    void isOnChanged(bool isOn);
    void valueChanged(bool value);

private:
    static LightType readLightTypeFrom(const QJsonObject& json);

    void onValueChanged();

    Room* m_room { nullptr };
    QColor m_color { Qt::white };
    bool m_colorUpdateEnabled { true };
    bool m_isOn { false };
    int m_value { 0 };
};

} // namespace il
