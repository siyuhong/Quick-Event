#include "orderwork.h"

#include <QTimer>
#include <QEventLoop>

OrderWork::OrderWork(QuickWork *parent) : QuickWork(parent)
{
    moveType_ = NewThread;
}

void OrderWork::start()
{
    while(runFlag_)
    {
        qDebug() << "OrderWork::start";

        QTimer timer;
        QEventLoop loop;

        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        connect(this, &QuickWork::quit, &loop, &QEventLoop::quit);

        timer.start(1000);
        loop.exec();
    }
}
