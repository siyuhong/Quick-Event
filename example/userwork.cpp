#include "userwork.h"
#include "event/quickapplication.h"

#include <QDebug>
#include <QString>

UserWork::UserWork(QObject *parent) : QuickWork(parent)
{
    QuickApplication::subscibeEvent(this, "dashao");
}

void UserWork::event_dashao(QSharedPointer<QVariant> ptr)
{
    qDebug() <<  ptr->value<QString>();
}
