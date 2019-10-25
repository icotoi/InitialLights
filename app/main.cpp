#include <QDirIterator>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef Q_OS_ANDROID
// Because deployment sometimes just forgets to include this lib otherwise
// https://github.com/papyros/qml-material/issues/302
#include <QtSvg>
#endif

#include <QQmlContext>

#include "il/backend.h"
#include "il/controller.h"
#include "il/controllerlist.h"
#include "il/mainpage.h"
#include "il/room.h"
#include "il/light.h"

void showFontFamiliesAndStyles()
{
    QFontDatabase database;
    const QStringList fontFamilies = database.families();
    for (const QString &family : fontFamilies) {
        if (!(QStringList() << "Inter").contains(family))
            continue;

        qDebug() << "family:" << family;

        const QStringList fontStyles = database.styles(family);
        for (const QString &style : fontStyles) {
            QString sizes;
            const QList<int> smoothSizes = database.smoothSizes(family, style);
            for (int points : smoothSizes)
                sizes += QString::number(points) + ' ';
            qDebug() << "style:" << style << sizes.trimmed();
        }
    }
}

void loadAppFonts()
{
    QDirIterator it(":/Fonts/", QStringList() << "*.otf");
    qDebug() << "has custom font files?" << it.hasNext();
    while (it.hasNext()) {
        QString fontFileName = it.next();
        int id = QFontDatabase::addApplicationFont(fontFileName);
        qDebug() << (id >= 0 ? "loaded:" : "failed to load:") << fontFileName;
    }
}

int main(int argc, char *argv[])
{
    // register C++ types
    qmlRegisterUncreatableType<il::Controller>("InitialLights", 1, 0, "Controller", "Type cannot be created in QML");
    qmlRegisterUncreatableType<il::ControllerList>("InitialLights", 1, 0, "ControllerList", "Type cannot be created in QML");
    qmlRegisterUncreatableType<il::MainPage>("InitialLights", 1, 0, "MainPage", "Type cannot be created in QML");
    qmlRegisterUncreatableType<il::Room>("InitialLights", 1, 0, "Room", "Type cannot be created in QML");
    qmlRegisterUncreatableType<il::Light>("InitialLights", 1, 0, "Light", "Type cannot be created in QML");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setApplicationName("InitialLights");
    QCoreApplication::setOrganizationName("DeviceHub");
    QCoreApplication::setOrganizationDomain("net.devicehub");

    QGuiApplication app(argc, argv);

    loadAppFonts();
//    showFontFamiliesAndStyles();

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
