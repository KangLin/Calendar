#include "Activity.h"

static const int gTypeIdActivity = qRegisterMetaType<CActivity>();

CActivity::CActivity(QObject *parent) : QObject(parent)
{
    m_nId = 0;
    m_tyDate = Solar;
    AddPrompt();
}

CActivity::CActivity(const CActivity &a)
{
    m_nId = a.m_nId;
    m_szTitle = a.m_szTitle;
    m_szDescription = a.m_szDescription;
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

CActivity::~CActivity()
{
}

int CActivity::SetId(int id)
{
    m_nId = id;
    return 0;
}

int CActivity::GetId()
{
    return m_nId;
}

int CActivity::SetTitle(const QString &szTitle)
{
    m_szTitle = szTitle;
    return 0;
}

QString CActivity::GetTitle() const
{
    return m_szTitle;
}

int CActivity::SetDescription(const QString &szDescription)
{
    m_szDescription = szDescription;
    return 0;
}

QString CActivity::GetDescription() const
{
    return m_szDescription;
}

int CActivity::SetPlace(const QString &szPlace)
{
    m_szPlace = szPlace;
    return 0;
}

QString CActivity::GetPlace() const
{
    return m_szPlace;
}

int CActivity::SetAccount(const QString &szAccount)
{
    m_szAccount = szAccount;
    return 0;
}

QString CActivity::GetAccount() const
{
    return m_szAccount;
}

int CActivity::SetTypeDate(_TYPE_DATE type)
{
    m_tyDate = type;
    return 0;
}

CActivity::_TYPE_DATE CActivity::GetTypeDate() const
{
    return m_tyDate;
}

int CActivity::SetDateStart(int year, int month, int day)
{
    m_dtStart.Year = year;
    m_dtStart.Month = month;
    m_dtStart.Day = day;
    return 0;
}

CActivity::CDate CActivity::GetDateStart() const
{
    return m_dtStart;
}

int CActivity::SetDateEnd(int year, int month, int day)
{
    m_dtEnd.Year = year;
    m_dtEnd.Month = month;
    m_dtEnd.Day = day;
    return 0;
}

CActivity::CDate CActivity::GetDateEnd() const
{
    return m_dtEnd;
}

int CActivity::SetRepeat(_ENUM_REPEAT repeat)
{
    m_Repeat = repeat;
    return 0;
}

CActivity::_ENUM_REPEAT CActivity::GetRepeat() const
{
    return m_Repeat;
}

int CActivity::AddPrompt(int minute)
{
    _PROMPT p = {minute, false};
    m_Prompt.push_back(p);
    return 0;
}

int CActivity::onCheck()
{
    int nRet = 0;
    if(m_Prompt.isEmpty())
        return 0;
    
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

int CActivity::onPrompt()
{
    int nRet = 0;
    
    return nRet;
}

int CActivity::onCheckOnce()
{
    int nRet = 0;
    QDateTime dt = QDateTime::currentDateTime();
    if(Solar == GetTypeDate())
    {
        
    }
    return nRet;
}
