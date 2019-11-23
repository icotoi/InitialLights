#include "controllercollection.h"

#include "controller.h"
#include "jsonhelper.h"
#include "iindexer.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

namespace il {

namespace {
const QString jsonControllersTag { "controllers" };
}

ControllerCollection::ControllerCollection(std::function<IIndexer* (IIndexed *, QObject *)> indexerAllocator, QObject *parent)
    : QObject(parent)
    , m_items { new QQmlObjectListModel<Controller>(this) }
    , m_indexer { indexerAllocator(this, this) }
{
}

ControllerCollection::~ControllerCollection()
{
}

int ControllerCollection::count() const
{
    return m_items->count();
}

int ControllerCollection::maxIndex() const
{
    auto mi = std::max_element(m_items->begin(), m_items->end(), [](auto lhs, auto rhs) { return lhs->cid() < rhs->cid(); });
    return mi != m_items->end() ? (*mi)->cid() : 0;
}

std::vector<int> ControllerCollection::indexes() const
{
    std::vector<int> ret;
    ret.resize(std::vector<int>::size_type(m_items->count()));
    std::transform(m_items->begin(), m_items->end(), ret.begin(), [](Controller* c) { return c->cid(); });
    return ret;
}

void ControllerCollection::read(const QJsonObject &json)
{
    readCollectionPropertyIfExists<Controller>(json, jsonControllersTag, m_items);
    m_indexer->rebuild();
}

void ControllerCollection::write(QJsonObject &json) const
{
    writeCollectionProperty(json, jsonControllersTag, m_items);
}

void ControllerCollection::clearLocalData()
{
    m_items->clear();
}

Controller *ControllerCollection::appendNewController()
{
    Controller* controller = new Controller();
    controller->set_cid(m_indexer->allocateNextFreeIndex());
    m_items->append(controller);
    return controller;
}

} // namespace il
