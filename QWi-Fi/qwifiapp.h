#ifndef QWIFIAPP_H
#define QWIFIAPP_H

#include <QObject>
#include <QList>
#include <QRegExp>


class QWiFiApp : public QObject
{
    Q_OBJECT
public:

    explicit QWiFiApp(QObject *parent = 0);
    bool isUp();
    void denyAcces(QString mac, QString ip);
    void setActiveIterface(QString iface);


public slots:
    void startWiFiAP(QString wifiIface, QString inthernetIface, QString ssid, QString password);
    void stopWiFiAP();
    void wifiReadyOutput(QString output);
    void wifiReadyErrorOutput(QString output);


signals:
    void wifiAPStarted();
    void wifiAPStopped();
    void newMessage(const QString &msg);

private:
    QString _activeInterface;
    QRegExp _apEnabled;
    QRegExp _clientIn;
    QRegExp _clientOut;

};

#endif // QWIFIAPP_H
