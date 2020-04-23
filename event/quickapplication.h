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

#include "quickevent.h"

class QuickWork;

class QuickApplication : public QApplication
{
    Q_OBJECT
public:
    QuickApplication(int &argc, char **argv);

    virtual ~QuickApplication();

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
