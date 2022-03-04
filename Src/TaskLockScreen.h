// 作者：康林 <kl222@126.com>

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
    explicit CTaskLockScreen(QObject* parent);
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

protected Q_SLOTS:
    virtual void slotShow() override;
    virtual void slotClose() override;
    virtual void slotUpdate() override;
        
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
