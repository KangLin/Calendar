#include "TaskLockScreen.h"
#include <QDebug>

#if defined(Q_OS_WIN)
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        return 1;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(
  _In_ int    nCode,
  _In_ WPARAM wParam,
  _In_ LPARAM lParam
        )
{
    if (nCode == HC_ACTION)
    {
        return 1;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
#endif

CTaskLockScreen::CTaskLockScreen(int nInterval, int nPromptInterval, QObject *parent)
    : CTask(nInterval, nPromptInterval, parent)
{
    Init();
}

int CTaskLockScreen::Init()
{
    SetName("Lock Screen");
    m_hKeyboardHook = NULL;
    m_hMouseHook = NULL;
    return 0;
}

int CTaskLockScreen::onStart()
{
    int nRet = 0;

    m_FullScreen.showFullScreen();
   
#if defined(Q_OS_WIN)
    if(NULL == m_hKeyboardHook)
        m_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
                                           (HOOKPROC)KeyboardHookProc,
                                           (HINSTANCE)GetModuleHandle(NULL),
                                           0);
    if(NULL == m_hMouseHook)
        m_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL,
                                      (HOOKPROC)LowLevelMouseProc,
                                      (HINSTANCE)GetModuleHandle(NULL),
                                      0);
#endif
    slotPrompt();
    return nRet;
}

int CTaskLockScreen::onRun()
{
    int nRet = 0;

#if defined(Q_OS_WIN)
    if(m_hKeyboardHook)
    {
        BOOL bFlag = UnhookWindowsHookEx(m_hKeyboardHook);
        if(bFlag) m_hKeyboardHook = NULL;
    }
    if(m_hMouseHook)
    {
        BOOL bFlag = UnhookWindowsHookEx(m_hMouseHook);
        if(bFlag) m_hMouseHook = NULL;
    }
#endif

    m_FullScreen.close();
    return nRet;
}

void CTaskLockScreen::slotPrompt()
{
    QTime tm(0, 0);
    tm = tm.addMSecs(Remaining());
    m_FullScreen.Prompt(tr("Remaining: %1")
                         .arg(tm.toString("HH:mm:ss")),
                        0, Remaining(), GetInterval(),
                        true);
}
