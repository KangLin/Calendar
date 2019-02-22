#include "Tasks.h"
#include <QDebug>
#include "ObjectFactory.h"

int gTypeIdCTasks = qRegisterMetaType<CTasks>();

CTasks::CTasks(QObject *parent) : QObject(parent)
{
    m_nCurrent = 0;
    m_nId = -1;
    setObjectName("Tasks");
    SetTitle(objectName());
}

CTasks::CTasks(const CTasks &tasks)
{
    m_nCurrent = tasks.m_nCurrent;
    m_nId = tasks.m_nId;
    m_szTitle = tasks.m_szTitle;
    m_szContent = tasks.m_szContent;
    setObjectName(tasks.objectName());
    m_vTask = tasks.m_vTask;
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
    
    int nIndex = m_vTask.indexOf(task);
    if(nIndex > -1)
    {
        qDebug() << "The task is exist";
        return 0;
    }
    
    m_vTask.push_back(task);
    nRet = ReSetId();
    return nRet;
}

int CTasks::Insert(QSharedPointer<CTask> task, int nIndex)
{
    if(nullptr == task.data() || nIndex < 0 || nIndex > m_vTask.length())
        return -1;
    
    int i = m_vTask.indexOf(task);
    if(i > -1)
    {
        qDebug() << "The task is exist";
        return 0;
    }
    
    m_vTask.insert(nIndex, task);
    ReSetId();
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
    m_vTask.removeOne(task);
    if(m_nCurrent >= m_vTask.size())
        m_nCurrent = m_vTask.size() - 1;
    ReSetId();
    return nRet;
}

QSharedPointer<CTask> CTasks::Get(int index)
{
    if(index >= m_vTask.size() || index < 0)
        return QSharedPointer<CTask>();
    return m_vTask.at(index);
}

QSharedPointer<CTask> CTasks::Get()
{
    return Get(m_nCurrent);
}

int CTasks::Length()
{
    return m_vTask.length();
}

int CTasks::GetCurrentIndex()
{
    return m_nCurrent;
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
    return m_vTask.isEmpty();
}

int CTasks::ReSetId()
{
    int n = 0;
    foreach(QSharedPointer<CTask> t, m_vTask)
    {
        t->SetId(n++);
    }
    return 0;
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
        qWarning() << "CTasks::Check(): task pointer is null";
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

int CTasks::LoadSettings(const QDomElement &e)
{
    int nRet = 0;
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
        m_vTask.push_back(t);
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
    foreach(QSharedPointer<CTask> t, m_vTask)
    {
        t->SaveSettings(tasks);
    }
    e.appendChild(tasks);
    return nRet;
}
