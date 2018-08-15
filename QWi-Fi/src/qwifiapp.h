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
    Q_PROPERTY(int devicesCount  READ getDevicesCount NOTIFY devicesCountChanged)

public:
    explicit QWiFiApp(QObject *parent = 0);
    bool isUp();
    void setActiveIterface(QString iface);
    void setCurrentWiFiConfigPath(QString path);
    QAbstractItemModel* getDeviceModel();
    int getDevicesCount();
    void setDevicesCount(int count);
    enum MessageType{
        Success = 1,
        Info = 2,
        Warning =3,
        Error = 4
    };
    Q_ENUM(MessageType)


public slots:
    void startWiFiAP(QString channel, QString gateway, bool isolation, bool hidden,
                     QString inthernetIface, QString wifiIface, QString ssid, QString password);
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
    void newMessage(const QString &msg,enum MessageType messageType=Info);
    void deviceModelChanged();
    void devicesCountChanged();

private:
    void _setNameAndIpAdress();

private:
    int _devicesCount=0;
    QString _activeInterface;
    QString _currentWiFiConfigPath;
    QRegExp _deviceInfoRegExp;

    QTimer _devicesMonitorTimer;
    DeviceModel *_deviceModel;


};

#endif // QWIFIAPP_H
