#include "quickwork.h"
#include "quickevent.h"

#include <QEvent>
#include <QThread>
#include <QMetaMethod>
#include <QSharedPointer>

#include <QTimer>
#include <QEventLoop>

QuickWork::QuickWork(QObject *parent) : QObject(parent)
{
    runFlag_ = true;
    moveType_ =  WorkThread;
}

QuickWork::~QuickWork()
{
    runFlag_ = false;
    emit quit();
}

void QuickWork::moveToThread(QThread *thread)
{
    QObject::moveToThread(thread);
    connect(thread, &QThread::started, this, &QuickWork::start);
}

void QuickWork::setRunFlag(int value)
{
    runFlag_ = value;
}

QuickWork::MoveThreadType QuickWork::getMoveType() const
{
    return moveType_;
}

