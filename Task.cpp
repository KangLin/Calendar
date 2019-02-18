#include "Task.h"
#include <QDebug>
#include <QSound>
#include <ObjectFactory.h>
#include <QtXml>
#include <QMetaProperty>

int gTypeIdCTask = qRegisterMetaType<CTask>();

CTask::CTask(QObject *parent) : QObject(parent)
{
    Init();
    SetInterval(0);
    SetPromptInterval(0);
}

CTask::CTask(const CTask &task)
{
    m_nId = task.m_nId;
    setObjectName(task.objectName());
    m_szTitle = task.m_szTitle;
    m_szContent = task.m_szContent;
    m_szRunSound = task.m_szRunSound;
    m_szStartSound = task.m_szStartSound;
    m_nInterval = task.m_nInterval;
    m_nPromptInterval = task.m_nPromptInterval;
}

CTask::CTask(int nInterval, int nPromptInterval, QObject *parent)
{
    Init();
    SetInterval(nInterval);
    SetPromptInterval(nPromptInterval);
}

int CTask::Init()
{
    bool check = connect(&m_PromptTimer, SIGNAL(timeout()),
                         this, SLOT(slotPrompt()));
    Q_ASSERT(check);
    SetId(-1);
    setObjectName("Task");
    m_Time.start();
    return 0;
}

CTask::~CTask()
{
    qDebug() << "CTask::~CTask(), id: " << GetId() << " name:" << objectName();
}

int CTask::Start()
{
    if(!m_szStartSound.isEmpty())
        QSound::play(m_szStartSound);
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
        if(!m_szRunSound.isEmpty())
            QSound::play(m_szRunSound);
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

int CTask::SetTitle(QString szTitle)
{
    m_szTitle = szTitle;
    return 0;
}

QString CTask::GetTitle()
{
    return m_szTitle;
}

int CTask::SetContent(QString szContent)
{
    m_szContent = szContent;
    return 0;
}

QString CTask::GetContent()
{
    return m_szContent;
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
    int nRet = GetInterval() - Elapsed();
    if(nRet < 0)
        return 0;
    return nRet;
}

QString CTask::szRemaining()
{
    QTime tm(0, 0);
    tm = tm.addMSecs(Remaining());
    return tm.toString("HH:mm:ss");
}

int CTask::GetInterval()
{
    return m_nInterval;
}

int CTask::GetPromptInterval()
{
    return m_nPromptInterval;
}

int CTask::SetPromptInterval(int interval)
{
    m_nPromptInterval = interval;
    if(m_PromptTimer.isActive())
    {
        m_PromptTimer.stop();
        m_PromptTimer.start(m_nPromptInterval);
    }
    return 0;
}

int CTask::SetStartSound(const QString &szSound)
{
    m_szStartSound = szSound;
    return 0;
}

int CTask::SetRunSound(const QString &szSound)
{
    m_szRunSound = szSound;
    return 0;
}

int CTask::SetSound(const QString &szStartSound, const QString &szRunSound)
{
    m_szStartSound = szStartSound;
    m_szRunSound = szRunSound;
    return 0;
}

bool CTask::End()
{
    return false;
}

int CTask::LoadSettings(const QDomElement &e)
{
    int nRet = 0;
    if("class" != e.tagName())
    {
        qCritical() << "CTask::LoadSettings faile: tagName:"
                    << e.tagName() << " name:" << e.attribute("name");
        return -1;
    }
    const QMetaObject* pObj = metaObject();
    QDomElement de = e.firstChildElement();
    while(!de.isNull())
    {
        QString szName = de.nodeName();
        QString szValue = de.attribute("value");
        int type = de.attribute("type").toInt();
        int nIndex = pObj->indexOfProperty(szName.toStdString().c_str());
        QMetaProperty property = pObj->property(nIndex);
        QVariant v(szValue);
        
        if(!property.write(this, szValue))
            qCritical() << "Write propery fail: " << pObj->className() << szName;
        
        de = de.nextSiblingElement();
    }
    return nRet;
}

int CTask::SaveSettings(QDomElement &e)
{
    int nRet = 0;

    const QMetaObject* pObj = metaObject();
    
    QDomDocument doc;
    QDomElement task = doc.createElement("class");
    task.setAttribute("name", pObj->className());    
    
    int nAttr = pObj->propertyCount();
    for(int i = 0; i < nAttr; i++)
    {
        QMetaProperty p = pObj->property(i);
        if(!(p.isReadable() && p.isWritable()))
            continue;
        QString szName = p.name();
        QVariant value = p.read(this);
        //qDebug() << "propery name: " << szName << " value: " << value.toString();
        QDomElement domProperty = doc.createElement(szName);
        domProperty.setAttribute("type", QString::number(value.type()));
        domProperty.setAttribute("value", value.toString());
        
        task.appendChild(domProperty);
    }
    e.appendChild(task);
    
    return nRet;
}
