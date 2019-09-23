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
    Q_PROPERTY(QDateTime time READ GetModifyTime)
    Q_PROPERTY(QDateTime time READ GetCreateTime)
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
    int SetWindows(const QPoint &pos, const QSize &size);
    int GetWindows(QPoint &pos, QSize &size);
    int SetWindowHide(bool bHide = true);
    bool GetWindowHide();
    QDateTime GetModifyTime();
    QDateTime GetCreateTime();

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
    int SetCreateTime();
    
private:
    QString m_szContent; //include QTextEdit::toHtml
    QString m_szText;    //include QTextEdit::toPlainText
    QPoint m_WindowsPos;
    QSize m_WindowSize;
    bool m_bWindowHide;
    QDateTime m_tmModify, m_tmCreate;
    POLICY m_Policy;
    qint8 m_nVersion;
};

Q_DECLARE_METATYPE(CSticky)
#endif // STICKY_H
