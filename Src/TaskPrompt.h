// 作者：康林 <kl222@126.com>

#ifndef TASKPROMPT_H_KL
#define TASKPROMPT_H_KL

#pragma once

#include "Task.h"
#include "FrmTop.h"

class CTaskPrompt : public CTask
{
    Q_OBJECT
    
public:
    explicit CTaskPrompt(QObject *parent = nullptr);
    explicit CTaskPrompt(const QString szContent,
                         const QString szTitle = tr("Prompt"),
                         int nInterval = 5 * 60 * 1000,
                         int nPromptInterval = 1000,
                         QObject *parent = nullptr);
    CTaskPrompt(const CTaskPrompt &t);
    virtual QString GetDescription() const override;
    
protected:
    virtual int onStart() override;
    virtual int onRun() override;

Q_SIGNALS:
    void sigShow();
    void sigClose();
    void sigUpdate();
    
protected Q_SLOTS:
    virtual void slotPrompt() override;
    virtual void slotShow();
    virtual void slotClose();
    virtual void slotUpdate();
    
private:
    void Init();
    
protected:
    CFrmTop m_Top;
};

Q_DECLARE_METATYPE(CTaskPrompt)
#endif // TASKPROMPT_H_KL
