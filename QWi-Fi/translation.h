#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <QObject>
#include <QTranslator>

class Translation : public QObject
{
    Q_OBJECT
public:
    explicit Translation(QObject *parent = nullptr);
    Q_INVOKABLE void selectLanguage(QString language);

signals:
    void languageChanged();

private:
    QTranslator *translator;

};

#endif // TRANSLATION_H
