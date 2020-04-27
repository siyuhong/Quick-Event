#ifndef TESTWORK_H
#define TESTWORK_H

#include "event/quick.h"
#include "event/quickwork.h"

#include <QSharedPointer>
#include <QVariant>
#include <QTimer>

#include "student.h"

class TestWork : public QuickWork
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TestWork(QObject *parent = nullptr);

    bool S_Request();
public slots:
    void event_dashao(const QString &name, QString work);
    void event_denglu(const Student &stu);

    void start();
};
QUICK_AUTO(TestWork)


#endif // TESTWORK_H
