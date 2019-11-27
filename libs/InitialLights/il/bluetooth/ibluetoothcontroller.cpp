#include "ibluetoothcontroller.h"

namespace il {
namespace bluetooth {

IBluetoothController::IBluetoothController(QObject *parent)
    : QObject(parent)
    , m_isConnected { false }
    , m_isConnecting { false }
{    
}

IBluetoothController::~IBluetoothController()
{
}

} // namespace bluetooth
} // namespace il
