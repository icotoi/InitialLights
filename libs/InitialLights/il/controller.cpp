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
}

Controller::Controller(QObject *parent)
    : QObject(parent)
    , m_cid(unconfiguredIndex)
    , m_state(Unconfigured)
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
    readStateIfExists(json);
}

void Controller::write(QJsonObject &json) const
{
    json[jsonIndexTag] = m_cid;
    json[jsonNameTag] = m_name;
    json[jsonAddressTag] = m_address;
    json[jsonStateTag] = QMetaEnum::fromType<State>().valueToKey(m_state);
}

void Controller::readStateIfExists(const QJsonObject &json)
{
    State value = m_state;
    const QString& tag = jsonStateTag;

    if (json.contains(tag) && json[tag].isString()) {
        int newValue = QMetaEnum::fromType<Controller::State>().keyToValue(json[tag].toString().toStdString().c_str());
        if (newValue >= 0) {
            value = Controller::State(newValue);
            set_state(value);
            qDebug() << " >>> state (Controller::State):" << m_state;
        }
    }
}

} // namespace il
