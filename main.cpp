#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bluetooth_bridge.h"
#include "clock_info.h"

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    clock_Info CLOCK_INFO;
    bluetooth_Bridge BLE_BRIDGE(&CLOCK_INFO);

    engine.rootContext()->setContextProperty("BLE_BRIDGE", &BLE_BRIDGE);
    engine.rootContext()->setContextProperty("CLOCK_INFO", &CLOCK_INFO);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
