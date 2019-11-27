#pragma once

#include "lightbase.h"

namespace il {

namespace lights {

class INITIALLIGHTSSHARED_EXPORT RGBWLight : public LightBase
{
    Q_OBJECT

    Q_PROPERTY(int red READ red WRITE setRed NOTIFY redChanged)
    Q_PROPERTY(int green READ green WRITE setGreen NOTIFY greenChanged)
    Q_PROPERTY(int blue READ blue WRITE setBlue NOTIFY blueChanged)
    Q_PROPERTY(int white READ white WRITE setWhite NOTIFY whiteChanged)

public:
    enum Light { Red, Green, Blue, White };

    explicit RGBWLight(QObject *parent = nullptr);
    ~RGBWLight() override;

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
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void setWhite(int white);

private:
    void setValue(Light light, int value) const;

    int m_red;
    int m_green;
    int m_blue;
    int m_white;
};

} // namespace lights
} // namespace il
