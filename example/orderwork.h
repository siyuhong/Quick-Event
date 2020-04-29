#ifndef ORDERWORK_H
#define ORDERWORK_H

#include "event/quickwork.h"
#include <QObject>

class OrderWork : public QuickWork
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit OrderWork(QuickWork *parent = 0);

signals:

public slots:
    void start();
};
QUICK_AUTO(OrderWork)
#endif // ORDERWORK_H
