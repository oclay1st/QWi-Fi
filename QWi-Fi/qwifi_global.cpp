#include "qwifi_global.h"

#include <QStringList>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QFile>

#include <unistd.h>
#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/wireless.h>

void QWiFi::Utils::initBD()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "MAC_ID");

    db.setDatabaseName("/home/oclay/macs.db");

    if (!db.open()){
        qDebug() << QObject::tr("Database Error") << db.lastError().text();
    }
}

QString QWiFi::Utils::convert(quint64 bytes)
{
    const QStringList sufix{
        QLatin1String("Bytes"),
                QLatin1String("KiB"),
                QLatin1String("MiB"),
                QLatin1String("GiB"),
                QLatin1String("TiB")
    };

    float work = bytes;
    int cont = 0;

    while (work > 1024 && cont < sufix.size()){
        work /= 1024;
        ++cont;
    }

    QString ret = QString::number(work);

    int index = ret.lastIndexOf(".");

    if (index != -1 && index < ret.size() - 2){
        ret = ret.left(index + 3);
    }


    return QString("%1 %2").arg(ret).arg(sufix[cont]);
}

QSqlQuery *QWiFi::Utils::consultBD(const QString &connection, const QString &querySQL)
{
    QSqlDatabase db = QSqlDatabase::database(connection);
    QSqlQuery* query = new QSqlQuery(db);

    if (query->exec(querySQL)) {
        return query;
    }else{
        qDebug() << query->lastError().text();
        delete query;
        return nullptr;
    }
}

QString QWiFi::Utils::macDescription(const QString &mac)
{
    QString sql = QString("SELECT description FROM mac WHERE mac LIKE \"%1\" LIMIT 1").arg(mac);
    qDebug() << "QUERY:" << sql;
    QSqlQuery *query = consultBD("MAC_ID", sql);

    if (query) {
        if (query->next()){
            return query->value(0).toString();
        }else{
            return QString("Unknown MAC identity");
        }
    }else{
        return QString("Unknown MAC ID");
    }
}



bool QWiFi::Utils::isWireless(const char* ifname, char* protocol) {
    int sock = -1;
    struct iwreq pwrq;
    memset(&pwrq, 0, sizeof(pwrq));
    strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return false;
    }

    if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1) {
        if (protocol) strncpy(protocol, pwrq.u.name, IFNAMSIZ);
        close(sock);
        return true;
    }

    close(sock);
    return false;
}

QStringList QWiFi::Utils::getWirelessInterfaces(){
    QStringList interfaces;
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
    }
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        char protocol[IFNAMSIZ]  = {0};
        if (ifa->ifa_addr == NULL ||
                ifa->ifa_addr->sa_family != AF_PACKET ||
                !!(ifa->ifa_flags & IFF_LOOPBACK)) continue;

        if (isWireless(ifa->ifa_name, protocol)) {
            interfaces << ifa->ifa_name;
        }
    }
    freeifaddrs(ifaddr);
    return interfaces;
}


QStringList QWiFi::Utils::getAllInterfaces(){
    QStringList interfaces;
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
    }
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL ||
                ifa->ifa_addr->sa_family != AF_PACKET ||
                !!(ifa->ifa_flags & IFF_LOOPBACK)) continue;

        interfaces << ifa->ifa_name;
    }

    freeifaddrs(ifaddr);
    return interfaces;

}






