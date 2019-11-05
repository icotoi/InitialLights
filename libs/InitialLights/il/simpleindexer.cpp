#include "simpleindexer.h"

#include "iindexed.h"
#include <QDebug>

namespace il {

SimpleIndexer::SimpleIndexer(IIndexed *indexed, QObject *parent)
    : QObject(parent)
    , m_indexed(indexed)
{
//    qDebug() << "+++ SimpleIndexer()";
}

SimpleIndexer::~SimpleIndexer()
{
//    qDebug() << "--- SimpleIndexer()";
}

int SimpleIndexer::allocateNextFreeIndex()
{
    if (m_unusedIndexes.empty()) {
        return m_indexed->count();
    } else {
        int index = m_unusedIndexes.front();
        m_unusedIndexes.pop_front();
        return index;
    }
}

void SimpleIndexer::freeIndex(int index)
{
    m_unusedIndexes.push_back(index);
    m_unusedIndexes.erase(
        std::remove_if(m_unusedIndexes.begin(), m_unusedIndexes.end(),
                       [this](int i) { return i >= std::max(m_indexed->count(), m_indexed->maxIndex()); }),
        m_unusedIndexes.end()
        );
    std::sort(m_unusedIndexes.begin(), m_unusedIndexes.end());
    //    qDebug() << "unused room indexes:" << QList<int>::fromStdList(std::list<int>(m_unusedRoomIndexes.begin(), m_unusedRoomIndexes.end()));
}

void SimpleIndexer::rebuild()
{
    m_unusedIndexes.clear();
    std::vector<int> indexes = m_indexed->indexes();
    std::sort(indexes.begin(), indexes.end());
    int current = 0;
    for (int i: indexes) {
        while (current < i) {
            m_unusedIndexes.push_back(current);
            ++current;
        }
        ++current;
    }
}

}
