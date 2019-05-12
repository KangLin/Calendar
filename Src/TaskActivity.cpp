#include "TaskActivity.h"
#include "ObjectFactory.h"
#include <QDebug>

static const int gTypeIdTaskActivity = qRegisterMetaType<CTaskActivity>();
static const int gTypeIdCDate = qRegisterMetaType<CTaskActivity::CDate>();

CTaskActivity::CTaskActivity(QObject *parent) : CTask(parent)
{
    setObjectName("Task Activity");
    SetTitle(objectName());
    m_tyDate = Solar;
    m_dtStart.Year = QDate::currentDate().year();
    m_dtStart.Month = QDate::currentDate().month();
    m_dtStart.Day = QDate::currentDate().day();
    m_dtEnd = m_dtStart;
    m_Repeat = Once;
    AddPrompt();
}

CTaskActivity::CTaskActivity(const CTaskActivity &a)
{
    m_szAccount = a.m_szAccount;
    m_szPlace = a.m_szPlace;
    m_tyDate = a.m_tyDate;
    m_dtStart = a.m_dtStart;
    m_dtEnd = a.m_dtEnd;
    m_tmStart = a.m_tmStart;
    m_tmEnd = a.m_tmEnd;
    m_Repeat = a.m_Repeat;
    m_Prompt = a.m_Prompt;
}

CTaskActivity::~CTaskActivity()
{
}

QString CTaskActivity::GetDescription() const
{
    return tr("Task Activity");
}

int CTaskActivity::SetPlace(const QString &szPlace)
{
    m_szPlace = szPlace;
    return 0;
}

QString CTaskActivity::GetPlace() const
{
    return m_szPlace;
}

int CTaskActivity::SetAccount(const QString &szAccount)
{
    m_szAccount = szAccount;
    return 0;
}

QString CTaskActivity::GetAccount() const
{
    return m_szAccount;
}

int CTaskActivity::SetTypeDate(_TYPE_DATE type)
{
    m_tyDate = type;
    return 0;
}

CTaskActivity::_TYPE_DATE CTaskActivity::GetTypeDate() const
{
    return m_tyDate;
}

int CTaskActivity::SetDateStart(int year, int month, int day)
{
    m_dtStart.Year = year;
    m_dtStart.Month = month;
    m_dtStart.Day = day;
    return 0;
}

int CTaskActivity::GetDateStart(CDate &date) 
{
    date = m_dtStart;
    return 0;
}

int CTaskActivity::SetDateStart(QString date)
{
    QStringList s = date.split("-");
    m_dtStart.Year = s.at(0).toInt();
    m_dtStart.Month = s.at(1).toInt();
    m_dtStart.Day = s.at(2).toInt();
    return 0;
}

QString CTaskActivity::GetDateStart()
{
    return QString::number(m_dtStart.Year)
            + "-" + QString::number(m_dtStart.Month)
            + "-" + QString::number(m_dtStart.Day);
    
}

int CTaskActivity::SetTimeStart(QTime t)
{
    m_tmStart = t;
    return 0;
}

QTime CTaskActivity::GetTimeStart()
{
    return m_tmStart;
}

int CTaskActivity::SetDateEnd(int year, int month, int day)
{
    m_dtEnd.Year = year;
    m_dtEnd.Month = month;
    m_dtEnd.Day = day;
    return 0;
}

int CTaskActivity::GetDateEnd(CDate date)
{
    date = m_dtEnd;
    return 0;
}

int CTaskActivity::SetDateEnd(QString date)
{
    QStringList s = date.split("-");
    m_dtEnd.Year = s.at(0).toInt();
    m_dtEnd.Month = s.at(1).toInt();
    m_dtEnd.Day = s.at(2).toInt();
    return 0;
}

QString CTaskActivity::GetDateEnd()
{
    return QString::number(m_dtEnd.Year)
            + "-" + QString::number(m_dtEnd.Month)
            + "-" + QString::number(m_dtEnd.Day);
}

int CTaskActivity::SetTimeEnd(QTime t)
{
    m_tmEnd = t;
    return 0;
}

QTime CTaskActivity::GetTimeEnd()
{
    return m_tmEnd;
}

int CTaskActivity::SetRepeat(_ENUM_REPEAT repeat)
{
    m_Repeat = repeat;
    return 0;
}

CTaskActivity::_ENUM_REPEAT CTaskActivity::GetRepeat() const
{
    return m_Repeat;
}

int CTaskActivity::AddPrompt(int minute)
{
    _PROMPT p = {minute, false};
    m_Prompt.push_back(p);
    return 0;
}

int CTaskActivity::SetPrompt(const QString &prompt)
{
    QStringList s = prompt.split(",");
    foreach(QString p, s)
    {
        AddPrompt(p.toInt());
    }
    return 0;
}

QString CTaskActivity::GetPrompt()
{
    QString s;
    QVector<_PROMPT>::iterator it;
    for(it = m_Prompt.begin(); it != m_Prompt.end(); it++)
    {
        if(it != m_Prompt.begin())
            s += ",";
        s += QString::number(it->nPrompt);
    }
    return s;
}

int CTaskActivity::onPrompt()
{
    int nRet = 0;
    
    return nRet;
}

int CTaskActivity::Start()
{
    return 0;
}

int CTaskActivity::Check()
{
    int nRet = 0;
    
    switch (GetRepeat()) {
    case Once:
        nRet = onCheckOnce();
        break;
    case EveryDay:
        break;
    case Weekly:
        break;
    case Monthly:
        break;
    case EveryYear:
        break;
    case Custom:
        break;
    }
    return nRet;
}

bool CTaskActivity::End()
{
    return false;
}

int CTaskActivity::onCheckOnce()
{
    int nRet = 0;
    QDateTime dt = QDateTime::currentDateTime();
    QVector<_PROMPT>::iterator it;
    for(it = m_Prompt.begin(); it != m_Prompt.end(); it++)
    {
        
    }
    if(Solar == GetTypeDate())
    {
        
    }
    return nRet;
}
