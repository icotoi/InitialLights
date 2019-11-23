#pragma once

#include "ibluetoothexplorer.h"

namespace il {

class ControllerCollection;

class INITIALLIGHTSSHARED_EXPORT BluetoothExplorer : public IBluetoothExplorer
{
    Q_OBJECT
public:
    explicit BluetoothExplorer(ControllerCollection* controllers, QObject *parent = nullptr);

public slots:
    void search() override;
    void connectTo(Controller *controller) override;
    void disconnectFrom(Controller *controller) override;
    void readDataFrom(Controller *controller) override;
    void writeDataTo(Controller *controller) override;

    void cancelSearch() override;
    void cancelConnectTo(Controller *controller) override;
    void cancelReadDataFrom(Controller *controller) override;
    void cancelWriteDataTo(Controller *controller) override;

private:
    ControllerCollection* m_controllers;

};

} // namespace il
