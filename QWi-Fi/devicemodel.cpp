/***This code comes from QHotSpotQML(by H3R3TIC), but it has some changes**/

#include "devicemodel.h"
#include "qwifi_global.h"

DeviceModel::DeviceModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

QHash<int, QByteArray> DeviceModel::roleNames() const noexcept
{
    QHash<int, QByteArray> roles;

    roles[NameRole] = "name";
    roles[MacRole] = "mac";
    roles[IpRole] = "ip";
    roles[BytesReadedRole] = "bytesReaded";
    roles[BytesWritedRole] = "bytesWrited";
    roles[DownloadRateRole] = "downloadRate";
    roles[UploadRateRole] = "uploadRate";
    roles[ManufacturerRole] = "manufacturer";
    roles[ConnectionCountRole] = "connCount";
    roles[ConnectionTimeRole] = "connTime";

    return roles;
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const noexcept
{
    if (!index.isValid()) {
        return QVariant();
    }
    Device *dev = _devices[index.row()];

    switch (role) {
    case Qt::DisplayRole:
        break;

    case NameRole:
        return dev->name();
        break;

    case MacRole:
        return dev->mac();
        break;

    case IpRole:
        return dev->ip();
        break;

    case BytesReadedRole:
        return QWiFi::Utils::sizeFormat(dev->bytesReaded());
        break;

    case BytesWritedRole:
        return QWiFi::Utils::sizeFormat(dev->bytesWrited());
        break;

    case DownloadRateRole:
        return QWiFi::Utils::sizeFormat(dev->downloadRate()/2) + "/s";
        break;

    case UploadRateRole:
        return QWiFi::Utils::sizeFormat(dev->uploadRate()/2) + "/s";
        break;

    case ManufacturerRole:
        return dev->manufacturer();
        break;

    case ConnectionCountRole:
        return dev->connCount();
        break;

    case ConnectionTimeRole:
        return dev->connTime();
        break;

    default:
        break;
    }

    return QVariant();
}

bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role) noexcept
{
    if (!index.isValid()){
        return false;
    }
    Device *dev = _devices[index.row()];
    QVector<int> roles;
    roles << role;

    switch (role) {
    case NameRole:
        dev->setName(value.toString());
        break;

    case MacRole:
        dev->setMac(value.toString());
        break;

    case IpRole:
        dev->setIp(value.toString());
        break;

    case BytesReadedRole:
        dev->setDownloadRate(value.toULongLong() - dev->bytesReaded());
        dev->setBytesReaded(value.toULongLong());
        roles << DownloadRateRole;
        break;

    case BytesWritedRole:
        dev->setUploadRate(value.toULongLong() - dev->bytesWrited());
        dev->setBytesWrited(value.toULongLong());
        roles << UploadRateRole;
        break;

    case ManufacturerRole:
        dev->setManufacturer(value.toString());
        break;

    case ConnectionCountRole:
        dev->setConnCount(value.toInt());
        break;

    case ConnectionTimeRole:
        dev->setConnTime(value.toInt());
        break;

    default:
        return false;
    }

    emit dataChanged(index, index,roles);

    return true;
}

QModelIndex DeviceModel::index(int row, int column, const QModelIndex &parent) const noexcept
{
    Q_UNUSED (parent)

    return createIndex(row, column);
}

void DeviceModel::addDevice(Device *add) noexcept
{
    Q_ASSERT(add);

    int row = 0;

    beginInsertRows(QModelIndex(), row, row);

    _devices.insert(row, add);

    endInsertRows();
}

void DeviceModel::removeDevice(int idx) noexcept
{

    beginRemoveRows(QModelIndex(), idx, idx);

    Device *remove = _devices[idx];
    _devices.remove(idx);
    remove->deleteLater();

    endRemoveRows();

}

void DeviceModel::removeAllDevices() noexcept{
    for (int i = _devices.size() - 1; i >= 0; --i) {
            removeDevice(i);
    }
}

void DeviceModel::removeNoMatchingDevice(QStringList macs) noexcept
{
    for (int i = _devices.size() - 1; i >= 0; --i) {
        if(!macs.contains(_devices[i]->mac())){
            removeDevice(i);
        }
    }
}

QModelIndex DeviceModel::lookup(const QString &mac) noexcept
{
    bool flag = false;
    int idx = -1;
    for (int i = 0; i < _devices.size() && flag == false; ++i) {
        if(_devices[i]->mac() == mac){
            idx = i;
            flag=true;
        }
    }
    if(flag){
        return index(idx);
    } else{
        return QModelIndex();
    }
}

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const noexcept
{
    if (index.isValid()){
        return (QAbstractItemModel::flags(index) | Qt::ItemIsEditable);
    }

    return QAbstractItemModel::flags(index);
}

int DeviceModel::rowCount(const QModelIndex &parent) const noexcept
{
    return parent.isValid() ? 0 : _devices.size();
}

