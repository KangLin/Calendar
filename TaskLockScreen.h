#ifndef TASKLOCKSCEEN_H
#define TASKLOCKSCEEN_H

#pragma once

#include "Task.h"
#include "FrmFullScreen.h"

#include <QTimer>

#if defined(Q_OS_WIN)
    #include <Windows.h>
#endif

class CTaskLockScreen : public CTask
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
                             int nPromptInterval = 60 * 1000,
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
    CFrmFullScreen m_FullScreen;
};

#endif // TASKLOCKSCEEN_H
