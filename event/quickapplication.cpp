#include "quickapplication.h"
#include "quickevent.h"
#include "quickwork.h"
#include "quickcontroller.h"

#include <QObject>
#include <QTimer>
#include <QEventLoop>

QMap< QByteArray, QSet<QObject *> > QuickApplication::s_quick_event_pool;
QReadWriteLock QuickApplication::s_lock;


QuickApplication::QuickApplication(int &argc, char **argv):QApplication(argc, argv)
{
}

QuickApplication::~QuickApplication()
{
}

bool QuickApplication::doSendEvent(QObject *receiver, QEvent *event)
{
    if(event == nullptr)
        return false;

    int type = event->type();

    if(type == S_QuickEvent)
    {
        auto quickEvent = dynamic_cast<QuickEvent*>(event);
        auto name = quickEvent->eventName();

        QReadLocker loker(&s_lock);

        if(s_quick_event_pool.contains(name))
        {
             auto set = s_quick_event_pool[name];
             foreach (auto var, set) {
                     return QApplication::sendEvent(var, quickEvent);
             }
        }
    }

    return QApplication::sendEvent(receiver, event);
}

void QuickApplication::doPostEvent(QObject *receiver, QEvent *event, int priority)
{
    if(event == nullptr)
        return ;

    int type = event->type();

    if(type == S_QuickEvent)
    {
        auto quickEvent = dynamic_cast<QuickEvent*>(event);
        auto name = quickEvent->eventName();

        QReadLocker loker(&s_lock);

        if(s_quick_event_pool.contains(name))
        {
             auto set = s_quick_event_pool[name];
             foreach (auto var, set) {
                     QuickEvent *newevent = new QuickEvent();
                     *newevent = *quickEvent;
                     QApplication::postEvent(var, newevent, priority);
             }
        }
        delete quickEvent;
        return;
    }

    QApplication::postEvent(receiver, event, priority);
}

bool QuickApplication::subscibeEvent(QObject *listener, QByteArray eventName)
{

    QWriteLocker loker(&s_lock);

    if(s_quick_event_pool.contains(eventName))
    {
        QSet<QObject *> tmpset = s_quick_event_pool[eventName];

        tmpset.insert(listener);

        s_quick_event_pool.insert(eventName, tmpset);

        return true;
    }

    QSet<QObject *> tmpset;
    tmpset.insert(listener);
    s_quick_event_pool.insert(eventName, tmpset);

    return true;
}

void QuickApplication::logoutEvent(QObject *listener, QByteArray eventName)
{
    QWriteLocker loker(&s_lock);

    if(s_quick_event_pool.contains(eventName))
    {
        QSet<QObject *> tmpset = s_quick_event_pool[eventName];

        tmpset.remove(listener);

        s_quick_event_pool.insert(eventName, tmpset);
    }

}

void QuickApplication::exit(int rlt)
{
    QuickController::destory();
    qApp->exit(rlt);
}
