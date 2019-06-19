#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef Q_OS_ANDROID
// Because deployment sometimes just forgets to include this lib otherwise
// https://github.com/papyros/qml-material/issues/302
#include <QtSvg>
#endif

#include <QQmlContext>

#include "il/backend.h"
#include "il/controllerlist.h"
#include "il/room.h"
#include "il/light.h"

int main(int argc, char *argv[])
{
    qmlRegisterUncreatableType<il::ControllerList>("InitialLights", 1, 0, "ControllerList", "Type cannot be created in QML");
    qmlRegisterUncreatableType<il::Room>("InitialLights", 1, 0, "Room", "Type cannot be created in QML");
    qmlRegisterUncreatableType<il::Light>("InitialLights", 1, 0, "Light", "Type cannot be created in QML");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setApplicationName("InitialLights");
    QCoreApplication::setOrganizationName("DeviceHub");
    QCoreApplication::setOrganizationDomain("net.devicehub");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    il::BackEnd backend;
    backend.loadLocalData();
    engine.rootContext()->setContextProperty("backend", &backend);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    int ret = app.exec();
    backend.saveLocalData();
    return ret;
}
