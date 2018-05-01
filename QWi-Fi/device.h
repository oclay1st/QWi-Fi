/***This code comes from QHotSpotQML(by H3R3TIC), but it has some changes**/

#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QTimer>


class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString mac READ mac WRITE setMac NOTIFY macChanged)
    Q_PROPERTY(QString manufacturer READ manufacturer WRITE setManufacturer NOTIFY manufacturerChanged)
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(quint64 bytesReaded READ bytesReaded WRITE setBytesReaded NOTIFY bytesReadedChanged)
    Q_PROPERTY(quint64 bytesWrited READ bytesWrited WRITE setBytesWrited NOTIFY bytesWritedChanged)
    Q_PROPERTY(float downloadRate READ downloadRate WRITE setDownloadRate NOTIFY downloadRateChanged)
    Q_PROPERTY(float uploadRate READ uploadRate WRITE setUploadRate NOTIFY uploadRateChanged)
    Q_PROPERTY(int connCount READ connCount WRITE setConnCount NOTIFY connCountChanged)
    Q_PROPERTY(int connTime READ connTime WRITE setConnTime NOTIFY connTimeChanged)
public:
    explicit Device(QObject *parent = 0);

    QString name() const noexcept;
    QString mac() const noexcept;
    QString manufacturer() const noexcept;
    QString ip() const noexcept;
    quint64 bytesReaded() const noexcept;
    quint64 bytesWrited() const noexcept;
    float downloadRate() const noexcept;
    float uploadRate() const noexcept;
    int connCount () const noexcept;
    int connTime () const noexcept;

    void setName (const QString &name) noexcept;
    void setMac (const QString &mac) noexcept;
    void setIp (const QString &ip) noexcept;
    void setBytesReaded (const quint64 bytesReaded) noexcept;
    void setBytesWrited (const quint64 bytesWrited) noexcept;
    void setDownloadRate (const quint64 downloadRate) noexcept;
    void setUploadRate (const quint64 uploadRate) noexcept;
    void setManufacturer (const QString &manufacturer) noexcept;
    void setConnCount (const int connCount) noexcept;
    void setConnTime (const int connTime) noexcept;


signals:
    void nameChanged(const QString &name);
    void macChanged(const QString &mac);
    void ipChanged(const QString &ip);
    void bytesReadedChanged(const quint64 bytesReaded);
    void bytesWritedChanged(const quint64 bytesWrited);
    void downloadRateChanged(const quint64 downloadRate);
    void uploadRateChanged(const quint64 uploadRate);
    void manufacturerChanged(const QString &manufacturer);
    void connCountChanged (const int connCount);
    void connTimeChanged (const int connTime);

private:
    QString _name;
    QString _mac;
    QString _ip;
    quint64 _bytesReaded;
    quint64 _bytesWrited;
    float _downloadRate;
    float _uploadRate;
    QString _manufacturer;
    int _connCount;
    int _connTime;
};



#endif // DEVICE_H
