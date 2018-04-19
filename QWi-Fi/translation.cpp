#include <QApplication>
#include <QDir>
#include <QDebug>

#include "translation.h"

Translation::Translation(QObject *parent) : QObject(parent)
{
    translator = new QTranslator(this);
}

QString Translation::qmli18n(){
    //    dirty trick to fix a QmlEngine bug with dynamic language switching in QML
    return QString();
}

void Translation::selectLanguage(QString language){
    QDir dir = QDir(qApp->applicationDirPath()).absolutePath();
    if(!translator->load(
                QString("qwifi_%1").arg(language),
                QString("%1/translations").arg(dir.path())
                )
            )
    {
        qDebug() << "Failed to load translation";
    }
    qApp->installTranslator(translator);
    emit languageChanged();
}
