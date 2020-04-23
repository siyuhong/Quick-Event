#include "quickevent.h"

const char *MethodHead = "event_";

QEvent::Type S_QuickEvent = static_cast<QEvent::Type>(QEvent::registerEventType());


QuickEvent::QuickEvent(Type type):QEvent(type)
{
}

QuickEvent::QuickEvent(QByteArray eventName, QVariant &info, QEvent::Type type)
    :QEvent(type), eventName_(eventName), info_(&info)
{

}

QuickEvent::~QuickEvent()
{

}

QuickEvent &QuickEvent::operator=(const QuickEvent &other)
{
    eventName_ = other.eventName_;
    this->info_ = other.info_;
    return *this;
}

QSharedPointer<QVariant> QuickEvent::info() const
{
    return info_;
}

void QuickEvent::setInfo(QVariant *info)
{
    info_.reset(info);
}

QByteArray QuickEvent::eventName() const
{
    return eventName_;
}

void QuickEvent::setEventName(const QByteArray &eventName)
{
    eventName_ = eventName;
}
