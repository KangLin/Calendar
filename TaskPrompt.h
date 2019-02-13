#ifndef __TASKPROMPT_H_KL__
#define __TASKPROMPT_H_KL__

#pragma once

#include "Task.h"
#include "FrmTop.h"

class CTaskPrompt : public CTask
{
    Q_OBJECT
    
public:
    explicit CTaskPrompt(QObject *parent = nullptr);
    explicit CTaskPrompt(const QString szText,
                         int nInterval = 5 * 60 * 1000,
                         int nPromptInterval = 1000,
                         QObject *parent = nullptr);

protected:
    virtual int onStart();
    virtual int onRun();
        
protected Q_SLOTS:
    virtual void slotPrompt();
    
private:
    CFrmTop m_Top;
};

#endif // __TASKPROMPT_H_KL__
