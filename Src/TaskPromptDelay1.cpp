// 作者：康林 <kl222@126.com>

#include "TaskPromptDelay.h"
#include <QSound>

static int gTypeIdCTaskPromptDelay = qRegisterMetaType<CTaskPromptDelay>();

CTaskPromptDelay::CTaskPromptDelay(QObject* parent) : CTaskPrompt (parent)
{
    Init();
}

CTaskPromptDelay::CTaskPromptDelay(const QString szText,
                       const QString szTitle,
                       int nInterval,
                       int nPromptInterval,
                       QObject *parent) 
    : CTaskPrompt (szText, szTitle, nInterval, nPromptInterval, parent)
{
    Init();
}

CTaskPromptDelay::CTaskPromptDelay(const CTaskPromptDelay &task)
{
    Q_UNUSED(task);
}

int CTaskPromptDelay::Init()
{
    m_bStop = false;
    setObjectName("TaskPromptDelay");
    SetTitle(objectName());
    /*m_Menu.addAction(QIcon(":/icon/Close"), tr("Close"),
                     &m_Top, SLOT(close()));
    m_Menu.addAction(tr("Delay 5 Minute"),
                  this, SLOT(slotDelay5Minute(bool)));*/
    m_Top.SetPopupMenu(&m_Menu);
    return 0;
}

int CTaskPromptDelay::SaveSettings(QDomElement &e)
{
    Q_UNUSED(e);
    return 0;
}

QString CTaskPromptDelay::GetDescription() const
{
    return tr("Delayable task. the task can be delayed.");
}

int CTaskPromptDelay::Check()
{
    int nRet = -1;
    
    if(m_bStop)
    {
        if(m_Delay.isEmpty())
            return 0;
        nRet = m_Delay.first()->Check();
        if(nRet)
            return nRet;
        m_Delay.pop_front();
        return -1;
    }
    
    if(GetInterval() < Elapsed())
    {
        m_bStop = true;
        m_PromptTimer.stop();
        if(!m_szRunSound.isEmpty())
            QSound::play(m_szRunSound);
        nRet = onRun();
        //TODO: weather check the nRet?
        if(m_Delay.isEmpty())
            return nRet;
        m_Delay.first()->Start();
        return -1;
    }
    return nRet;
}

void CTaskPromptDelay::slotDelay5Minute(bool checked)
{
    Q_UNUSED(checked);
    AddDelay(5);
}

int CTaskPromptDelay::AddDelay(int nMinute)
{
    m_Top.close();
    CTaskPromptDelay *p =
                new CTaskPromptDelay(
                    GetContent(),
                    GetTitle(),
                    nMinute * 60 * 1000,
                    GetPromptInterval());
   // QSharedPointer<CTaskPromptDelay> t(p);
    //m_Delay.append(QSharedPointer<CTaskPromptDelay>(p));
    return 0;
}
