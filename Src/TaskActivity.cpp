// 作者：康林 <kl222@126.com>

#include "TaskActivity.h"
#include "FrmTopActivity.h"
#include "ObjectFactory.h"
#include <QDebug>
#include "LunarCalendar.h"

static const int gTypeIdTaskActivity = qRegisterMetaType<CTaskActivity>();
static const int gTypeIdCDate = qRegisterMetaType<CTaskActivity::CDate>();

CTaskActivity::CTaskActivity(QObject *parent) : CTask(parent)
{
    setObjectName("Task Activity");
    SetContent("");
    SetTitle(objectName());
    m_tyDate = Solar;
    m_dtStart.Year = QDate::currentDate().year();
    m_dtStart.Month = QDate::currentDate().month();
    m_dtStart.Day = QDate::currentDate().day();
    m_dtEnd = m_dtStart;
    m_tmStart = QTime::currentTime();
    m_tmEnd = m_tmStart.addSecs(3600);
    m_Repeat = Once;
    m_CustomNumber = 1;
    m_LoopCount = 1;
    m_Week = 0;
    m_Effective = Always;
    m_UntilDate = QDate::currentDate();
    AddPrompt();
    
    bool check = connect(this, SIGNAL(sigShowTopForm()),
                         this, SLOT(slotShowTopForm()));
    Q_ASSERT(check);
}

CTaskActivity::CTaskActivity(const CTaskActivity &a) : CTask(a)
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
    m_CustomNumber = a.m_CustomNumber;
    m_Week = a.m_Week;
    m_Effective = a.m_Effective;
    m_UntilDate = a.m_UntilDate;
    m_LoopCount = a.m_LoopCount;
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

int CTaskActivity::GetDateEnd(CDate &date)
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

int CTaskActivity::SetCustomNumber(int n)
{
    m_CustomNumber = n;
    return 0;
}

int CTaskActivity::GetCustomNumber() const
{
    return m_CustomNumber;
}

int CTaskActivity::SetWeek(int w)
{
    m_Week = w;
    return 0;
}

int CTaskActivity::GetWeek() const
{
    return m_Week;
}

int CTaskActivity::SetEffective(_ENUM_EFFECTIVE e)
{
    m_Effective = e;
    return 0;
}

CTaskActivity::_ENUM_EFFECTIVE CTaskActivity::GetEffective() const
{
    return m_Effective;
}

int CTaskActivity::SetUntil(QDate d)
{
    m_UntilDate = d;
    return 0;
}

QDate CTaskActivity::GetUntil() const
{
    return m_UntilDate;
}

int CTaskActivity::SetLoopCount(int n)
{
    m_LoopCount = n;
    return 0;
}

int CTaskActivity::GetLoopCount() const
{
    return m_LoopCount;
}

int CTaskActivity::AddPrompt(int minute)
{
    _PROMPT p = {minute, false};
    m_Prompt.push_back(p);
    return 0;
}

int CTaskActivity::SetPrompt(const QString &prompt)
{
    m_Prompt.clear();
    QStringList s = prompt.split(",");
    foreach(QString p, s)
    {
        if(!p.isEmpty())
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

    nRet = CheckDate(QDate::currentDate());
    if(nRet)
        return nRet;
    
    if(m_tmEnd < QDateTime::currentDateTime().time())
        return 0;
    
    QVector<_PROMPT>::iterator it;
    for(it = m_Prompt.begin(); it != m_Prompt.end(); it++)
    {   
        if(it->bStop)
            continue;
        if(m_tmStart.addSecs(60 * it->nPrompt)
                < QDateTime::currentDateTime().time())
        {
            it->bStop = true;
            emit sigShowTopForm();
        }
    }
    return nRet;
}

bool CTaskActivity::End()
{
    //if(m_tmEnd < QDateTime::currentDateTime().time())
    //    return true;
    return false;
}

void CTaskActivity::slotShowTopForm()
{
    CFrmTopActivity* top = new CFrmTopActivity();
    if(top)
    {
        bool check = connect(this, SIGNAL(destroyed()),
                             top, SLOT(deleteLater()));
        Q_ASSERT(check);
        top->SetTask(this);
        top->SetPostion(CFrmTopActivity::RightBottom);
        top->setWindowTitle(GetTitle());
        QString szText = GetTitle();
        if(!GetContent().isEmpty())
            szText += "\n" + GetContent();
        top->SetText(szText);
        top->show();
    }
}

int CTaskActivity::CheckDate(const QDate &date)
{
    int nRet = -1;
    if(Lunar == GetTypeDate()) {
        if(GetRepeat() == EveryYear){
            int y, m, d;
            CLunarCalendar::GetLunar(date, y, m, d);
            qDebug() << "Lunar:" << y << m << d;
            if(m_dtStart.Month == m && m_dtStart.Day == d)
                return 0;
            return -1;
        }
        qDebug() << "Other isn't support";
        return -1;
    }
    
    switch (GetRepeat()) {
    case Once:
        {
            QDate s(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day);
            QDate end(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day);
            if(s <= date && date <= end)
                return 0;
        }
        break;
    case EveryDay:
        return 0;
    case Weekly:
        {
            if(date < QDate(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day))
                return -1;
            QDate s(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day);
            QDate e(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day);
            int sWeek = s.dayOfWeek();
            int eWeek = e.dayOfWeek();
            if(sWeek <= eWeek)
            {
                if(sWeek <= date.dayOfWeek() && date.dayOfWeek() <= eWeek)
                    return 0;
                else 
                    return -1;
            }
            if(sWeek <= date.dayOfWeek() && date.dayOfWeek() <= 7)
                return 0;
            else if (1<=date.dayOfWeek() && date.dayOfWeek() <= eWeek) {
                return 0;
            }
            return -1;
        }
    case Monthly:
        {
            if(date < QDate(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day))
                return -1;
            
            if(QDate(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day).addMonths(1)
                    < QDate(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day))
                return 0;
            
            if(m_dtStart.Day <= m_dtEnd.Day)
            {
                if(m_dtStart.Day <= date.day() && date.day() <= m_dtEnd.Day)
                    return 0;
                else
                    return -1;
            }
            else
            {
                 if(m_dtStart.Day <= date.day() || date.day() <= m_dtEnd.Day)
                     return 0;
                 else
                     return -1;
            }
        }
    case EveryYear:
        {
            if(date < QDate(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day))
                return -1;
            
            if(QDate(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day).addYears(1)
                    < QDate(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day))
                return 0;
            
            if(m_dtStart.Year == m_dtEnd.Year)
            {
                QDate s = GetValidDate(date.year(), m_dtStart.Month, m_dtStart.Day);
                QDate e = GetValidDate(date.year(), m_dtEnd.Month, m_dtEnd.Day);
                if(s <= date && date <= e)
                    return 0;
                else
                    return -1;
            }
            
            QDate s = GetValidDate(date.year(), m_dtStart.Month, m_dtStart.Day);
            QDate e = GetValidDate(date.year(), 12, 31);
            if(s <= date && date <= e)
                return 0;

            s = QDate(date.year(), 1, 1);
            e = GetValidDate(date.year(), m_dtEnd.Month, m_dtEnd.Day);
            if(s <= date && date <= e)
                return 0;
            
            return -1;
        }
    case CustomDay:
        {
            qint64 count = 0;
            QDate s(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day);
            QDate e(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day);
            if(date < s)
                return -1;
            count = s.daysTo(date) / m_CustomNumber;
            switch (m_Effective) {
            case Until:
                {
                    if(date > m_UntilDate)
                        return -1;
                }
            case LoopCount:
                {
                    if(count < 0 || count >= m_LoopCount)
                        return -1;
                }
            case Always:
                if(s.addDays(m_CustomNumber * count) <= date 
                        && date <= e.addDays(m_CustomNumber * count))
                    return 0;
                else
                    return -1;
            }
        }
        break;
    case CustomWeek:
        {
            qint64 count = 0;
            int number = m_CustomNumber * 7;
            QDate s(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day);
            QDate e(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day);
            if(date < s)
                return -1;
            count = s.daysTo(date) / number;
            switch (m_Effective) {
            case Until:
                {
                    if(date > m_UntilDate)
                        return -1;
                }
            case LoopCount:
                {
                    if(count < 0 || count >= m_LoopCount)
                        return -1;
                }
            case Always:
                if(m_Week)
                {
                    if(s.daysTo(e) > 7)
                    {
                        if(s.addDays(number * count) <= date 
                                && date <= e.addDays(number * count))
                        {
                            if(m_Week & 1 << (date.dayOfWeek() - 1))
                                return 0;
                            else
                                return -1;
                        }
                    }
                    else
                    {
                        e = s.addDays(7);
                        if(s.addDays(number * count) <= date 
                                && date <= e.addDays(number * count))
                            if(m_Week & 1 << (date.dayOfWeek() - 1))
                                return 0;
                            else
                                return -1;
                    }
                } else {
                    
                    if(s.addDays(number * count) <= date 
                            && date <= e.addDays(number * count))
                        return 0;
                    else
                        return -1;
                }
            }
        }
        break;
    case CustomMonth:
        {
            int count = 0;
            QDate s(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day);
            QDate e(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day);
            if(date < s)
                return -1;
            
            int countMonth = (date.year() - s.year()) * 12 + (date.month() - s.month());
            count = countMonth / m_CustomNumber;
            QDate start = s.addMonths(m_CustomNumber * count);
            QDate end = start.addDays(s.daysTo(e));
            end = GetValidDate(end.year(), end.month(), m_dtEnd.Day);

            int countMonth1 = (date.year() - e.year()) * 12 + (date.month() - e.month());
            int count1 = countMonth1 / m_CustomNumber;
            QDate end1 = e.addMonths(count1 * m_CustomNumber);
            QDate start1 = e.addDays(e.daysTo(s));
            start1 = GetValidDate(start1.year(), start1.month(), m_dtStart.Day);
            
            switch (m_Effective) {
            case Until:
                {
                    if(date > m_UntilDate)
                        return -1;
                }
            case LoopCount:
                {
                    if((count < 0 || count >= m_LoopCount)
                            && (count1 < 0 || count1 >= m_LoopCount))
                        return -1;
                }
            case Always:
                if(start <= date && date <= end)
                    return 0;
                
                if(start1 <= date && date <= end1)
                    return 0;
                return -1;
           }
        }
        break;
    case CustomYear:
        {
            int count = 0;
            QDate s(m_dtStart.Year, m_dtStart.Month, m_dtStart.Day);
            QDate e(m_dtEnd.Year, m_dtEnd.Month, m_dtEnd.Day);
            if(date < s)
                return -1;
            
            int countYear = date.year() - s.year();
            count = countYear / m_CustomNumber;
            QDate start = s.addYears(m_CustomNumber * count);
            QDate end = start.addDays(s.daysTo(e));
            end = GetValidDate(end.year(), m_dtEnd.Month, m_dtEnd.Day);
    
            int countYear1 = date.year() - e.year();
            int count1 = countYear1 / m_CustomNumber;
            QDate end1 = e.addYears(count1 * m_CustomNumber);
            QDate start1 = e.addDays(e.daysTo(s));
            start1 = GetValidDate(start1.year(), m_dtStart.Month, m_dtStart.Day);
            
            switch (m_Effective) {
            case Until:
                {
                    if(date > m_UntilDate)
                        return -1;
                }
            case LoopCount:
                {
                    if((count < 0 || count >= m_LoopCount)
                            && (count1 < 0 || count1 >= m_LoopCount))
                        return -1;
                }
            case Always:
                if(start <= date && date <= end)
                    return 0;
                
                if(start1 <= date && date <= end1)
                    return 0;
                return -1;
           }
        }
        break;
    default:
        qDebug() << "CTaskActivity::CheckDate: GetRepeat():" << GetRepeat() << " isn't know";
    }
    return nRet;
}

QDate CTaskActivity::GetValidDate(int year, int month, int day)
{
    QDate d(year, month, day);
    while(!d.isValid())
    {
        d = QDate(year, month, --day);
    }
    return d;
}
