#include "ibluetoothexplorer.h"

namespace il {

IBluetoothExplorer::IBluetoothExplorer(QObject *parent)
    : QObject(parent)
    , m_isSearching { false }
    , m_searchTimeout { 3000 }
{
}

IBluetoothExplorer::~IBluetoothExplorer()
{
}

} // namespace il
