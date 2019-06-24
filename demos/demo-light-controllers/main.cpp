//#include <QtCore/QLoggingCategory>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef Q_OS_ANDROID
// Because deployment sometimes just forgets to include this lib otherwise
// https://github.com/papyros/qml-material/issues/302
#include <QtSvg>
#endif

#include <QQmlEngine>

#include "lightcontrollerlist.h"

int main(int argc, char *argv[])
{
    //    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    il::LightControllerList lightControllers;
    engine.rootContext()->setContextProperty("lightControllers", &lightControllers);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
