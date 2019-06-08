//#include <QtCore/QLoggingCategory>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "lightsuart.h"

int main(int argc, char *argv[])
{
    //    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    il::LightsUart lightsUart;
    engine.rootContext()->setContextProperty("lightsUart", &lightsUart);

    const QUrl url(QStringLiteral("qrc:/assets/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
