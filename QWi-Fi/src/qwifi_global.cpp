#include "qwifi_global.h"

#include <QStringList>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStandardPaths>
#include <QFile>

void QWiFi::Utils::initBD()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "MAC_ID");

    db.setDatabaseName("/home/oclay/macs.db");

    if (!db.open()){
        qDebug() << "Database Error" << db.lastError().text();
    }
}

QString QWiFi::Utils::sizeFormat(quint64 size)
{
    qreal calc = size;
    QStringList list;
    list << "KiB" << "MiB" << "GiB" << "TiB";

    QStringListIterator i(list);
    QString unit("Bytes");

    while(calc >= 1024 && i.hasNext())
    {
        unit = i.next();
        calc /= 1024;
    }

    return QString().setNum(calc, 'f', 0) + " " + unit;
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







