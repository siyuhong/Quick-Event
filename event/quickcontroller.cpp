#include "quickcontroller.h"

#include "quickwork.h"

QMap<QThread*, QuickWork*> QuickController::threads_;
QPair<QThread*, QSet<QuickWork*> > QuickController::workthread_;
QSet<QuickWork*> QuickController::works_;

QuickController::QuickController(QObject *parent) : QObject(parent)
{
    auto list = static_cast< QSet<QByteArray> *>(NewInstance(nullptr));

    auto workt = new QThread();

    workthread_.first = nullptr;

    QSet<QuickWork*> set;

    foreach(auto var, *list)
    {
        auto type = QMetaType::type(var + "*");
        auto meta = QMetaType::metaObjectForType(type);
        auto obj = meta->newInstance(Q_ARG(QObject*, nullptr));
        auto work = qobject_cast<QuickWork*>(obj);
        auto t = new QThread();

        switch (work->getMoveType()) {
        case QuickWork::NewThread:
            work->moveToThread(t);
            threads_.insert(t, work);
            t->start();
            break;
        case QuickWork::WorkThread:
            set.insert(work);
            work->moveToThread(workt);
            break;
        case QuickWork::MainThread:
            connect(this, &QuickController::startwork, work, &QuickWork::start);
            works_.insert(work);
            break;
        }
    }

    if(!set.isEmpty())
    {
        workthread_.first = workt;
        workthread_.second = set;
        workt->start();
    } else
    {
        delete workt;
    }

    if(!works_.isEmpty())
        emit startwork();
}

QuickController::~QuickController()
{
    auto it = threads_.begin();

    for(; it != threads_.end(); ++ it)
    {
        it.key()->deleteLater();
    }

    if(workthread_.first != nullptr)
         workthread_.first ->deleteLater();
}

void *QuickController::NewInstance(const char *name)
{
    static QSet<QByteArray> list;

    if(name != nullptr)
        list.insert(name);

    return (void *)&list;
}

void QuickController::destory()
{
    auto it = threads_.begin();

    for(; it != threads_.end(); ++ it)
    {
        it.value()->setRunFlag(false);
        delete it.value();
    }

    foreach(auto var, workthread_.second)
    {
        var->setRunFlag(false);
        delete var;
    }

    foreach(auto var, works_)
    {
        var->setRunFlag(false);
        delete var;
    }
}
