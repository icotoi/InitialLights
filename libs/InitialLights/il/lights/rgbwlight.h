#pragma once

#include "lightbase.h"

namespace il {

namespace lights {

class INITIALLIGHTSSHARED_EXPORT RGBWLight : public LightBase
{
    Q_OBJECT

    Q_PROPERTY(int red READ red WRITE set_red NOTIFY redChanged)
    Q_PROPERTY(int green READ green WRITE set_green NOTIFY greenChanged)
    Q_PROPERTY(int blue READ blue WRITE set_blue NOTIFY blueChanged)
    Q_PROPERTY(int white READ white WRITE set_white NOTIFY whiteChanged)

public:
    enum Light { Red, Green, Blue, White };

    explicit RGBWLight(QObject *parent = nullptr);
    ~RGBWLight() override;

    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;

    int red() const { return m_red; }
    int green() const { return m_green; }
    int blue() const { return m_blue; }
    int white() const { return m_white; }

signals:
    void redChanged(int red);
    void greenChanged(int green);
    void blueChanged(int blue);
    void whiteChanged(int white);

public slots:
    void set_red(int red);
    void set_green(int green);
    void set_blue(int blue);
    void set_white(int white);

private:
    void setValue(Light light, int value) const;

    int m_red;
    int m_green;
    int m_blue;
    int m_white;
};

} // namespace lights
} // namespace il
