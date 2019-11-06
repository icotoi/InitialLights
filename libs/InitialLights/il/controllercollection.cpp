#include "controllercollection.h"

#include <QTimer>

namespace il {

ControllerCollection::ControllerCollection(QObject *parent)
    : QObject(parent)
{    
}

ControllerCollection::~ControllerCollection()
{
}

void ControllerCollection::read(const QJsonObject &/*json*/)
{
    // TODO
}

void ControllerCollection::write(QJsonObject &/*json*/) const
{
    // TODO
}

void ControllerCollection::clearLocalData()
{
    // TODO
}

void ControllerCollection::scan()
{
    // TODO
    QTimer::singleShot(3000, this, &ControllerCollection::scanFinished);
}

} // namespace il
