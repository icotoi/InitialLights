#pragma once

#include "abstractlightcontroller.h"

namespace il {

class DeviceInfo;

class LightController : public AbstractLightController
{
    Q_OBJECT

public:
    explicit LightController(DeviceInfo* info, QObject *parent = nullptr);
    ~LightController() override;

public slots:
    void connectToController() override;
    void disconnectFromController() override;

private:
    DeviceInfo* m_info;

};

} // namespace il
