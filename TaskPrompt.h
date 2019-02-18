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
                         const QString szTitle = tr("Prompt"),
                         int nInterval = 5 * 60 * 1000,
                         int nPromptInterval = 1000,
                         QObject *parent = nullptr);
    CTaskPrompt(const CTaskPrompt &t);
    
protected:
    virtual int onStart();
    virtual int onRun();
        
protected Q_SLOTS:
    virtual void slotPrompt();
    
private:
    CFrmTop m_Top;
};

Q_DECLARE_METATYPE(CTaskPrompt)
#endif // __TASKPROMPT_H_KL__
