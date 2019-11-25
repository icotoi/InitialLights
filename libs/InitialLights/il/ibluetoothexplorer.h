#pragma once

#include "initiallights_global.h"

#include "QQmlVarPropertyHelpers.h"

#include <QObject>

namespace il {

class Controller;

class INITIALLIGHTSSHARED_EXPORT IBluetoothExplorer : public QObject
{
    Q_OBJECT

    QML_READONLY_VAR_PROPERTY(bool, isSearching)
    QML_WRITABLE_VAR_PROPERTY(QString, message)
    QML_WRITABLE_VAR_PROPERTY(int, searchTimeout)

public:
    virtual ~IBluetoothExplorer();

signals:
    void searchFinished();

public slots:
    virtual void search() = 0;

protected:
    explicit IBluetoothExplorer(QObject *parent = nullptr);
};

} // namespace il
