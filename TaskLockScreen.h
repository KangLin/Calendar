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

protected:
    virtual int onStart();
    virtual int onRun();

protected slots:
    virtual void slotPrompt();
    
private:
    int Init();

#if defined(Q_OS_WIN)
    HHOOK m_hKeyboardHook;
    HHOOK m_hMouseHook;
#endif
    QSharedPointer<CFrmFullScreen> m_FullScreen;
};

#endif // TASKLOCKSCEEN_H
