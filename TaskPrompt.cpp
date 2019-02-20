#include "TaskPrompt.h"

static int gTypeIdCTaskPrompt = qRegisterMetaType<CTaskPrompt>();

CTaskPrompt::CTaskPrompt(QObject *parent) : CTask(parent)
{
    setObjectName("TaskPrompt");
    SetTitle(objectName());
}

CTaskPrompt::CTaskPrompt(const QString szContent, const QString szTitle,
                         int nInterval,
                         int nPromptInterval,
                         QObject *parent)
    : CTask (nInterval, nPromptInterval, parent)
{
    setObjectName("TaskPrompt");
    SetTitle(szTitle);
    SetContent(szContent);
}

CTaskPrompt::CTaskPrompt(const CTaskPrompt &t)
{
    Q_UNUSED(t);
}

QString CTaskPrompt::GetDescription() const
{
    return tr("Prompt task, Only prompt.");
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
