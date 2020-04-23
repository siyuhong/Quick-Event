#ifndef TESTWORK_H
#define TESTWORK_H

#include "event/quick.h"
#include "event/quickwork.h"

#include <QSharedPointer>
#include <QVariant>
#include <QTimer>

class TestWork : public QuickWork
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TestWork(QObject *parent = nullptr);

    bool S_Request();
private slots:
    void event_denglu(QSharedPointer<QVariant> ptr);

    void start();
};
QUICK_AUTO(TestWork)


#endif // TESTWORK_H
