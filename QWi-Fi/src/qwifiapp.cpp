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
    _deviceInfoRegExp.setPattern("(([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2})\nflags(.|\\s)*rx_bytes=([0-9]+)(.|\\s)*tx_bytes=([0-9]+)(.|\\s)*connected_time=([0-9]+)");
    _devicesMonitorTimer.setInterval(2000);
}

QAbstractItemModel* QWiFiApp::getDeviceModel(){
    return _deviceModel;
}

int QWiFiApp::getDevicesCount(){
    return _devicesCount;
}

void QWiFiApp::setDevicesCount(int count){
    _devicesCount = count;
    emit devicesCountChanged();
}

void QWiFiApp::setActiveIterface(QString iface){
    _activeInterface = iface;
}

void QWiFiApp::setCurrentWiFiConfigPath(QString path){
    _currentWiFiConfigPath = path;
}

void QWiFiApp::startWiFiAP(QString channel, QString gateway, bool isolation, bool hidden,
                           QString inthernetIface, QString wifiIface, QString ssid, QString password){
    QStringList arguments;
    arguments << "create_ap" << "-c" << channel << "-g" << gateway << "--no-virt";
    if(isolation){
        arguments << "--isolate-clients" ;
    }
    if(hidden){
        arguments << "--hidden" ;
    }
    arguments << wifiIface << inthernetIface << ssid << password;

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

    if(output.contains("AP-ENABLED")){

        setActiveIterface(output.split(":")[0]);
        qDebug() << output << "started";
        emit wifiAPStarted();

    }else if(output.contains("Config dir")){

        QString path = output.split(":")[1].simplified();
        setCurrentWiFiConfigPath(path);

    }else if(output.contains("AP-STA-CONNECTED")){

        QString mac = output.split(" ").last().simplified();
        QString message = tr("New device %1 connected").arg(mac);
        emit  newMessage(message);
        setDevicesCount(_devicesCount+1);
        qDebug() << output << "client IN";

    }else if(output.contains("AP-STA-DISCONNECTED")){

        QString mac = output.split(" ").last().simplified();
        QString message = tr("Device %1 disconnected").arg(mac);
        emit  newMessage(message);
        setDevicesCount(_devicesCount-1);
        qDebug() << output << "client OUT";

    }
}
void QWiFiApp::wifiReadyErrorOutput(QString errorOutput){
    qDebug() << errorOutput;
    MessageType messageType = Info;
    QString message="";

    if(errorOutput.contains("not possible due to RF-kill") ||  errorOutput.contains("rfkill unblock")){
        message = tr("Your adapter seems disabled, please enable it");
        messageType = Error;
    }else if(errorOutput.startsWith("ERROR: ")){
        if(errorOutput.contains("not support AP")){
            message = tr("Your adapter does not support AP (master) mode");
        }else if(errorOutput.contains("and an AP at the same time")){
            message = tr("Your adapter can not be a station and an AP at the same time");
        }else{
            message = errorOutput.remove(0,7);
        }
        messageType = Error;
    }else if(errorOutput.startsWith("WARN: ")){
        message = errorOutput.remove(0,6);
        messageType = Warning;
    }

    emit wifiAPStopped();
    emit newMessage(message.simplified(),messageType);
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
    setDevicesCount(0);
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
    // Starting the monitor just after the timer starts... emiting a timeout signal
    connect(thread, SIGNAL(started()), &_devicesMonitorTimer, SIGNAL(timeout()));
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
        while ((index = _deviceInfoRegExp.indexIn(output, index)) != -1){
            ++index;
            QString mac = _deviceInfoRegExp.cap(1);
            const quint64 bytesWrited = _deviceInfoRegExp.cap(4).toULongLong();
            const quint64 bytesReaded = _deviceInfoRegExp.cap(6).toULongLong();
            const int connTime = _deviceInfoRegExp.cap(8).toInt();
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
