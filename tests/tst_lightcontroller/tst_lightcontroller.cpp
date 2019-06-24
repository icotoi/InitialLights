#include <QtTest>

#include "il/controller.h"
#include "il/light.h"

class LightController : public QObject
{
    Q_OBJECT

private slots:
    void test_2AnalogicControllerUpdateDeviceCommand_data()
    {
        QTest::addColumn<int>("valueChannel0");
        QTest::addColumn<int>("valueChannel1");
        QTest::addColumn<QByteArray>("expectedCommand");

        QTest::newRow("00,00") << 0x00 << 0x00 << QByteArray("US0000000002\n");
        QTest::newRow("99,FF") << 0x99 << 0xFF << QByteArray("US99FF000002\n");
        QTest::newRow("FF,99") << 0xFF << 0x99 << QByteArray("USFF99000002\n");
        QTest::newRow("FF,FF") << 0xFF << 0xFF << QByteArray("USFFFF000002\n");
    }

    void test_2AnalogicControllerUpdateDeviceCommand()
    {
        QFETCH(int, valueChannel0);
        QFETCH(int, valueChannel1);
        QFETCH(QByteArray, expectedCommand);

        il::Controller dut;
        dut.set_isOnline(false);
        QJsonObject json = QJsonDocument::fromJson(
            "{ "
            "\"type\": \"V1_2x10V\", "
            "\"lights\": "
            "[ "
            "{ \"type\": \"Analogic\", \"minValue\": 0, \"maxValue\": 255 },"
            "{ \"type\": \"Analogic\", \"minValue\": 0, \"maxValue\": 255 }"
            "]"
            "}").object();

        dut.read(json);

        auto lights = dut.get_lights();
        lights->at(0)->setValue(valueChannel0);
        lights->at(1)->setValue(valueChannel1);

        QCOMPARE(dut.updateDeviceCommand(), expectedCommand);
    }

    void test_onOffPWMRGBControllerUpdateDeviceCommand_data()
    {
        QTest::addColumn<int>("pwm");
        QTest::addColumn<int>("red");
        QTest::addColumn<int>("green");
        QTest::addColumn<int>("blue");
        QTest::addColumn<bool>("pwmIsOn");
        QTest::addColumn<bool>("rgbIsOn");
        QTest::addColumn<QByteArray>("expectedCommand");

        QTest::newRow("00, 00, 00, 00, off, off") << 0x00 << 0x00 << 0x00 << 0x00 << false << false << QByteArray("US0000000001\n");
        QTest::newRow("00, 00, 00, 00, off, on") << 0x00 << 0x00 << 0x00 << 0x00 << false << true << QByteArray("US00FFFFFF01\n");
        QTest::newRow("00, 00, 00, 00, on, off") << 0x00 << 0x00 << 0x00 << 0x00 << true << false << QByteArray("USFF00000001\n");
        QTest::newRow("00, 00, 00, 00, on, on") << 0x00 << 0x00 << 0x00 << 0x00 << true << true << QByteArray("USFFFFFFFF01\n");

        QTest::newRow("00, 00, 00, FF, off, on") << 0x00 << 0x00 << 0x00 << 0xFF << false << true << QByteArray("US000000FF01\n");
    }

    void test_onOffPWMRGBControllerUpdateDeviceCommand()
    {
        QFETCH(int, pwm);
        QFETCH(int, red);
        QFETCH(int, green);
        QFETCH(int, blue);
        QFETCH(bool, pwmIsOn);
        QFETCH(bool, rgbIsOn);
        QFETCH(QByteArray, expectedCommand);

        il::Controller dut;
        dut.set_isOnline(false);

        QJsonObject json = QJsonDocument::fromJson(
                               "{ "
                               "\"type\": \"V1_1xPWM_1xRGB\", "
                               "\"lights\": "
                               "[ "
                               "{ \"type\": \"PWM\" },"
                               "{ \"type\": \"RGB\" }"
                               "]"
                               "}").object();

        dut.read(json);

        auto lights = dut.get_lights();
        auto pwmLight = lights->at(0);
        pwmLight->setValue(pwm);
        pwmLight->setIsOn(pwmIsOn);
        auto rgbLight = lights->at(1);
        rgbLight->set_redValue(red);
        rgbLight->set_greenValue(green);
        rgbLight->set_blueValue(blue);
        rgbLight->setIsOn(rgbIsOn);

        QCOMPARE(dut.updateDeviceCommand(), expectedCommand);
    }
};

QTEST_APPLESS_MAIN(LightController)

#include "tst_lightcontroller.moc"
