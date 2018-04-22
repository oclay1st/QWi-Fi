#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>
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
    if(!translator->load(
                QLocale(language),
                QString("qwifi"),
                QString("_"),
                QString(":/resources/translations")
                )
            )
    {
        qDebug() << "Failed to load translation";
    }
    qApp->installTranslator(translator);

    emit languageChanged();}
