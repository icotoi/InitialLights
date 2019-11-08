#include <QtTest>

#include "il/roomcollection.h"
#include "il/room.h"
#include "il/simpleindexer.h"

class RoomCollection : public QObject
{
    Q_OBJECT

private slots:
    void test_noRoomsOnCreation()
    {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        QCOMPARE(dut.get_items()->count(), 0);
    }

    void test_add1()
    {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        dut.appendNewRoom();
        QCOMPARE(dut.get_items()->count(), 1);
        QCOMPARE(dut.get_items()->at(0)->rid(), 0);
    }

    void test_add2()
    {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        dut.appendNewRoom();
        dut.appendNewRoom();
        QCOMPARE(dut.get_items()->count(), 2);
        QCOMPARE(dut.get_items()->at(1)->rid(), 1);
    }

    void test_add2Remove1()
    {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        dut.appendNewRoom();
        dut.appendNewRoom();
        dut.removeRoom(0);
        QCOMPARE(dut.get_items()->count(), 1);
        QCOMPARE(dut.get_items()->at(0)->rid(), 1);
    }

    void test_add2Remove1Add1() {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        dut.appendNewRoom();
        dut.appendNewRoom();
        dut.removeRoom(0);
        dut.appendNewRoom();
        QCOMPARE(dut.get_items()->count(), 2);
        QCOMPARE(dut.get_items()->at(0)->rid(), 1);
        QCOMPARE(dut.get_items()->at(1)->rid(), 0);
    }

    void test_add2Remove2Add1() {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        dut.appendNewRoom();
        dut.appendNewRoom();
        dut.removeRoom(1);
        dut.removeRoom(0);
        dut.appendNewRoom();
        QCOMPARE(dut.get_items()->count(), 1);
        QCOMPARE(dut.get_items()->at(0)->rid(), 0);
    }

    void test_add4Remove2Add1Remove1Add3() {
        il::RoomCollection dut([](il::IIndexed* indexed, QObject* parent) { return new il::SimpleIndexer(indexed, parent); });
        dut.appendNewRoom(); // 0
        dut.appendNewRoom(); // 0, 1
        dut.appendNewRoom(); // 0, 1, 2
        dut.appendNewRoom(); // 0, 1, 2, 3
        dut.removeRoom(1); // 0, 2, 3
        dut.removeRoom(0); // 2, 3
        dut.appendNewRoom(); // 2, 3, 0
        dut.removeRoom(0); // 3, 0
        dut.appendNewRoom(); // 3, 0, 1
        dut.appendNewRoom(); // 3, 0, 1, 2
        dut.appendNewRoom(); // 3, 0, 1, 2, 4
        QCOMPARE(dut.get_items()->count(), 5);
        QCOMPARE(dut.get_items()->at(0)->rid(), 3);
        QCOMPARE(dut.get_items()->at(1)->rid(), 0);
        QCOMPARE(dut.get_items()->at(2)->rid(), 1);
        QCOMPARE(dut.get_items()->at(3)->rid(), 2);
        QCOMPARE(dut.get_items()->at(4)->rid(), 4);
    }

    void test_maxIndexForEmptyReturns0() {
        il::RoomCollection dut([](il::IIndexed*, QObject*){ return nullptr; });
        QCOMPARE(dut.maxIndex(), 0);
    }
};

QTEST_APPLESS_MAIN(RoomCollection)

#include "tst_roomcollection.moc"
