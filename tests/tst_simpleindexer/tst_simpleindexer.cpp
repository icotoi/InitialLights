#include <QtTest>

#include "il/simpleindexer.h"
#include "il/iindexed.h"
#include "fakeit.hpp"

using namespace fakeit;

class SimpleIndexer : public QObject
{
    Q_OBJECT

private slots:
    void test_rebuild_data()
    {
        QTest::addColumn<std::vector<int>>("indexes");
        QTest::addColumn<int>("nextFreeIndex");

        QTest::newRow("{   } -> 0") << std::vector<int> {   } << 0;
        QTest::newRow("{ 0 } -> 1") << std::vector<int> { 0 } << 1;
        QTest::newRow("{ 1 } -> 0") << std::vector<int> { 1 } << 0;
        QTest::newRow("{ 0, 1 } -> 2") << std::vector<int> { 0, 1 } << 2;
        QTest::newRow("{ 1, 0 } -> 2") << std::vector<int> { 1, 0 } << 2;
        QTest::newRow("{ 0, 2 } -> 1") << std::vector<int> { 0, 2 } << 1;
        QTest::newRow("{ 2, 1 } -> 0") << std::vector<int> { 2, 1 } << 0;
    }

    void test_rebuild()
    {
        QFETCH(std::vector<int>, indexes);
        QFETCH(int, nextFreeIndex);

        Mock<il::IIndexed> mock;
        When(Method(mock, indexes)).Return(indexes);
        When(Method(mock, count)).Return(int(indexes.size()));
        il::IIndexed& indexed = mock.get();

        il::SimpleIndexer dut(&indexed);
        dut.rebuild();
        QCOMPARE(dut.allocateNextFreeIndex(), nextFreeIndex);
    }

};

QTEST_APPLESS_MAIN(SimpleIndexer)

#include "tst_simpleindexer.moc"
