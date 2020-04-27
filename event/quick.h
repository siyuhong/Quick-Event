#ifndef QUICK_H
#define QUICK_H

#include "quickcontroller.h"
#include "quickapplication.h"

#define QUICK_AUTO(ClassName)                                                            \
    static int ClassId = qRegisterMetaType<ClassName *>();                               \
    static void *ThisPtr = QuickController::NewInstance(#ClassName);

#define QUICK_EVENT(PARENTANME)                                                                 \
public:                                                                                         \
    bool event(QEvent *e) override                                                              \
    {                                                                                           \
        if(e->type() == S_QuickEvent)                                                           \
        {                                                                                       \
            auto quickEvent = dynamic_cast<QuickEvent*>(e);                                     \
            auto methodName = quickEvent->eventName();                                          \
            auto infos = quickEvent->info();                                                    \
            QList<QGenericArgument> list;                                                       \
            methodName = QByteArray(MethodHead) + methodName;                                   \
            for(int i = 0; i < quickEvent->info().size() && i < 10; ++ i)                       \
                list << QGenericArgument(infos[i]->typeName(), infos[i]->constData());          \
            while(list.size() <= 10)                                                            \
                list << QGenericArgument();                                                     \
            QMetaObject::invokeMethod(this, methodName, list[0], list[1], list[2], list[3],     \
                                    list[4], list[5], list[6], list[7], list[8], list[9]);      \
            return true;                                                                        \
        }                                                                                       \
        return PARENTANME##::event(e);                                                          \
    }


//#define QUICK_EVENT(PARENTANME)                                                         \
//public:                                                                                 \
//    bool event(QEvent *e) override                                                      \
//    {                                                                                   \
//        if(e->type() == S_QuickEvent)                                                   \
//        {                                                                               \
//            auto metaObj = this->metaObject();                                          \
//            auto quickEvent = dynamic_cast<QuickEvent*>(e);                             \
//            QByteArray eventName = quickEvent->eventName();                             \
//            eventName = QByteArray(MethodHead) + eventName + "(";                       \
//            for(int index= 0; index < metaObj->methodCount(); ++ index)                 \
//            {                                                                           \
//                auto method = metaObj->method(index);                                   \
//                if(method.methodSignature().contains(eventName))                        \
//                {                                                                       \
//                    method.invoke(this,                                                 \
//                                  Qt::AutoConnection,                                   \
//                                  Q_ARG(QSharedPointer<QVariant>, quickEvent->info())); \
//                }                                                                       \
//            }                                                                           \
//            return true;                                                                \
//        }                                                                               \
//        return PARENTANME##::event(e);                                                  \
//    }


#endif // QUICK_H
