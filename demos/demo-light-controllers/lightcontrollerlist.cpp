#include "lightcontrollerlist.h"

#include "deviceinfo.h"
#include "lightcontroller.h"
#include "dummylightcontroller.h"

namespace il {

LightControllerList::LightControllerList(QObject *parent)
    : QObject (parent)
    , m_scanning { false }
    , m_scanningTimeout { 3000 }
    , m_controllers { new QQmlObjectListModel<AbstractLightController>(this) }
{
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &LightControllerList::deviceDiscovered);
    connect(&m_deviceDiscoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error),
            this, &LightControllerList::scanError);
    connect(&m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &LightControllerList::scanFinished);

    // add some dummy controllers
    createDummyControllers();
}

LightControllerList::~LightControllerList()
{
}

void LightControllerList::scan()
{
    update_scanning(true);
    set_message("Scanning for devices...");
    m_controllers->clear();
    m_deviceDiscoveryAgent.setLowEnergyDiscoveryTimeout(m_scanningTimeout);
    m_deviceDiscoveryAgent.start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

bool LightControllerList::deviceAlreadyScanned(const QBluetoothDeviceInfo &info) const
{
    auto address = DeviceInfo::address(info);
    return std::any_of(m_controllers->begin(), m_controllers->end(), [address](AbstractLightController* controller){
       return controller->address() == address;
    });
}

void LightControllerList::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    if (DeviceInfo::isValidDevice(info)) {
        if (!deviceAlreadyScanned(info)) {
            auto deviceInfo = new DeviceInfo(info);
            auto controller = new LightController(deviceInfo);
            m_controllers->append(controller);
            qWarning() << "LE Device name:" << deviceInfo->name()
                       << "address:" << deviceInfo->address() << "scanned; adding it to the devices list...";
        }
        set_message("Low Energy device found. Scanning for more...");
    }
    //...
}

void LightControllerList::scanError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    switch (error) {
    case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
        set_message("The Bluetooth adaptor is powered off, power it on before doing discovery.");
        break;
    case QBluetoothDeviceDiscoveryAgent::InputOutputError:
        set_message("Writing or reading from the device resulted in an error.");
        break;
    default:
        set_message("An unknown error has occurred.");
    }
}

void LightControllerList::scanFinished()
{
    qDebug() << "scan finished";
    update_scanning(false);
    set_message(m_controllers->size() == 0
               ? "No Low Energy devices found"
               : QString("Found %1 device(s)").arg(m_controllers->size()));

    if (m_controllers->size() == 0) {
        // recreate the dummy controllers
        createDummyControllers();
    }
}

void LightControllerList::createDummyControllers()
{
    m_controllers->append(new DummyLightController(AbstractLightController::V1_4xPWM,
                                                   "Dummy 4 x PWM (v1)",
                                                   "{xxx-xxx-001}"));
    m_controllers->append(new DummyLightController(AbstractLightController::V1_1xPWM_1xRGB,
                                                   "Dummy 1 x PWM + 1 x RGB (v1)",
                                                   "{xxx-xxx-002}"));
    m_controllers->append(new DummyLightController(AbstractLightController::V1_2x10V,
                                                   "Dummy 2 x 10V (v1)",
                                                   "{xxx-xxx-003}"));
}

}

//LightsUart::LightsUart()
//    : m_currentDevice(QBluetoothDeviceInfo()),
//      m_foundUartService(false),
//      m_max(0),
//      m_min(0),
//      m_calories(0),
//      m_control(nullptr),
//      m_timer(nullptr),
//      m_service(nullptr)
//{
//    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

//    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
//            this, &LightsUart::addDevice);
//    connect(m_deviceDiscoveryAgent, qOverload<QBluetoothDeviceDiscoveryAgent::Error>(&QBluetoothDeviceDiscoveryAgent::error),
//            this, &LightsUart::deviceScanError);
//    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
//            this, &LightsUart::scanFinished);

//    // initialize random seed for demo mode
//    // FIXME: qsrand is obsolete
////    qsrand(QTime::currentTime().msec());
//}

//void LightsUart::obtainResults()
//{
//}

//int LightsUart::measurements(int index) const
//{
//    if (index > m_measurements.size())
//        return 0;
//    else
//        return m_measurements.value(index);
//}

//int LightsUart::measurementsSize() const
//{
//    return m_measurements.size();
//}
