#include "ThreadTasks.h"
#include <QDebug>
#include <QTimer>
#include "TasksList.h"

CThreadTasks::CThreadTasks(CTasksList *parent) : QThread(),
    m_bExit(false),
    m_pTaskList(parent)
{
}

CThreadTasks::~CThreadTasks()
{
}

void CThreadTasks::run()
{
    while(!m_bExit)
    {
        qDebug() << "thread id:" << QThread::currentThreadId()
                 << ";Interval:" << m_pTaskList->GetTimerInterval();
        
        QThread::usleep(1000);
        m_pTaskList->Check();
    }
}

int CThreadTasks::Quit()
{
    m_bExit = true;
    quit();
    return 0;
}
