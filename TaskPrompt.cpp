#include "TaskPrompt.h"

int gTypeIdCTaskPrompt = qRegisterMetaType<CTaskPrompt>();

CTaskPrompt::CTaskPrompt(QObject *parent) : CTask(parent)
{
}

CTaskPrompt::CTaskPrompt(const QString szText, const QString szTitle,
                         int nInterval,
                         int nPromptInterval,
                         QObject *parent)
    : CTask (nInterval, nPromptInterval, parent)
{
    setObjectName("Task prompt");
    SetTitle(szTitle);
    SetContent(szText);
}

CTaskPrompt::CTaskPrompt(const CTaskPrompt &t)
{
}

int CTaskPrompt::onStart()
{
    slotPrompt();
    m_Top.show();
    return 0;
}

int CTaskPrompt::onRun()
{
    m_Top.close();
    return 0;
}

void CTaskPrompt::slotPrompt()
{
    m_Top.SetText(GetContent() + "\n" + tr("Remaining: ") + szRemaining());
}
