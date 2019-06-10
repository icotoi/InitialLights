#pragma once

#include "abstractlightcontroller.h"

namespace il {

class DummyLightController : public AbstractLightController
{
public:
    DummyLightController(ControllerType controllerType, const QString& name, const QString& address, QObject* parent = nullptr);

public slots:
    void connectToController() override;
    void disconnectFromController() override;

private:
    void clear();
};

} // namespace il
