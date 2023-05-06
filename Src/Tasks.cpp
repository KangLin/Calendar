// 作者：康林 <kl222@126.com>

#include "Tasks.h"
#include <QDebug>
#include "ObjectFactory.h"

static const int gTypeIdCTasks = qRegisterMetaType<CTasks>();

CTasks::CTasks(QObject *parent) : QObject(parent)
{
    m_CurrentPostion = 0;
    m_nIdTask = 0;
    m_nId = -1;
    setObjectName("Tasks");
    SetTitle(objectName());
}

CTasks::CTasks(const CTasks &tasks)
{
    m_CurrentPostion = tasks.m_CurrentPostion;
    m_nIdTask = tasks.m_nIdTask;
    m_nId = tasks.m_nId;
    m_szTitle = tasks.m_szTitle;
    m_szContent = tasks.m_szContent;
    setObjectName(tasks.objectName());
    m_Task = tasks.m_Task;
}

CTasks::~CTasks()
{
    qDebug() << "CTasks::~CTasks()" << "id: " << m_nId
             << " name: " << objectName()
             << " Title: " << GetTitle();
}

int CTasks::Add(QSharedPointer<CTask> task)
{
    int nRet = 0;
    if(nullptr == task.data())
        return -1;
    if(m_Task.contains(task))
    {
        qDebug() << "The task is exist";
        return -2;
    }
    
    task->SetId(m_nIdTask++);
    m_Task.push_back(task);

    return nRet;
}

int CTasks::Insert(QSharedPointer<CTask> task, int nIndex)
{
    if(nullptr == task.data())
        return -1;
    if(m_Task.contains(task))
    {
        qDebug() << "The task is exist";
        return -2;
    }
    if(nIndex + 1 < 0 || m_Task.size() <= nIndex + 1)
    {
        return Add(task);
    }
    task->SetId(m_nIdTask++);
    m_Task.insert(nIndex + 1, task);
    return 0;
}

/*
int CTasks::InsertAfter(QSharedPointer<CTask> newTask,
                        QSharedPointer<CTask> task)
{
    int nIndex = m_vTask.indexOf(task);
    return Insert(newTask, nIndex + 1);
}
*/
int CTasks::Remove(QSharedPointer<CTask> task)
{
    int nRet = 0;
    if(nullptr == task.data())
        return -1;
    
    if(!m_Task.contains(task))
    {
        qDebug() << "The task is not exist";
        return 0;
    }
    m_Task.removeAll(task);
    return nRet;
}

QSharedPointer<CTask> CTasks::Get(int nIdTask)
{
    return m_Task.value(nIdTask);
}

QSharedPointer<CTask> CTasks::GetCurrent()
{
    if(m_CurrentPostion < 0 || m_CurrentPostion >= m_Task.size())
        return QSharedPointer<CTask>();
    return m_Task[m_CurrentPostion];
}

int CTasks::Length()
{
    return m_Task.size();
}

QSharedPointer<CTask> CTasks::GetIndex(int nIndex)
{
    if(nIndex < 0 || nIndex >= m_Task.size())
        return QSharedPointer<CTask>();
    return m_Task[nIndex];
}

int CTasks::GetCurrentIndex()
{
    int nIndex = 0;
    POSITION it = m_Task.begin();
    while(it != m_Task.end())
    {
        if(m_Task.size() <= m_CurrentPostion)
        {
            return nIndex;
        }
        it++;
        nIndex++;
    }
    return nIndex;
}

CTasks::POSITION CTasks::GetFirst()
{
    return m_Task.begin();
}

QSharedPointer<CTask> CTasks::GetNext(POSITION &pos)
{
    if(m_Task.end() == pos)
        return QSharedPointer<CTask>();
    
    QSharedPointer<CTask> t = *pos;
    pos++;
    return t;
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

QString CTasks::GetTitle()
{
    return m_szTitle;
}

int CTasks::SetTitle(const QString &szTitle)
{
    m_szTitle = szTitle;
    return 0;
}

QString CTasks::GetContent()
{
    return m_szContent;
}

int CTasks::SetContent(const QString &szContent)
{
    m_szContent = szContent;
    return 0;
}

QIcon CTasks::GetIcon()
{
    return m_Icon;
}

int CTasks::SetIcon(QIcon icon)
{
    m_Icon = icon;
    return 0;
}

bool CTasks::End()
{
    return m_Task.isEmpty();
}

int CTasks::Start()
{
    QSharedPointer<CTask> task = GetCurrent();
    if(task.data())
        task->Start();
    return 0;
}

int CTasks::Check()
{
    int nRet = 0;
    QSharedPointer<CTask> task = GetCurrent();
    if(nullptr == task.data())
    {
        qWarning() << "CTasks::Check(): task pointer is null";
        return 0;
    }
    
    nRet = task->Check();
    if(nRet)
        return nRet;
    
    if(task->End())
        m_Task.remove(task->GetId());
    else
        m_CurrentPostion++;

    if(m_CurrentPostion >= m_Task.size())
        m_CurrentPostion = 0;
    
    Start();
    
    return nRet;
}

int CTasks::LoadSettings(const QDomElement &e)
{
    int nRet = 0;
    m_nIdTask = 0;
    CObjectFactory::LoadSettings(e, this);
    QDomElement task = e.firstChildElement("class");
    while (!task.isNull()) {
        QSharedPointer<CTask> t(qobject_cast<CTask*>(
                                    CObjectFactory::createObject(
                       task.attribute("name").toStdString().c_str())));
        if(!t.data())
        {
            qCritical() << "CTasksList::LoadSettings fail: the pointer is null"
                           << task.attribute("name");;
            continue;
        }
        t->LoadSettings(task);
        Add(t);
        task = task.nextSiblingElement("class");
    }
    return nRet;
}

int CTasks::SaveSettings(QDomElement &e)
{
    int nRet = 0;
    if(e.isNull())
    {
        qCritical() << "CTask::SaveSettings： e is null";
        return -1;
    }
    const QMetaObject* pObj = metaObject();
    QDomDocument doc;
    QDomElement tasks = doc.createElement("class");
    tasks.setAttribute("name", pObj->className());;
        
    CObjectFactory::SaveSettings(tasks, this);
    foreach(QSharedPointer<CTask> t, m_Task)
    {
        t->SaveSettings(tasks);
    }
    e.appendChild(tasks);
    return nRet;
}
