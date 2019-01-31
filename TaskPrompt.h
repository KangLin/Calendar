#ifndef TASKPROMPT_H
#define TASKPROMPT_H

#include "Task.h"

class CTaskPrompt : public CTask
{
    Q_OBJECT
public:
    CTaskPrompt(QObject *parent = nullptr);

public slots:
    virtual int slotStart();
    
protected:
    virtual int onRun();
};

#endif // TASKPROMPT_H
