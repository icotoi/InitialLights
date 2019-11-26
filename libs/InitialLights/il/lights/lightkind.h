#pragma once

#include "initiallights_global.h"
#include "QQmlAutoPropertyHelpers.h"

namespace il {

namespace lights {

class INITIALLIGHTSSHARED_EXPORT LightKind : public QObject
{
public:
    enum Kind {
        RGBW,
        Analogic,
        Unknown
    };

private:
    Q_OBJECT

    Q_ENUM(Kind)

public:
    LightKind(QObject* parent = nullptr);
    ~LightKind() override;

    static Kind kind(const QJsonObject& json);
    static const QString jsonKindTag;
};

} // namespace lights
} // namespace il
