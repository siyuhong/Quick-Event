#ifndef QUICK_H
#define QUICK_H

#include "quickcontroller.h"
#include "quickapplication.h"

#define QUICK_AUTO(ClassName)                                                            \
    static int ClassId = qRegisterMetaType<ClassName *>();                               \
    static void *ThisPtr = QuickController::NewInstance(#ClassName);

#define QUICK_EVENT(PARENTANME)                                                         \
public:                                                                                 \
    bool event(QEvent *e) override                                                      \
    {                                                                                   \
        if(e->type() == S_QuickEvent)                                                   \
        {                                                                               \
            auto metaObj = this->metaObject();                                          \
            auto quickEvent = dynamic_cast<QuickEvent*>(e);                             \
            QByteArray eventName = quickEvent->eventName();                             \
            eventName = QByteArray(MethodHead) + eventName + "(";                       \
            for(int index= 0; index < metaObj->methodCount(); ++ index)                 \
            {                                                                           \
                auto method = metaObj->method(index);                                   \
                if(method.methodSignature().contains(eventName))                        \
                {                                                                       \
                    method.invoke(this,                                                 \
                                  Qt::AutoConnection,                                   \
                                  Q_ARG(QSharedPointer<QVariant>, quickEvent->info())); \
                }                                                                       \
            }                                                                           \
            return true;                                                                \
        }                                                                               \
        return PARENTANME##::event(e);                                                  \
    }

#endif // QUICK_H
