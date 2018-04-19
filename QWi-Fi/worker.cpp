#include "worker.h"
#include <QDebug>
#include <QByteArray>

Worker::Worker(QString command, QStringList arguments, QObject *parent) : QObject(parent)
{
    _proc = new QProcess(this);
    _command = command;
    _arguments = arguments;
}

void Worker::process() {
    connect(_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    connect(_proc, SIGNAL(readyReadStandardError()), this, SLOT(error()));
    connect(_proc, SIGNAL(finished(int , QProcess::ExitStatus )), this, SIGNAL(processfinished()));
    _proc->start(_command,_arguments);
    if (!_proc->waitForStarted())
        qDebug() << "Error excecuting the command: " << _command;
}

void Worker::processOutput(){
    while(_proc->canReadLine()){
        QString output = _proc->readLine();
        emit readyOutput(output);
    }
}

void Worker::error(){
    QByteArray  error = _proc->readAllStandardError();
    emit readyErrorOutput(error);
}

