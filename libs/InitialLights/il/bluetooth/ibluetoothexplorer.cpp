#include "ibluetoothexplorer.h"

namespace il {
namespace bluetooth {

IBluetoothExplorer::IBluetoothExplorer(QObject *parent)
    : QObject(parent)
    , m_isSearching { false }
    , m_searchTimeout { 3000 }
{
}

IBluetoothExplorer::~IBluetoothExplorer()
{
}

} // namespace bluetooth
} // namespace il
