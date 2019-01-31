#ifndef TASKWORK_H
#define TASKWORK_H

#include "Task.h"

class CTaskWork : public CTask
{
    Q_OBJECT
public:
    explicit CTaskWork(int nInterval = 40 * 60 * 1000,
                       QObject *parent = nullptr);
protected:
    virtual int onRun();
};

#endif // TASKWORK_H
