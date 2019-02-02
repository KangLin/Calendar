#include "Task.h"
#include <QDebug>

CTask::CTask(QObject *parent) : QObject(parent)
{
    SetInterval(0);
    m_nPromptInterval = 0;
    Init();
}

CTask::CTask(int nInterval, int nPromptInterval, QObject *parent)
{
    SetInterval(nInterval);
    m_nPromptInterval = nPromptInterval;
    Init();
}

int CTask::Init()
{
    bool check = connect(&m_PromptTimer, SIGNAL(timeout()),
                         this, SLOT(slotPrompt()));
    Q_ASSERT(check);
    m_nId = -1;
    m_szName = "Task";
    m_Time.start();
    return 0;
}

CTask::~CTask()
{
    qDebug() << "CTask::~CTask(), id: " << GetId() << " name:" << GetName();
}

int CTask::Start()
{
    m_Time.restart();
    if(m_nPromptInterval > 0)
        m_PromptTimer.start(m_nPromptInterval);
    return onStart();
}

int CTask::onStart()
{
    return 0;
}

int CTask::onRun()
{
    return 0;
}

int CTask::Check()
{
    int nRet = -1;
    if(m_nInterval < Elapsed())
    {
        m_PromptTimer.stop();
        nRet = onRun();
    }
    return nRet;
}

void CTask::slotPrompt()
{
    QTime tm(0, 0);
    tm = tm.addMSecs(Remaining());
    qDebug() << "CTask::slotPrompt() " << tm.toString("HH:mm:ss");
}

int CTask::GetId()
{
    return m_nId;
}

int CTask::SetId(int id)
{
    m_nId = id;
    return m_nId;
}

QString CTask::GetName()
{
    return m_szName;
}

int CTask::SetName(QString szName)
{
    m_szName = szName;
    return 0;
}

int CTask::SetInterval(int nInterval)
{
    m_nInterval = nInterval;
    return m_nInterval;
}

int CTask::Elapsed()
{
    return m_Time.elapsed();
}

int CTask::Remaining()
{
    return GetInterval() - Elapsed();
}

int CTask::GetInterval()
{
    return m_nInterval;
}

bool CTask::End()
{
    return false;
}

int CTask::LoadSettings()
{
    int nRet = 0;
    
    return nRet;
}

int CTask::SaveSettings()
{
    int nRet = 0;
    
    return nRet;
}
