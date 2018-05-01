#include "worker.h"
#include <QDebug>
#include <QByteArray>

Worker::Worker(QString command, QStringList arguments, bool readAtFinished, QObject *parent) : QObject(parent)
{    
    _command = command;
    _arguments = arguments;
    _proc = new QProcess(this);

    if(readAtFinished){
        connect(_proc, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(processAllOutput()));
    }else{
        connect(_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(processOutput()));
    }
    connect(_proc, SIGNAL(readyReadStandardError()), this, SLOT(error()));
    connect(_proc, SIGNAL(finished(int , QProcess::ExitStatus )), this, SIGNAL(processfinished()));
}

void Worker::process() {
    _proc->setProgram(_command);
    _proc->setArguments(_arguments);
    _proc->start();
    if (!_proc->waitForStarted())
        qDebug() << "Error excecuting the command: " << _command;
}

void Worker::processOutput(){
    QString output;
    while(_proc->canReadLine()){
        output = _proc->readLine();
        emit readyOutput(output);
    }
}

void Worker::processAllOutput(){
    QString output = _proc->readAllStandardOutput();
    emit readyAllOutput(output);
}

void Worker::error(){
    QByteArray  error = _proc->readAllStandardError();
    emit readyErrorOutput(error);
}

