#pragma once

#include "initiallights_global.h"
#include "iindexed.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT ControllerCollection : public QObject
{
    Q_OBJECT
public:
    explicit ControllerCollection(QObject *parent = nullptr);
    virtual ~ControllerCollection();

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    void clearLocalData();

signals:
    void scanFinished();

public slots:
    void scan();
};

} // namespace il
