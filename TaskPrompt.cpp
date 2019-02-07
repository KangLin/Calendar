#include "TaskPrompt.h"

CTaskPrompt::CTaskPrompt(QObject *parent) : CTask(parent)
{
}

CTaskPrompt::CTaskPrompt(const QString szText,
                         int nInterval,
                         int nPromptInterval,
                         QObject *parent)
    : CTask (nInterval, nPromptInterval, parent)
{
    m_szText = szText;
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
    m_Top.SetText(m_szText + "\n" + tr("Remaining: ") + szRemaining());
}
