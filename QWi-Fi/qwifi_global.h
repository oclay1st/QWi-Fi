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


class Utils : public QObject {
public:
    static void initBD();
    static QString convert (quint64 bytes);
    static QSqlQuery* consultBD(const QString &connection, const QString &querySQL);
    static QString macDescription (const QString &mac);
};

QWIFI_NAMESPACE_END
#endif // GLOBAL_H
