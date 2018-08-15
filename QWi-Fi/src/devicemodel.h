/***This code comes from QHotSpotQML(by H3R3TIC), but it has some changes**/

#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>

#include <src/device.h>

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DeviceRoles {
        NameRole = Qt::UserRole + 1,
        MacRole,
        IpRole,
        BytesReadedRole,
        BytesWritedRole,
        DownloadRateRole,
        UploadRateRole,
        ManufacturerRole,
        ConnectionTimeRole
    };

    explicit DeviceModel(QObject *parent = 0);


    QHash<int, QByteArray> roleNames() const noexcept override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const noexcept override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) noexcept override;

    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const noexcept;

    void addDevice (Device *dev) noexcept;
    void removeDevice (int idx) noexcept;
    void removeAllDevices () noexcept;
    void removeNoMatchingDevice(QStringList macs) noexcept;

    QModelIndex lookup(const QString &mac) noexcept;

    Qt::ItemFlags flags(const QModelIndex &index) const noexcept override;

    int rowCount(const QModelIndex &parent=QModelIndex()) const noexcept override;

signals:

public slots:

private:
    QVector<Device *> _devices;
};


#endif // DEVICEMODEL_H
