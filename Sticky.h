#ifndef STICKY_H
#define STICKY_H

#include <QObject>
#include <QRect>
#include <QDateTime>
#include <QDataStream>

class CSticky : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString content READ GetContent WRITE SetContent)
    Q_PROPERTY(QString text READ GetText WRITE SetText)
    Q_PROPERTY(QRect windowRect READ GetWindowRect WRITE SetWindowRect)
    Q_PROPERTY(QDateTime time READ GetModifyTime) 
    Q_PROPERTY(bool windowHide READ GetWindowHide WRITE SetWindowHide)
public:
    explicit CSticky(QObject *parent = nullptr);
    CSticky(const CSticky &s);
    virtual ~CSticky();
    
#ifndef QT_NO_DATASTREAM
    friend QDataStream& operator<<(QDataStream &d, const CSticky &s);
    friend QDataStream& operator>>(QDataStream &d, CSticky &s);
#endif
    
    int SetContent(const QString &szContent);
    QString GetContent();
    int SetText(const QString &szText);
    QString GetText();
    int SetWindowRect(const QRect &rect);
    QRect GetWindowRect();
    int SetWindowHide(bool bHide = true);
    bool GetWindowHide();
    QDateTime GetModifyTime();
    
    enum POLICY
    {
        normal,
        priority,
        delay
    };
    int SetPolicy(POLICY p);
    POLICY GetPolicy();
    
Q_SIGNALS:
    void sigRemove(QSharedPointer<CSticky>);
    void sigUpdate();
    
private:
    int SetModifyTime();
    
private:
    QString m_szContent;
    QString m_szText;
    QRect m_WindowRect;
    bool m_bWindowHide;
    QDateTime m_Time;
    POLICY m_Policy;
};

Q_DECLARE_METATYPE(CSticky)
#endif // STICKY_H
