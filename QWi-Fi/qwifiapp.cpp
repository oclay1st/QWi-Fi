#include <QThread>
#include <QStringList>
#include <QDebug>
#include <QFile>

#include "qwifiapp.h"
#include "worker.h"
#include "qwifi_global.h"

QWiFiApp::QWiFiApp(QObject *parent) : QObject(parent)
{
    _deviceModel = new DeviceModel(this);
    _apEnabled.setPattern("\\bAP-ENABLED\\b");
    _clientIn.setPattern("\\bAP-STA-CONNECTED\\b");
    _clientOut.setPattern("\\bAP-STA-DISCONNECTED\\b");
    _wifiConfigDir.setPattern("\\bConfig dir\\b");
    _deviceInfo.setPattern("(([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2})\nflags(.|\\s)*rx_bytes=([0-9]+)(.|\\s)*tx_bytes=([0-9]+)(.|\\s)*connected_time=([0-9]+)");
    _devicesMonitorTimer.setInterval(2000);
}

QAbstractItemModel* QWiFiApp::getDeviceModel(){
    return _deviceModel;
}

void QWiFiApp::setActiveIterface(QString iface){
    _activeInterface = iface;
}

void QWiFiApp::setCurrentWiFiConfigPath(QString path){
    _currentWiFiConfigPath = path;
}

void QWiFiApp::startWiFiAP(QString inthernetIface, QString wifiIface, QString ssid, QString password){
    QStringList arguments;
    arguments << "create_ap" << "--no-virt" << wifiIface << inthernetIface << ssid << password;
    QThread *thread = new QThread(this);
    Worker *worker = new Worker("pkexec", arguments);
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(readyOutput(QString)),this,SLOT(wifiReadyOutput(QString)));
    connect(worker, SIGNAL(readyErrorOutput(QString)),this,SLOT(wifiReadyErrorOutput(QString)));
    connect(worker, SIGNAL(processfinished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(processfinished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}

void QWiFiApp::wifiReadyOutput(QString output){
    if(_apEnabled.indexIn(output)!=-1){

        setActiveIterface(output.split(":")[0]);
        qDebug() << output << "started";
        emit wifiAPStarted();

    }else if(_wifiConfigDir.indexIn(output)!=-1){

        QString path = output.split(":")[1].simplified();
        setCurrentWiFiConfigPath(path);

    }else if(_clientIn.indexIn(output)!=-1){

        qDebug() << output << "client IN";
        emit  newMessage(output);

    }else if(_clientOut.indexIn(output)!=-1){

        qDebug() << output << "client OUT";
        emit  newMessage(output);

    }
}
void QWiFiApp::wifiReadyErrorOutput(QString errorOutput){
    qDebug() << errorOutput;
    emit  newMessage(errorOutput);
}

void QWiFiApp::stopWiFiAP(){
    QProcess *process = new QProcess(this);
    QStringList arguments;
    arguments << "create_ap" << "--stop" << _activeInterface;
    connect(process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            [=](int exitCode, QProcess::ExitStatus){
        if (exitCode != 0) {
            qDebug() << "Errror ocurred";
        }else{
            setActiveIterface("");
            emit wifiAPStopped();
        }
    });
    process->start("pkexec", arguments);
}


void QWiFiApp::startDevicesMonitor(){

    QStringList arguments;
    arguments << "hostapd_cli";
    arguments << "-p" << _currentWiFiConfigPath + "/hostapd_ctrl";
    arguments << "-i" << _activeInterface;
    arguments << "all_sta";

    QThread *thread = new QThread(this);
    Worker *worker = new Worker("pkexec", arguments, true);
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), &_devicesMonitorTimer, SLOT(start()));
    connect(this,SIGNAL(wifiAPStopped()),this,SLOT(stopDevicesMonitor()));
    connect(&_devicesMonitorTimer, SIGNAL(timeout()), worker,SLOT(process()));
    connect(worker, SIGNAL(readyAllOutput(QString)),this,SLOT(monitorReadyOutput(QString)));
    connect(worker, SIGNAL(readyErrorOutput(QString)),this,SLOT(monitorReadyErrorOutput(QString)));
    connect(this, SIGNAL(devicesMonitorStopped()), thread, SLOT(quit()));
    connect(this, SIGNAL(devicesMonitorStopped()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
    emit devicesMonitorStarted();
}


void QWiFiApp::monitorReadyOutput(QString output){

    if(!output.isEmpty()){
        QStringList currentMacs; int index = 0;
        while ((index = _deviceInfo.indexIn(output, index)) != -1){
            ++index;
            QString mac = _deviceInfo.cap(1);
            const quint64 bytesWrited = _deviceInfo.cap(4).toULongLong();
            const quint64 bytesReaded = _deviceInfo.cap(6).toULongLong();
            const int connTime = _deviceInfo.cap(8).toInt();
            currentMacs << mac;

            QModelIndex modelIndex = _deviceModel->lookup(mac);
            if (!modelIndex.isValid()){
                QString manufacturer = QWiFi::Utils::macDescription(mac.section(":", 0, 2));
                Device *dev = new Device(QString(), QString(), mac, manufacturer, bytesReaded, bytesWrited, connTime);
                _deviceModel->addDevice(dev);
            }else{
                _deviceModel->setData(modelIndex, bytesWrited, DeviceModel::BytesWritedRole);
                _deviceModel->setData(modelIndex, bytesReaded, DeviceModel::BytesReadedRole);
                _deviceModel->setData(modelIndex, connTime, DeviceModel::ConnectionTimeRole);
            }
        }
        _deviceModel->removeNoMatchingDevice(currentMacs);
        this->_setNameAndIpAdress();

        emit deviceModelChanged();

    }else if(_deviceModel->rowCount()!=0){
        _deviceModel->removeAllDevices();

        emit deviceModelChanged();
    }
}

void QWiFiApp::_setNameAndIpAdress(){

    QFile leases(_currentWiFiConfigPath + "/dnsmasq.leases");
    if (leases.open(QIODevice::ReadOnly)){
        QTextStream stream(&leases);
        QString line;
        while (!(line = stream.readLine()).isNull()){
            QStringList parts = line.split(" ");
            Q_ASSERT(parts.length() == 5);
            const QString &mac = parts[1];
            const QString &ip = parts[2];
            const QString &name = parts[3];
            QModelIndex index = _deviceModel->lookup(mac);
            if (index.isValid()) {
                _deviceModel->setData(index, ip, DeviceModel::IpRole);
                _deviceModel->setData(index, name, DeviceModel::NameRole);
            }
        }
    }else{
        stopDevicesMonitor();
        qDebug() << "The dnsmasq leases file has failed whe opened: " << leases.errorString();
    }
}

void QWiFiApp::monitorReadyErrorOutput(QString output){
    qDebug() << output;
}

void QWiFiApp::stopDevicesMonitor(){
    _devicesMonitorTimer.stop();
    _deviceModel->removeAllDevices();
    emit devicesMonitorStopped();
}
