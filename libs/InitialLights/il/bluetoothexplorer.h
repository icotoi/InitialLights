#pragma once

#include "ibluetoothexplorer.h"

namespace il {

class INITIALLIGHTSSHARED_EXPORT BluetoothExplorer : public IBluetoothExplorer
{
    Q_OBJECT
public:
    explicit BluetoothExplorer(QObject *parent = nullptr);

public slots:
    void searchControllers() override;
    void connectTo(Controller *controller) override;
    void disconnectFrom(Controller *controller) override;
    void readDataFrom(Controller *controller) override;
    void writeDataTo(Controller *controller) override;
    void cancelCurrentOperation() override;
};

} // namespace il
