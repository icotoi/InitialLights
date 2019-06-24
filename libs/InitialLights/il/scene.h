#pragma once

#include "icodable.h"

#include "QQmlAutoPropertyHelpers.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT Scene : public QObject, public ICodable
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(QString, name)

public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene() override;

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;
};

} // namespace il
