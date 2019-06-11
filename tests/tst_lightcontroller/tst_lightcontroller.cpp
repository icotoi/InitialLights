#include <QtTest>

#include "dummylightcontroller.h"
#include "lightcontrollervoltagechannel.h"

class LightController : public QObject
{
    Q_OBJECT

private slots:
    void test_2x10VupdateDeviceCommand_data()
    {
        QTest::addColumn<int>("valueChannel0");
        QTest::addColumn<int>("valueChannel1");
        QTest::addColumn<QByteArray>("expectedCommand");

        QTest::newRow("00,00") << 0x00 << 0x00 << QByteArray("US0000000002\n");
        QTest::newRow("99,FF") << 0x99 << 0xFF << QByteArray("US99FF000002\n");
        QTest::newRow("FF,99") << 0xFF << 0x99 << QByteArray("USFF99000002\n");
        QTest::newRow("FF,FF") << 0xFF << 0xFF << QByteArray("USFFFF000002\n");
    }

    void test_2x10VupdateDeviceCommand()
    {
        QFETCH(int, valueChannel0);
        QFETCH(int, valueChannel1);
        QFETCH(QByteArray, expectedCommand);

        il::DummyLightController dut(il::AbstractLightController::V1_2x10V, "", "");
        dut.set_connectDelay(0);
        dut.connectToController();

        auto channels = dut.get_voltageChannels();
        channels->at(0)->set_value(valueChannel0);
        channels->at(1)->set_value(valueChannel1);

        QCOMPARE(dut.updateDeviceCommand(), expectedCommand);
    }
};

QTEST_APPLESS_MAIN(LightController)

#include "tst_lightcontroller.moc"
