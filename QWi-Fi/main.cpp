#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qwifiapp.h"
#include "qwifi_global.h"
#include "singleapplication.h"
#include "translation.h"
#include "networkutility.h"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("QWi-Fi");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    SingleApplication single( "QWiFi" );
    if ( !single.tryToRun() )
        return 0;

    QApplication app(argc, argv);

    QWiFi::Utils::initBD();

    qmlRegisterType<QWiFiApp>("QWiFi", 1, 0, "QWiFiApp");
    qmlRegisterType<NetworkUtility>("QWiFi", 1, 0, "NetworkUtility");

    QQmlApplicationEngine engine;

    Translation trans;
    engine.rootContext()->setContextProperty("trans", &trans);

    engine.load(QUrl(QLatin1String("qrc:/qml/QWiFi.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
