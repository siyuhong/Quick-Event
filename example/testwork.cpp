#include "testwork.h"

#include "quickapplication.h"
#include "quickevent.h"

#include <QEventLoop>
#include <QByteArray>
#include <QDateTime>
#include <QDebug>

#include <QJsonObject>

TestWork::TestWork(QuickWork *parent) : QuickWork(parent)
{
    QuickApplication::subscibeEvent(this, "denglu");
    QuickApplication::subscibeEvent(this, "dashao");

    QTimer::singleShot(2000, this, []() {
        auto time = QDateTime::currentDateTime();
        QuickApplication::publishEvent("show_time", Qt::AutoConnection, time);
    });
}

void TestWork::event_dashao(const QString &name, QString work)
{
    QuickApplication::publishEvent("linggongju", Qt::AutoConnection, name);
    qDebug() <<  name << ":" << work;
}

void TestWork::event_denglu(const Student &stu)
{
    qDebug() << stu.name_;
    qDebug() << stu.id_;

   QTimer timer;
   QEventLoop loop;
   connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
   timer.start(2000);
   loop.exec();

   qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

void TestWork::start()
{
    while(runFlag_)
    {
        qDebug() << "123123123123";

        QTimer timer;
        QEventLoop loop;

        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        connect(this, &QuickWork::quit, &loop, &QEventLoop::quit);

        timer.start(1000);
        loop.exec();
    }
}
