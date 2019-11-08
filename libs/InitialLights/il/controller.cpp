#include "controller.h"

#include "jsonhelper.h"

#include <QJsonObject>

namespace il {

namespace {
const int unconfiguredIndex { -1 };

const QString jsonIndexTag { "index" };
const QString jsonNameTag { "name" };
const QString jsonAddressTag { "address" };
const QString jsonStateTag { "state" };

void readIfExists(const QJsonObject &json, const QString &tag, Controller::State &out)
{
    if (json.contains(tag) && json[tag].isString()) {
        int newValue = QMetaEnum::fromType<Controller::State>().keyToValue(json[tag].toString().toStdString().c_str());
        if (newValue >= 0) {
            out = Controller::State(newValue);
        }
    }
}

}

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_cid(unconfiguredIndex)
    , m_state(NotConfigured)
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
    READ_PROPERTY_IF_EXISTS(Controller::State, json, jsonStateTag, state)
}

void Controller::write(QJsonObject &json) const
{
    json[jsonIndexTag] = m_cid;
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
    json[jsonStateTag] = QMetaEnum::fromType<State>().valueToKey(m_state);
}

} // namespace il
