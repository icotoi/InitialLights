#include "iencodable.h"

il::IEncodable::~IEncodable()
{
}

void il::IEncodable::writeTo(QJsonObject &json, const QString &tag)
{
    QJsonObject object;
    write(object);
    json[tag] = object;
}
