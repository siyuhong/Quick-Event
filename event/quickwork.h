#ifndef QUICKWORK_H
#define QUICKWORK_H

#include <QObject>
#include <QEvent>

#include "quick.h"
#include <QSet>
#include <QString>
#include <QDebug>


class QuickWork : public QObject
{
    Q_OBJECT
    QUICK_EVENT(QObject)
public:

    typedef enum {
        MainThread = 0,
        WorkThread,
        NewThread
    } MoveThreadType;

    explicit QuickWork(QObject *parent = nullptr);
    virtual ~QuickWork();
    void moveToThread(QThread *thread);

    bool eventWait(int msec);

    void setRunFlag(int value);
    MoveThreadType getMoveType() const;

signals:
    void quit();

public slots:
    virtual void start(){};
protected:
    int runFlag_;
    //对象移动方式
    MoveThreadType moveType_;
};

#endif // QUICKWORK_H
