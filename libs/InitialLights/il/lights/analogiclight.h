#pragma once

#include "lightbase.h"

namespace il {

namespace lights {

class INITIALLIGHTSSHARED_EXPORT  AnalogicLight : public LightBase
{
public:
    enum Channel { Channel1, Channel2 };

private:
    Q_OBJECT

    Q_ENUM(Channel)
    QML_WRITABLE_AUTO_PROPERTY(Channel, channel)

    Q_PROPERTY(int value READ value WRITE set_value NOTIFY valueChanged)

public:

    explicit AnalogicLight(QObject *parent = nullptr);
    ~AnalogicLight() override;

    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;

    int value() const { return m_value; }

signals:
    void valueChanged(int value);

public slots:
    void set_value(int value);

private:
    void setValue(Channel channel, int value) const;

    int m_value;
};

} // namespace lights
} // namespace il
