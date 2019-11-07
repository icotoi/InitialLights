#include "controller.h"

#include "jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {
const int unconfiguredIndex { -1 };

const QString jsonIndexTag { "index" };
const QString jsonNameTag { "name" };
const QString jsonAddressTag { "address" };
}

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_cid(unconfiguredIndex)
{    
}

Controller::~Controller()
{
}

void Controller::read(const QJsonObject &json)
{
    READ_PROPERTY_IF_EXISTS(int, json, jsonIndexTag, cid)
    READ_PROPERTY_IF_EXISTS(QString, json, jsonNameTag, name)
    READ_PROPERTY_IF_EXISTS(QString, json, jsonAddressTag, address)
}

void Controller::write(QJsonObject &json) const
{
    json[jsonIndexTag] = m_cid;
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
}

} // namespace il
