#include "TaskPrompt.h"
#include <QDebug>

static int gTypeIdCTaskPrompt = qRegisterMetaType<CTaskPrompt>();

CTaskPrompt::CTaskPrompt(QObject *parent) : CTask(parent)
{
    setObjectName("TaskPrompt");
    SetTitle(objectName());
    SetTitle(GetTitle());
    SetInterval(5 * 60 * 1000);
    SetPromptInterval(1000);
    
    bool check = connect(this, SIGNAL(sigPrompt()),
                         this, SLOT(slotPrompt()));
    Q_ASSERT(check);
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
    emit sigPrompt();
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
    m_Top.show();
}
