#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <QMap>
#include <QRegExp>

#define QWIFI_NAMESPACE_START namespace QWiFi{
#define QWIFI_NAMESPACE_END }

QWIFI_NAMESPACE_START


#define AP_ENABLED QRegExp("\\bAP-ENABLED\\b")
#define CLIENT_IN_REG_EXP QRegExp("\\bAP-STA-CONNECTED\\b")
#define CLIENT_OUT_REG_EXP QRegExp("\\bAP-STA-DISCONNECTED\\b")

class Utils : public QObject {
public:
    static void initBD();
    static QString convert (quint64 bytes);
    static QSqlQuery* consultBD(const QString &connection, const QString &querySQL);
    static QString macDescription (const QString &mac);
    static QStringList getWirelessInterfaces();
    static QStringList getAllInterfaces();
    static bool isWireless(const char* ifname, char* protocol);
};

QWIFI_NAMESPACE_END
#endif // GLOBAL_H
