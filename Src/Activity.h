#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QVector>

class CActivity : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ GetId WRITE SetId)
    Q_PROPERTY(QString title READ GetTitle WRITE SetTitle)
    Q_PROPERTY(QString description READ GetDescription WRITE SetDescription)
    Q_PROPERTY(QString place READ GetPlace WRITE SetPlace)
    Q_PROPERTY(QString account READ GetAccount WRITE SetAccount)
    Q_PROPERTY(_TYPE_DATE typeDate READ GetTypeDate WRITE SetTypeDate)
    Q_PROPERTY(_ENUM_REPEAT repeat READ GetRepeat WRITE SetRepeat)
    
public:
    explicit CActivity(QObject *parent = nullptr);
    CActivity(const CActivity& a);
    virtual ~CActivity();
    
    Q_INVOKABLE int SetId(int id);
    Q_INVOKABLE int GetId();
    Q_INVOKABLE int SetTitle(const QString& szTitle);
    Q_INVOKABLE QString GetTitle() const;
    Q_INVOKABLE int SetDescription(const QString& szDescription);
    Q_INVOKABLE QString GetDescription() const;
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
    CDate GetDateStart() const;
    int SetDateEnd(int year, int month, int day);
    CDate GetDateEnd() const;
    enum _ENUM_REPEAT
    {
        Once = 0,
        EveryDay = 1,
        Weekly = 2,
        Monthly = 3,
        EveryYear = 4,
        Custom = 100
    };
    Q_ENUM(_ENUM_REPEAT)
    Q_INVOKABLE int SetRepeat(_ENUM_REPEAT repeat);
    Q_INVOKABLE _ENUM_REPEAT GetRepeat() const;
    
    int AddPrompt(int minute = -5);
    
    virtual int onCheck();
    
private:
    virtual int onPrompt();
    virtual int onCheckOnce();
    
public Q_SLOTS:
    
private:
    int m_nId;
    QString m_szTitle;
    QString m_szDescription;
    QString m_szPlace;
    QString m_szAccount;
    _TYPE_DATE m_tyDate;
    struct CDate m_dtStart, m_dtEnd;
    QTime m_tmStart, m_tmEnd;
    _ENUM_REPEAT m_Repeat;
    
    struct _PROMPT
    {
        int nPrompt;
        bool bStop;
    };
    QVector<_PROMPT> m_Prompt; //Sort ascending. Units: minutes
};

Q_DECLARE_METATYPE(CActivity)

#endif // ACTIVITY_H
