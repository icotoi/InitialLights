#pragma once

#include "initiallights_global.h"
#include "iindexed.h"

#include "QQmlAutoPropertyHelpers.h"
#include "QQmlObjectListModel.h"

namespace il {

class Controller;
class IIndexer;

class INITIALLIGHTSSHARED_EXPORT ControllerCollection : public QObject, public IIndexed
{
    Q_OBJECT

    QML_OBJMODEL_PROPERTY(il::Controller, items)

public:
    explicit ControllerCollection(std::function<IIndexer* (IIndexed *, QObject*)> indexerAllocator, QObject *parent = nullptr);
    virtual ~ControllerCollection();

    int count() const override;
    int maxIndex() const override;
    std::vector<int> indexes() const override;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
    void clearLocalData();

    Controller* appendNewController();

private:
    IIndexer* m_indexer;
};

} // namespace il
