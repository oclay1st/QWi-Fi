#ifndef QWIFIAPP_H
#define QWIFIAPP_H

#include <QObject>
#include <QRegExp>
#include <QTimer>

#include "devicemodel.h"

class QWiFiApp : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* deviceModel  READ getDeviceModel NOTIFY deviceModelChanged)

public:
    explicit QWiFiApp(QObject *parent = 0);
    bool isUp();
    void setActiveIterface(QString iface);
    void setCurrentWiFiConfigPath(QString path);
    QAbstractItemModel* getDeviceModel();


public slots:
    void startWiFiAP(QString wifiIface, QString inthernetIface, QString ssid, QString password);
    void stopWiFiAP();
    void wifiReadyOutput(QString output);
    void wifiReadyErrorOutput(QString output);
    void startDevicesMonitor();
    void stopDevicesMonitor();
    void monitorReadyOutput(QString output);
    void monitorReadyErrorOutput(QString output);


signals:
    void wifiAPStarted();
    void wifiAPStopped();
    void devicesMonitorStarted();
    void devicesMonitorStopped();
    void newMessage(const QString &msg);
    void deviceModelChanged();

private:
    void _setNameAndIpAdress();

private:
    QString _activeInterface;
    QString _currentWiFiConfigPath;
    QRegExp _apEnabled;
    QRegExp _clientIn;
    QRegExp _clientOut;
    QRegExp _wifiConfigDir;
    QRegExp _deviceInfo;

    QTimer _devicesMonitorTimer;
    DeviceModel *_deviceModel;


};

#endif // QWIFIAPP_H
