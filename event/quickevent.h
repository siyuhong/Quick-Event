#ifndef QUICKEVENT_H
#define QUICKEVENT_H

#include <QEvent>
#include <QObject>
#include <QVariant>
#include <QMetaMethod>
#include <QSharedPointer>

extern const char *MethodHead;

extern QEvent::Type S_QuickEvent;

class QuickEvent : public QEvent
{
public:
    QuickEvent(Type type = S_QuickEvent);

    QuickEvent(QByteArray eventName, QVariant& info, Type type = S_QuickEvent);

    virtual ~QuickEvent();

    QuickEvent &operator=(const QuickEvent &other);

    QSharedPointer<QVariant> info() const;

    void setInfo(QVariant *info);

    QByteArray eventName() const;

    void setEventName(const QByteArray &eventName);

private:
    QByteArray           eventName_;
    QSharedPointer<QVariant> info_;
};

#endif // QUICKEVENT_H
