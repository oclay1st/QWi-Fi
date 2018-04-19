#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QProcess>
#include <QStringList>
class Worker : public QObject {
    Q_OBJECT

public:
    explicit Worker(QString command, QStringList arguments, QObject *parent = 0);

public slots:
    void process();
    void processOutput();
    void error();

signals:
    void processfinished();    
    void readyOutput(QString output);
    void readyErrorOutput(QString output);

private:
    QString _command;
    QStringList _arguments;
    QProcess* _proc;

};


#endif // WORKER_H
