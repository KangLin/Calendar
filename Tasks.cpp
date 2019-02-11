#include "Tasks.h"
#include <QDebug>

CTasks::CTasks(QObject *parent) : QObject(parent)
{
    m_nCurrent = 0;
    m_nId = -1;
    m_szName = "Tasks";
}

CTasks::~CTasks()
{
    qDebug() << "CTasks::~CTasks()" << "id: " << m_nId << " name: " << m_szName;
}

int CTasks::Add(QSharedPointer<CTask> task)
{
    int nRet = 0;
    if(nullptr == task.data())
        return -1;
    
    task->SetId(m_vTask.size());
    int nIndex = m_vTask.indexOf(task);
    if(nIndex > -1)
    {
        qDebug() << "The task is exist";
        return 0;
    }
    m_vTask.push_back(task);
    return nRet;
}

int CTasks::Remove(QSharedPointer<CTask> task)
{
    int nRet = 0;
    m_vTask.removeOne(task);
    return nRet;
}

QSharedPointer<CTask> CTasks::Get()
{
    if(m_nCurrent >= m_vTask.size() || m_nCurrent < 0)
        return nullptr;
    return m_vTask.at(m_nCurrent);
}

int CTasks::GetId()
{
    return m_nId;
}

int CTasks::SetId(int id)
{
    m_nId = id;
    return m_nId;
}

QString CTasks::GetName()
{
    return m_szName;
}

int CTasks::SetName(QString szName)
{
    m_szName = szName;
    return 0;
}

bool CTasks::End()
{
    return m_vTask.isEmpty();
}

int CTasks::Start()
{
    QSharedPointer<CTask> task = Get();
    if(task.data())
        task->Start();
    return 0;
}

int CTasks::Check()
{
    int nRet = 0;
    QSharedPointer<CTask> task = Get();
    if(nullptr == task.data())
    {
        qWarning() << "task pointer is null";
        return 0;
    }
    
    nRet = task->Check();
    if(nRet)
        return nRet;
    
    if(task->End())
        m_vTask.removeOne(task);
    else
        m_nCurrent++;

    if(m_nCurrent >= m_vTask.size())
        m_nCurrent = 0;
    
    Start();
    
    return nRet;
}
