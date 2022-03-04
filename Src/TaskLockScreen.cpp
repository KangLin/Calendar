// 作者：康林 <kl222@126.com>

#include "TaskLockScreen.h"
#include <QDebug>
#include <QCoreApplication>
#include "Global/TasksTools.h"

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

static int gTypeIdCTaskLockScreen = qRegisterMetaType<CTaskLockScreen>();

CTaskLockScreen::CTaskLockScreen(QObject* parent) : CTaskPrompt(parent)
{
    Init();
    SetTitle(tr("Reset"));
    SetInterval(15 * 60 * 1000);            
}

CTaskLockScreen::CTaskLockScreen(int nInterval,
                                 int nPromptInterval,
                                 QObject *parent)
    : CTaskPrompt(tr("Lock screen and reset"),
                  tr("Reset"), nInterval, nPromptInterval, parent)
{
    Init();
}

CTaskLockScreen::CTaskLockScreen(const CTaskLockScreen &t)
{
    Q_UNUSED(t);
}

int CTaskLockScreen::Init()
{
    setObjectName("TaskLockScreen");
#if defined(Q_OS_WIN)
    m_hKeyboardHook = NULL;
    m_hMouseHook = NULL;
#endif
    return 0;
}

QString CTaskLockScreen::GetDescription() const
{
    return tr("Lock screen");
}

void CTaskLockScreen::slotShow()
{
    if(nullptr == m_FullScreen.data())
    {
        m_FullScreen = QSharedPointer<CFrmFullScreen>(new CFrmFullScreen());
    }
    if(m_FullScreen)
        m_FullScreen->showFullScreen();
   
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
    slotUpdate();
}

void CTaskLockScreen::slotClose()
{
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
#elif defined(Q_OS_LINUX)
    //TODO: linux
    //https://www.x.org/releases/X11R7.7/doc/libX11/XKB/xkblib.html#Core_X_Protocol_Support_for_Keyboards
#endif

    //如果是屏保，则结束
    CTasksTools::ScreenPower(false);
    
    if(m_FullScreen)
    {
        m_FullScreen->close();
        m_FullScreen.clear();
    }
}

void CTaskLockScreen::slotUpdate()
{
    QTime tm(0, 0);
    tm = tm.addMSecs(Remaining());
    if(m_FullScreen)
        m_FullScreen->Prompt(GetContent() + "\n" + tr("Remaining: %1")
                         .arg(tm.toString("HH:mm:ss")),
                        Remaining(),
                        0,
                        GetInterval(),
                        true
                        );
}
