#ifndef __TASKPROMPT_H_KL__
#define __TASKPROMPT_H_KL__

#pragma once

#include "Task.h"
#include "FrmTop.h"

class CTaskPrompt : public CTask
{
    Q_OBJECT
    Q_PROPERTY(QString Text READ GetText WRITE SetText)
    
public:
    explicit CTaskPrompt(QObject *parent = nullptr);
    explicit CTaskPrompt(const QString szText,
                         int nInterval = 5 * 60 * 1000,
                         int nPromptInterval = 60 * 1000,
                         QObject *parent = nullptr);

protected:
    virtual int onStart();
    virtual int onRun();
    virtual int SetText(QString szText);
    virtual QString GetText();
    
protected slots:
    virtual void slotPrompt();
    
private:
    CFrmTop m_Top;
    QString m_szText;
};

#endif // __TASKPROMPT_H_KL__
