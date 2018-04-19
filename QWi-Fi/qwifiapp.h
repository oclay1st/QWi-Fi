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
    void start(QString wifiIface, QString inthernetIface, QString ssid, QString password);
    void stop();
    void proccessReadyOutput(QString output);
    void proccessReadyErrorOutput(QString output);


signals:
    void started();
    void stopped();
    void newMessage(const QString &msg);

private:
    QString _activeInterface;


};

#endif // QWIFIAPP_H
