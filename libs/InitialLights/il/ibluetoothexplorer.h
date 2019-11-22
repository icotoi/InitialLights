#pragma once

#include "initiallights_global.h"
#include <QObject>

namespace il {

class Controller;

class INITIALLIGHTSSHARED_EXPORT IBluetoothExplorer : public QObject
{
    Q_OBJECT
public:
    virtual ~IBluetoothExplorer();

signals:
    void searchFinished();
    void connectedTo(Controller* controller);
    void disconnectedFrom(Controller* controller);
    void dataReadFrom(Controller* controller, QByteArray data);

public slots:
    virtual void searchControllers() = 0;
    virtual void connectTo(Controller* controller) = 0;
    virtual void disconnectFrom(Controller* controller) = 0;
    virtual void readDataFrom(Controller* controller) = 0;
    virtual void writeDataTo(Controller* controller) = 0;
    virtual void cancelCurrentOperation() = 0;

protected:
    explicit IBluetoothExplorer(QObject *parent = nullptr);
};

} // namespace il
