#ifndef USERWORK_H
#define USERWORK_H

#include "event/quick.h"
#include "event/quickwork.h"
#include <QVariant>
#include <QSharedPointer>


class UserWork : public QuickWork
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit UserWork(QObject *parent = nullptr);
public slots:
    void event_dashao(QSharedPointer<QVariant> ptr);
};
QUICK_AUTO(UserWork)

#endif // USERWORK_H
