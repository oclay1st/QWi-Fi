#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <QSettings>

#include "qwifiapp.h"
#include "qwifi_global.h"
#include "singleapplication.h"
#include "networkutility.h"


int main(int argc, char *argv[])
{
    QApplication::setApplicationName("QWi-Fi");
    QApplication::setOrganizationName("FOSS");
    QApplication::setOrganizationDomain("CU");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    SingleApplication single("QWi-Fi");
    if ( !single.tryToRun() )
        return 0;

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/resources/images/qwifi.png"));

    QSettings settings;

    /*Config translations*/
    QTranslator translator;
    QString systemLocale = QLocale::system().name().section('_', 0, 0);
    QString locale = settings.value("appConfig/language", systemLocale).toString();
    if(translator.load(QLocale(locale),QString("qwifi"),QString("_"),QString(":/resources/translations"))){
        app.installTranslator(&translator);
        settings.setValue("appConfig/language",locale);
    }else{
        qDebug() << "Failed to load translation";
        settings.setValue("appConfig/language","en");
    }

    /*Config database*/
    QWiFi::Utils::initBD();

    /*Config C++ classes*/
     qmlRegisterType<QWiFiApp>("QWiFi", 1, 0, "QWiFiApp");
    qmlRegisterType<NetworkUtility>("QWiFi", 1, 0, "NetworkUtility");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QLatin1String("qrc:/qml/QWiFi.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();

}
