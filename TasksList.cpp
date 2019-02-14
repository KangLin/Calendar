#include "TasksList.h"
#include <QDebug>

CTasksList::CTasksList(QObject *parent) : QObject(parent)
{
    bool check = false;
    check = connect(&m_Timer, SIGNAL(timeout()),
                    this, SLOT(slotTimeout()));
    Q_ASSERT(check);
    m_nTimerInterval = 1000;
}

CTasksList::~CTasksList()
{
    if(m_Timer.isActive())
        m_Timer.stop();
}

int CTasksList::Add(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    if(NULL == tasks)
        return -1;
    tasks->SetId(m_lstTasks.size());
    int nIdex = m_lstTasks.indexOf(tasks);
    if(nIdex > -1)
    {
        qDebug() << "The tasks is exist";
        return 0;
    }
    m_lstTasks.push_back(tasks);
    //TODO: Add the maximum common divisor
    //m_nTimerInterval =
    return nRet;
}

int CTasksList::Remove(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    m_lstTasks.removeOne(tasks);
    return nRet;
}

int CTasksList::RemoveAll()
{
    m_lstTasks.clear();
    return 0;
}

int CTasksList::Start()
{
    foreach (QSharedPointer<CTasks> tasks, m_lstTasks)
    {
        tasks->Start();
    }
    if(m_nTimerInterval)
        m_Timer.start(m_nTimerInterval);
    return 0;
}

int CTasksList::Check()
{
    int nRet = 0;
    foreach (QSharedPointer<CTasks> task, m_lstTasks)
    {
        nRet = task->Check();
        if(task->End())
        {
            Remove(task);//TODO: 检查是否会出错  
            //TODO: Modify the maximum common divisor
        }
    }
    
    if(m_lstTasks.empty())
    {
        if(m_Timer.isActive())
            m_Timer.stop();
    }
    return nRet;
}

void CTasksList::slotTimeout()
{
    Check();
}
