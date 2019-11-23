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
    void searchCanceled();
    void connectedTo(Controller* controller);
    void connectCanceled();
    void disconnectedFrom(Controller* controller);
    void disconnectCanceled();
    void dataReadFrom(Controller* controller, QByteArray data);
    void readDataCanceled();
    void writeDataCanceled();

public slots:
    virtual void search() = 0;
    virtual void connectTo(Controller* controller) = 0;
    virtual void disconnectFrom(Controller* controller) = 0;
    virtual void readDataFrom(Controller* controller) = 0;
    virtual void writeDataTo(Controller* controller) = 0;

    virtual void cancelSearch() = 0;
    virtual void cancelConnectTo(Controller* controller) = 0;
    virtual void cancelReadDataFrom(Controller* controller) = 0;
    virtual void cancelWriteDataTo(Controller* controller) = 0;

protected:
    explicit IBluetoothExplorer(QObject *parent = nullptr);
};

} // namespace il
