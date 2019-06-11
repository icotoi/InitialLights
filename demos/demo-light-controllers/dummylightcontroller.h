#pragma once

#include "abstractlightcontroller.h"

namespace il {

class DummyLightController : public AbstractLightController
{
    Q_OBJECT

    QML_WRITABLE_AUTO_PROPERTY(int, connectDelay)

public:
    DummyLightController(ControllerType controllerType, const QString& name, const QString& address, QObject* parent = nullptr);

public slots:
    void connectToController() override;
    void disconnectFromController() override;

private:
    void connectToControllerFinished();
};

} // namespace il
