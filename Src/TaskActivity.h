// 作者：康林 <kl222@126.com>

#ifndef TASKACTIVITY_H
#define TASKACTIVITY_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QVector>
#include "Task.h"

class CTaskActivity : public CTask
{
    Q_OBJECT
    Q_PROPERTY(QString place READ GetPlace WRITE SetPlace)
    Q_PROPERTY(QString account READ GetAccount WRITE SetAccount)
    Q_PROPERTY(_TYPE_DATE typeDate READ GetTypeDate WRITE SetTypeDate)
    Q_PROPERTY(QString dateStart READ GetDateStart WRITE SetDateStart)
    Q_PROPERTY(QTime tmStart READ GetTimeStart WRITE SetTimeStart)
    Q_PROPERTY(QString dateEnd READ GetDateEnd WRITE SetDateEnd)
    Q_PROPERTY(QTime tmEnd READ GetTimeEnd WRITE SetTimeEnd)
    Q_PROPERTY(_ENUM_REPEAT repeat READ GetRepeat WRITE SetRepeat)
    Q_PROPERTY(QString prompt READ GetPrompt WRITE SetPrompt)
    Q_PROPERTY(int customNumber READ GetCustomNumber WRITE SetCustomNumber)
    Q_PROPERTY(int week READ GetWeek WRITE SetWeek)
    Q_PROPERTY(_ENUM_EFFECTIVE Effective READ GetEffective WRITE SetEffective)
    Q_PROPERTY(QDate until READ GetUntil WRITE SetUntil)
    Q_PROPERTY(int loopCount READ GetLoopCount WRITE SetLoopCount)
    
public:
    explicit CTaskActivity(QObject *parent = nullptr);
    CTaskActivity(const CTaskActivity& a);
    virtual ~CTaskActivity();
    
    Q_INVOKABLE virtual QString GetDescription() const;
    Q_INVOKABLE int SetPlace(const QString& szPlace);
    Q_INVOKABLE QString GetPlace() const;
    Q_INVOKABLE int SetAccount(const QString& szAccount);
    Q_INVOKABLE QString GetAccount() const;
    
    enum _TYPE_DATE
    {
        Solar = 0,
        Lunar = 1      
    };
    Q_ENUM(_TYPE_DATE)
    Q_INVOKABLE int SetTypeDate(_TYPE_DATE type);
    Q_INVOKABLE _TYPE_DATE GetTypeDate() const;
    struct CDate
    {
        int Year;
        int Month;
        int Day;
    };
    int SetDateStart(int year, int month, int day);
    int GetDateStart(CDate &date);
    Q_INVOKABLE int SetDateStart(QString date);
    Q_INVOKABLE QString GetDateStart();
    Q_INVOKABLE int SetTimeStart(QTime t);
    Q_INVOKABLE QTime GetTimeStart();
    int SetDateEnd(int year, int month, int day);
    int GetDateEnd(CDate &date);
    Q_INVOKABLE int SetDateEnd(QString date);
    Q_INVOKABLE QString GetDateEnd();
    Q_INVOKABLE int SetTimeEnd(QTime t);
    Q_INVOKABLE QTime GetTimeEnd();
    enum _ENUM_REPEAT
    {
        Once,
        EveryDay,
        Weekly,
        Monthly,
        EveryYear,
        CustomYear,
        CustomMonth,
        CustomWeek,
        CustomDay
    };
    Q_ENUM(_ENUM_REPEAT)
    Q_INVOKABLE int SetRepeat(CTaskActivity::_ENUM_REPEAT repeat);
    Q_INVOKABLE _ENUM_REPEAT GetRepeat() const;
    Q_INVOKABLE int SetCustomNumber(int n);
    Q_INVOKABLE int GetCustomNumber() const; 
    Q_INVOKABLE int SetWeek(int w);
    Q_INVOKABLE int GetWeek() const;
    enum _ENUM_EFFECTIVE
    {
        Always,
        Until,
        LoopCount
    };
    Q_ENUM(_ENUM_EFFECTIVE)
    Q_INVOKABLE int SetEffective(_ENUM_EFFECTIVE e);
    Q_INVOKABLE _ENUM_EFFECTIVE GetEffective() const;
    Q_INVOKABLE int SetUntil(QDate d);
    Q_INVOKABLE QDate GetUntil() const;
    Q_INVOKABLE int SetLoopCount(int n);
    Q_INVOKABLE int GetLoopCount() const;
    
    /**
     * @brief AddPrompt
     * @param minute
     * @return 
     */     
    int AddPrompt(int minute = -5);
    /**
     * @brief GetPrompt
     * @return QString
     * The time in minutes relative to StartTime. Separated by ","
     */
    Q_INVOKABLE QString GetPrompt();
    Q_INVOKABLE int SetPrompt(const QString& prompt);
    
    /**
     * @brief Start task, Initialize here. Note: first clean
     * @return 
     */
    virtual int Start();
    /**
     * @brief Check if the task can run
     * @return : 0, The task is finished. other, The task is continue.
     */
    virtual int Check();
    /**
     * @brief End
     * @return : true: The task is remove from tasks list
     *           false: The task remain in tasks list 
     */
    virtual bool End();

    virtual int CheckDate(const QDate &date);
    
private:
    virtual int onPrompt();
    QDate GetValidDate(int year, int month, int day);
    
public Q_SLOTS:
    virtual void slotShowTopForm();
Q_SIGNALS:
    void sigShowTopForm();
    
private:
    QString m_szPlace;
    QString m_szAccount;
    _TYPE_DATE m_tyDate;
    struct CDate m_dtStart, m_dtEnd;
    QTime m_tmStart, m_tmEnd;
    _ENUM_REPEAT m_Repeat;
    int m_CustomNumber;
    int m_Week;
    _ENUM_EFFECTIVE m_Effective;
    QDate m_UntilDate;
    int m_LoopCount;
    
    struct _PROMPT
    {
        int nPrompt;
        bool bStop;
    };
    QVector<_PROMPT> m_Prompt; //Sort ascending. Units: minutes
};

Q_DECLARE_METATYPE(CTaskActivity)
Q_DECLARE_METATYPE(CTaskActivity::CDate)

#endif // TASKACTIVITY_H
