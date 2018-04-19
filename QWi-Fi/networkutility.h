#ifndef NETWORKUTILITY_H
#define NETWORKUTILITY_H

#include <QObject>

class NetworkUtility : public QObject
{
    Q_OBJECT
public:
    explicit NetworkUtility(QObject *parent = nullptr);
    bool isWireless(const char* ifname, char* protocol);

signals:

public slots:
    QStringList getAllInterfaces();
    QStringList getWirelessInterfaces();
};

#endif // NETWORKUTILITY_H
