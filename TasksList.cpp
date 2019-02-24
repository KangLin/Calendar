#include "TasksList.h"
#include <QDebug>
#include "ObjectFactory.h"
#include <QFile>
#include <QDir>
#include "Global/GlobalDir.h"

CTasksList::CTasksList(QObject *parent) : QObject(parent)
{
    bool check = false;
    check = connect(&m_Timer, SIGNAL(timeout()),
                    this, SLOT(slotTimeout()));
    Q_ASSERT(check);
    m_nTimerInterval = 0;
    setObjectName("TasksList");
}

CTasksList::~CTasksList()
{
    m_lstTasks.clear();
    if(m_Timer.isActive())
        m_Timer.stop();
}

int CTasksList::Add(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    if(NULL == tasks)
        return -1;
    
    int nIdex = m_lstTasks.indexOf(tasks);
    if(nIdex > -1)
    {
        qDebug() << "The tasks is exist";
        return 0;
    }
    m_lstTasks.push_back(tasks);
    ReSetId();
    return nRet;
}

int CTasksList::Remove(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    m_lstTasks.removeOne(tasks);
    ReSetId();
    return nRet;
}

int CTasksList::RemoveAll()
{
    m_lstTasks.clear();
    return 0;
}

int CTasksList::ReSetId()
{
    int n = 0;
    foreach(QSharedPointer<CTasks> t, m_lstTasks)
    {
        t->SetId(n++);
    }
    return 0;
}

QSharedPointer<CTasks> CTasksList::Get(int index)
{
    if(index >= m_lstTasks.length() || index < 0)
        return QSharedPointer<CTasks>();
    return m_lstTasks.at(index);
}

int CTasksList::Start(int nInterval)
{
    foreach (QSharedPointer<CTasks> tasks, m_lstTasks)
    {
        tasks->Start();
    }
    m_nTimerInterval = nInterval;
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
        if(0 == nRet)
        {
            //TODO:最大公约数，调整间隔  
            //TODO: Modify the maximum common divisor
        }
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

int CTasksList::LoadSettings(const QDomElement &e)
{
    int nRet = 0;
    if("class" != e.tagName())
    {
        qCritical() << "CTasksList::LoadSettings faile: tagName:"
                    << e.tagName() << " name:" << e.attribute("name");
        return -1;
    }

    CObjectFactory::LoadSettings(e, this);
    QDomElement tasks = e.firstChildElement("class");
    while (!tasks.isNull()) {
        QSharedPointer<CTasks> t(qobject_cast<CTasks*>(
                                     CObjectFactory::createObject(
                       tasks.attribute("name").toStdString().c_str())));
        if(!t.data())
        {
            qCritical() << "CTasksList::LoadSettings fail: the pointer is null:"
                        << tasks.attribute("name");
            continue;
        }

        t->LoadSettings(tasks);
        Add(t);
        tasks = tasks.nextSiblingElement("class");
    }
    return nRet;
}

int CTasksList::SaveSettings(QDomElement &e)
{
    int nRet = 0;
    const QMetaObject* pObj = metaObject();
    QDomDocument doc;
    QDomElement de = doc.createElement("class");
    de.setAttribute("name", pObj->className());
    
    CObjectFactory::SaveSettings(de, this);
    
    foreach(QSharedPointer<CTasks> t, m_lstTasks)
    {
        t->SaveSettings(de);
    }
    
    e.appendChild(de);
    return nRet;
}

int CTasksList::LoadSettings(const QString &szFile)
{
    QString file = szFile;
    if(szFile.isEmpty())
        file = CGlobalDir::Instance()->GetDirApplicationXml()
                + QDir::separator()
                + objectName() + "_" + QLocale::system().name()
                + ".xml";
    QFile f(file);
    if(!f.open(QIODevice::ReadOnly))
    {
        qCritical() << "CTasksList::LoadSeetings open file fail: " << file;
        return -1;
    }
    QDomDocument doc;
    if(!doc.setContent(&f))
    {
        f.close();
        return -2;
    }
    f.close();
    return LoadSettings(doc.documentElement().firstChildElement());
}

int CTasksList::SaveSettings(const QString &szFile)
{
    int nRet = 0;
    QString file = szFile;
    if(szFile.isEmpty())
        file = CGlobalDir::Instance()->GetDirApplicationXml()
                + QDir::separator()
                + objectName() + "_" + QLocale::system().name()
                + ".xml";
    QFile f(file);
    if(!f.open(QIODevice::WriteOnly))
    {
        qCritical() << "CTasksList::SaveSettings open file fail: " << file;
        return -1;
    }
    
    QDomDocument doc;
    QDomProcessingInstruction ins;
    //<?xml version='1.0' encoding='UTF-8'?>
    ins = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'UTF-8\'");
    doc.appendChild(ins);
    QDomElement root = doc.createElement("Root");
    doc.appendChild(root);
    nRet = SaveSettings(root);
    if(nRet)
        return nRet;
    QTextStream stream(&f);
    stream.setCodec("UTF-8");
    doc.save(stream, 4);//4个空格缩进  
    f.close();
    return nRet;
}
