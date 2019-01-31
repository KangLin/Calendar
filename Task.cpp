#include "Task.h"
#include <QDebug>

CTask::CTask(QObject *parent) : QObject(parent)
{
    m_nId = -1;
    m_szName = "Task";
    SetInterval(0);
    m_Time.start();
}

CTask::CTask(int nInterval, QObject *parent)
{
    m_nId = -1;
    m_szName = "Task";
    SetInterval(nInterval);
    m_Time.start();
}

CTask::~CTask()
{
    qDebug() << "CTask::~CTask(), id: " << m_nId << " name:" <<m_szName;
}

int CTask::slotCheck()
{
    int nRet = -1;
    if(m_nInterval < m_Time.elapsed())
        nRet = onRun();
    return nRet;
}

int CTask::onRun()
{
    int nRet = 0;
    return nRet;
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

int CTask::slotStart()
{
    m_Time.restart();
    return 0;
}
