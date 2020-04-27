#include "testwork.h"

#include "event/quickapplication.h"
#include "event/quickevent.h"

#include <QEventLoop>
#include <QByteArray>
#include <QDateTime>
#include <QDebug>

#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

TestWork::TestWork(QObject *parent) : QuickWork(parent)
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

bool TestWork::S_Request()
{
    QString error;

    QNetworkAccessManager m_networkManger;

    if(QNetworkAccessManager::Accessible != m_networkManger.networkAccessible())
    {
        m_networkManger.setNetworkAccessible(QNetworkAccessManager::Accessible);
    }

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl("http://127.0.0.1:4127"));
    networkRequest.setRawHeader("Content-Type","json");

    QByteArray sendArray = "{\"reqtype\":0}";
    QEventLoop eventLoop;
    QNetworkReply *reply = m_networkManger.post(networkRequest , sendArray);
    connect(&m_networkManger, SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)), &eventLoop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

   if(reply->error() != QNetworkReply::NoError)
   {
       error = reply->errorString();
       return false;
   }

   QByteArray recvArray = reply->readAll();
   if(recvArray.size() == 0)
   {
       error = "nothing recved";
       return false;
   }
   qDebug() << "S_Request"<<recvArray;
   reply->deleteLater();

   return true;
}

void TestWork::start()
{
    while(runFlag_)
    {
        qDebug() << "123123123123";

        S_Request();

        QTimer timer;
        QEventLoop loop;

        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        connect(this, &QuickWork::quit, &loop, &QEventLoop::quit);

        timer.start(1000);
        loop.exec();
    }
}
