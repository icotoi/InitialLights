#include "controller.h"

#include "jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {
const int unconfiguredIndex { -1 };

const QString jsonIndexTag { "index" };
const QString jsonNameTag { "name" };
const QString jsonAddressTag { "address" };
const QString jsonConfiguredTag { "configured" };
const QString jsonEnabledTag { "enabled" };
const QString jsonOnlineTag { "online" };
}

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_cid(unconfiguredIndex)
    , m_configured(false)
    , m_enabled(false)
    , m_online(false)
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
    READ_PROPERTY_IF_EXISTS(bool, json, jsonConfiguredTag, configured)
    READ_PROPERTY_IF_EXISTS(bool, json, jsonEnabledTag, enabled)
    READ_PROPERTY_IF_EXISTS(bool, json, jsonOnlineTag, online)
}

void Controller::write(QJsonObject &json) const
{
    json[jsonIndexTag] = m_cid;
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
    json[jsonConfiguredTag] = m_configured;
    json[jsonEnabledTag] = m_enabled;
    json[jsonOnlineTag] = m_online;
}

} // namespace il
