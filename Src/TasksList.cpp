// 作者：康林 <kl222@126.com>

#include "TasksList.h"
#include <QDebug>
#include "ObjectFactory.h"
#include <QFile>
#include <QDir>
#include "RabbitCommonDir.h"
#include <QMessageBox>

CTasksList::CTasksList(QObject *parent) : QObject(parent),
    m_nTimerInterval(0),
    m_nIdCount(0),
    m_Thread(this),
    m_bThread(true)
{
    setObjectName("TasksList");
    
    bool check = false;
    if(!m_bThread)
    {
        check = connect(&m_Timer, SIGNAL(timeout()),
                        this, SLOT(slotTimeout()));
        Q_ASSERT(check);
    }
}

CTasksList::~CTasksList()
{
    if(m_bThread)
    {
        m_Thread.Quit();
        m_Thread.wait();
    } else {
        m_Tasks.clear();
        if(m_Timer.isActive())
            m_Timer.stop();
    }
}

int CTasksList::Add(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    if(NULL == tasks)
        return -1;
    
    if(m_Tasks.end() != m_Tasks.find(tasks->GetId()))
    {
        qDebug() << "The tasks is exist";
        return 0;
    }
    
    tasks->SetId(m_nIdCount++);
    m_Tasks[tasks->GetId()] = tasks;

    return nRet;
}

int CTasksList::Remove(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    m_Tasks.remove(tasks->GetId());
    return nRet;
}

int CTasksList::RemoveAll()
{
    m_Tasks.clear();
    m_nIdCount = 0;
    return 0;
}

QSharedPointer<CTasks> CTasksList::Get(int nId)
{
    return m_Tasks.value(nId);
}

CTasksList::POSITION CTasksList::GetFirst()
{
    return m_Tasks.begin();
}

QSharedPointer<CTasks> CTasksList::GetNext(POSITION &pos)
{
    if(m_Tasks.end() == pos)
        return QSharedPointer<CTasks>();
    
    QSharedPointer<CTasks> tasks = pos.value();
    pos++;
    return tasks;
}

int CTasksList::Start(int nInterval, bool bForce)
{
    if(m_bThread)
    {
        if(m_Thread.isRunning() && !bForce)
            return -1;
        
        foreach (QSharedPointer<CTasks> tasks, m_Tasks)
        {
            tasks->Start();
        }
        
        m_Thread.start();
    } else {
        
        if(m_Timer.isActive() && !bForce)
            return -1;
        foreach (QSharedPointer<CTasks> tasks, m_Tasks)
        {
            tasks->Start();
        }
        
        m_nTimerInterval = nInterval;
        if(m_nTimerInterval)
            m_Timer.start(m_nTimerInterval);
    }
    return 0;
}

int CTasksList::Check()
{
    int nRet = 0;
    foreach (QSharedPointer<CTasks> task, m_Tasks)
    {
        if(!task->GetEnable())
            continue;
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
    
    if(m_Tasks.empty())
    {
        if(m_bThread)
        {
            if(m_Thread.isRunning())
            {
                m_Thread.Quit();
            }
        } else {
            if(m_Timer.isActive())
                m_Timer.stop();
        }
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
        qCritical() << "CTasksList::LoadSettings failed: tagName:"
                    << e.tagName() << " name:" << e.attribute("name");
        return -1;
    }

    m_nIdCount = 0;
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
        //m_nIdCount = qMax(m_nIdCount, t->GetId());
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
    
    foreach(QSharedPointer<CTasks> t, m_Tasks)
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
    {
        file = RabbitCommon::CDir::Instance()->GetDirApplicationXml()
                + QDir::separator()
                + objectName() + "_" + QLocale::system().name()
                + ".xml";
        QDir f;
        if(!f.exists(file))
        {
#if defined (Q_OS_ANDROID)
            QString szFileReadOnly = RabbitCommon::CDir::Instance()->GetDirApplicationXml(true)
                    + QDir::separator()
                    + objectName() + "_" + QLocale::system().name()
                    + ".xml";
            if(f.exists(szFileReadOnly))
                QFile::copy(szFileReadOnly, file);
            if(!f.exists(file))
            {
#endif
                file = RabbitCommon::CDir::Instance()->GetDirApplicationXml()
                        + QDir::separator()
                        + objectName() + "_en.xml";
#if defined (Q_OS_ANDROID)
                if(!f.exists(file))
                {
                    szFileReadOnly = RabbitCommon::CDir::Instance()->GetDirApplicationXml(true)
                            + QDir::separator()
                            + objectName() + "_en.xml";
                    if(f.exists(szFileReadOnly))
                        QFile::copy(szFileReadOnly, file);
                }
            }
#endif
            
        }
    }
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
    //TODO: Check version
    return LoadSettings(doc.documentElement().firstChildElement());
}

int CTasksList::SaveSettings(const QString &szFile)
{
    int nRet = 0;
    QString file = szFile;
    if(szFile.isEmpty())
    {
        file = RabbitCommon::CDir::Instance()->GetDirApplicationXml()
                + QDir::separator()
                + objectName() + "_" + QLocale::system().name()
                + ".xml";
        QDir f(file);
        if(!f.exists())
            file = RabbitCommon::CDir::Instance()->GetDirApplicationXml()
                    + QDir::separator()
                    + objectName() + "_en.xml";
    }
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
    root.setAttribute("version", "1");
    doc.appendChild(root);
    nRet = SaveSettings(root);
    if(nRet)
        return nRet;
    QTextStream stream(&f);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    stream.setEncoding(QStringConverter::Utf8);
#else
    stream.setCodec("UTF-8");
#endif
    doc.save(stream, 4);//4个空格缩进  
    f.close();
    return nRet;
}
