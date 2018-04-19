#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QObject>
#include <QTranslator>

class Translation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ qmli18n NOTIFY languageChanged)
public:
    explicit Translation(QObject *parent = nullptr);
    QString qmli18n();
    Q_INVOKABLE void selectLanguage(QString language);

signals:
    void languageChanged();

private:
    QTranslator *translator;

};

#endif // TRANSLATION_H
