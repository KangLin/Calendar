#ifndef TASKLOCKSCEEN_H
#define TASKLOCKSCEEN_H

#pragma once

#include "TaskPrompt.h"
#include "FrmFullScreen.h"

#include <QTimer>
#include <QSharedPointer>

#if defined(Q_OS_WIN)
    #include <Windows.h>
#endif

class CTaskLockScreen : public CTaskPrompt
{
    Q_OBJECT
public:
    /**
     * @brief CTaskLockScreen
     * @param nInterval: unlocak. in milliseconds
     * @param nPromptInterval
     * @param parent
     */
    explicit CTaskLockScreen(int nInterval = 15 * 60 * 1000,
                             int nPromptInterval = 1000,
                             QObject *parent = nullptr);
    CTaskLockScreen(const CTaskLockScreen &t);
    virtual QString GetDescription() const override;
    
protected:
    virtual int onStart() override;
    virtual int onRun() override;

protected Q_SLOTS:
    virtual void slotPrompt() override;
    
private:
    int Init();

#if defined(Q_OS_WIN)
    HHOOK m_hKeyboardHook;
    HHOOK m_hMouseHook;
#endif
    QSharedPointer<CFrmFullScreen> m_FullScreen;
};

Q_DECLARE_METATYPE(CTaskLockScreen)

#endif // TASKLOCKSCEEN_H
