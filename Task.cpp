#include "Task.h"
#include <QDebug>
#include <QSound>
#include <ObjectFactory.h>
#include <QtXml>
#include <QMetaProperty>

static int gTypeIdCTask = qRegisterMetaType<CTask>();

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
    Q_UNUSED(parent);
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
    SetTitle(objectName());
    m_Time.start();
    return 0;
}

CTask::~CTask()
{
    qDebug() << "CTask::~CTask(), id: " << GetId()
             << " name:" << objectName()
             << " Title: " << GetTitle();
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
    if(GetInterval() < Elapsed())
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

int CTask::GetId() const
{
    return m_nId;
}

int CTask::SetId(int id)
{
    m_nId = id;
    return m_nId;
}

QString CTask::GetDescription() const
{
    return tr("Task is base unit. Is a minimal execution unit.\n"
              "Start with the Start function and run the Run function after the interval.\n"
              "If PromptInterval isn't 0, then interval PromptInterval time prompt.");
}

int CTask::SetTitle(QString szTitle)
{
    m_szTitle = szTitle;
    return 0;
}

QString CTask::GetTitle() const
{
    return m_szTitle;
}

int CTask::SetContent(QString szContent)
{
    m_szContent = szContent;
    return 0;
}

QString CTask::GetContent() const
{
    return m_szContent;
}

QIcon CTask::GetIcon()
{
    return m_Icon;
}

int CTask::SetIcon(QIcon icon)
{
    m_Icon = icon;
    return 0;
}

int CTask::SetInterval(int nInterval)
{
    m_nInterval = nInterval;
    return m_nInterval;
}

int CTask::GetInterval() const
{
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

int CTask::GetPromptInterval() const
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
    CObjectFactory::LoadSettings(e, this);
    return nRet;
}

int CTask::SaveSettings(QDomElement &e)
{
    int nRet = 0;
    if(e.isNull())
    {
        qCritical() << "CTask::SaveSettings： e is null";
        return -1;
    }
    const QMetaObject* pObj = metaObject();
    QDomDocument doc;
    QDomElement task = doc.createElement("class");
    task.setAttribute("name", pObj->className());;
    CObjectFactory::SaveSettings(task, this);
    e.appendChild(task);
    
    return nRet;
}
