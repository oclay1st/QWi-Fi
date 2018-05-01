#include <QApplication>
#include <QDir>
#include <QDebug>
#include "translation.h"

Translation::Translation(QObject *parent) : QObject(parent)
{
    translator = new QTranslator(this);
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
