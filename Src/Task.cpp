// 作者：康林 <kl222@126.com>

#include "Task.h"
#include <QDebug>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    #include <QSoundEffect>
#else
    #include <QSound>
#endif
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
    SetId(-1);
    setObjectName("Task");
    SetTitle(objectName());
    SetContent(GetTitle());
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
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        QSoundEffect effect;
        effect.setSource(QUrl::fromLocalFile(m_szStartSound));
        //    effect.setLoopCount(1);
        //    effect.setVolume(1);
        effect.play();
#else
        QSound::play(m_szStartSound);
#endif
    }

    m_Time.restart();
    if(m_nPromptInterval > 0)
    {
        m_PromptTime = QTime::currentTime();
    }
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
        nRet = onRun();
        if(nRet)
            qDebug() << "onRun fail:" << nRet;
        
        if(!m_szRunSound.isEmpty())
        {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            QSoundEffect effect;
            effect.setSource(QUrl::fromLocalFile(m_szRunSound));
            //    effect.setLoopCount(1);
            //    effect.setVolume(1);
            effect.play();
#else
            QSound::play(m_szRunSound);
#endif
        }

        nRet = 0;
    } else {
        if(m_nPromptInterval > 0)
        {
            if(m_PromptTime.msecsTo(QTime::currentTime()) > m_nPromptInterval)
            {
                slotPrompt();
                m_PromptTime = QTime::currentTime();
            }
        }
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
    m_PromptTime = QTime::currentTime();
    return 0;
}

int CTask::SetStartSound(const QString &szSound)
{
    m_szStartSound = szSound;
    return 0;
}

QString CTask::GetStartSound()
{
    return m_szStartSound;
}

int CTask::SetRunSound(const QString &szSound)
{
    m_szRunSound = szSound;
    return 0;
}

QString CTask::GetRunSound()
{
    return m_szRunSound;
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
