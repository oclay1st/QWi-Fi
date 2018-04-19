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







