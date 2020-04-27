#ifndef QUICKAPPLICATION_H
#define QUICKAPPLICATION_H

#include <QApplication>
#include <QObject>
#include <QSet>
#include <QMap>
#include <QReadWriteLock>
#include <QByteArray>
#include <QVariant>
#include <QSharedPointer>
#include <QThread>
#include <QGenericArgument>
#include <QtCore>

#include "quickevent.h"

class QuickWork;

enum PublishType {
    AutoPublish,
    DirectPublish,
    QueuedPublish,
    BlockingQueuedPublish,
    UniquePublish = 0x80
};

class QuickApplication : public QApplication
{
    Q_OBJECT
public:
    QuickApplication(int &argc, char **argv);

    virtual ~QuickApplication();

    template<class T>
    static void getAddress(QList<QGenericArgument> &list, T&& t)
    {
        list << Q_ARG(decltype(t), t);
    }

    template<class ...Args>
    static void publishEvent(QByteArray eventName, PublishType type, Args&&... args)
    {
        if(eventName.isEmpty())
            return ;

        auot argsNum = sizeof...(args);
        Q_ASSERT_X(argsNum <= 10, "QuickEvent", "publishEvent argv number not greater than 10");


        QList<QGenericArgument> list;
        int[] arr = {(getAddress(list, args),0)...};
        auto len = list.size();

        while(len < 10) list << QGenericArgument();

        QReadLocker loker(&s_lock);

        if(s_quick_event_pool.contains(name))
        {
            auto set = s_quick_event_pool[name];

            foreach (auto var, set) {
                auto methodIndex = 2;
                var->metaObject()->method(methodIndex).invoke(var, type, list[0], list[1], list[2], list[3],
                                                             list[4],list[5], list[6], list[7], list[8], list[9]);
            }
        }


    }

    static void doPostEvent(QObject *receiver, QEvent *event, int priority = Qt::NormalEventPriority);

    template <typename T>
    static void postEvent(QObject *receiver, T &info, QByteArray eventName, int priority = Qt::NormalEventPriority)
    {
        auto var = new QVariant();
        var->setValue(info);

        QuickEvent *event = new QuickEvent();
        event->setInfo(var);
        event->setEventName(eventName);

        doPostEvent(receiver, event, priority);
    }

    template <typename T>
    static bool sendEvent(QObject *receiver, T &info, QByteArray eventName)
    {
        auto var = new QVariant();
        var->setValue(info);

        QuickEvent *event = new QuickEvent();
        event->setInfo(var);
        event->setEventName(eventName);

        auto flag = doSendEvent(receiver, event);

        delete var;

        return flag;
    }

    static bool doSendEvent(QObject *receiver, QEvent *event);

    static bool subscibeEvent(QObject *listener, QByteArray eventName);

    static void logoutEvent(QObject *listener, QByteArray eventName);

    static void exit(int rlt = 0);

private:
    static QMap< QByteArray, QSet<QObject *> > s_quick_event_pool;

    static QReadWriteLock s_lock;
};

#endif // QUICKAPPLICATION_H
