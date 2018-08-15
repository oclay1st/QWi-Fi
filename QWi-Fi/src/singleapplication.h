#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H
#include <QObject>
#include <QSharedMemory>
#include <QSystemSemaphore>

class SingleApplication
{

public:
    SingleApplication( const QString& key );
    ~SingleApplication();

    bool isAnotherRunning();
    bool tryToRun();
    void release();

private:
    const QString key;
    const QString memLockKey;
    const QString sharedmemKey;

    QSharedMemory sharedMem;
    QSystemSemaphore memLock;

    Q_DISABLE_COPY( SingleApplication )
};

#endif // SINGLEAPPLICATION_H
