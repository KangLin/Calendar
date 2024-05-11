// 作者：康林 <kl222@126.com>

#include "TaskPrompt.h"
#include <QDebug>

static int gTypeIdCTaskPrompt = qRegisterMetaType<CTaskPrompt>();

CTaskPrompt::CTaskPrompt(QObject *parent) : CTask(parent)
{
    Init();
    SetTitle(objectName());
    SetTitle(GetTitle());
    SetInterval(5 * 60 * 1000);
    SetPromptInterval(1000);
}

CTaskPrompt::CTaskPrompt(const QString szContent, const QString szTitle,
                         int nInterval,
                         int nPromptInterval,
                         QObject *parent)
    : CTask (nInterval, nPromptInterval, parent)
{
    Init();
    SetTitle(szTitle);
    SetContent(szContent);
}

CTaskPrompt::CTaskPrompt(const CTaskPrompt &t)
{
    Q_UNUSED(t);
}

void CTaskPrompt::Init()
{
    setObjectName("TaskPrompt");
    bool check = connect(this, SIGNAL(sigShow()),
                         this, SLOT(slotShow()));
    Q_ASSERT(check);
    check = connect(this, SIGNAL(sigClose()),
                         this, SLOT(slotClose()));
    Q_ASSERT(check);
    check = connect(this, SIGNAL(sigUpdate()),
                         this, SLOT(slotUpdate()));
    Q_ASSERT(check);
}

QString CTaskPrompt::GetDescription() const
{
    return tr("Prompt task, Only prompt.");
}

int CTaskPrompt::onStart()
{
    emit sigShow();
    return 0;
}

int CTaskPrompt::onRun()
{
    emit sigClose();
    return 0;
}

void CTaskPrompt::slotPrompt()
{
    emit sigUpdate();
}

void CTaskPrompt::slotShow()
{
    slotPrompt();
    m_Top.show();
}

void CTaskPrompt::slotClose()
{
    m_Top.close();
}

void CTaskPrompt::slotUpdate()
{
    m_Top.SetText(GetContent() + "\n" + tr("Remaining: ") + szRemaining());
}
