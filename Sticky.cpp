#include "Sticky.h"

static int gTypeCSticky = qRegisterMetaType<CSticky>();
CSticky::CSticky(QObject *parent) : QObject(parent)
{
    m_bWindowHide = false;
    m_Policy = normal;
}

CSticky::CSticky(const CSticky &s)
{
    m_bWindowHide = s.m_bWindowHide;
    m_Policy = s.m_Policy;
    m_WindowRect = s.m_WindowRect;
    m_bWindowHide = s.m_bWindowHide;
    m_szContent = s.m_szContent;
    m_Time = s.m_Time;
}

int CSticky::SetContent(const QString &szContent)
{
    m_szContent = szContent;
    m_Time = QDateTime::currentDateTime();
    emit sigUpdate();
    return 0;
}

QString CSticky::GetContent()
{
    return m_szContent;
}

int CSticky::SetWindowRect(const QRect &rect)
{
    m_WindowRect = rect;
    emit sigUpdate();
    return 0;
}

QRect CSticky::GetWindowRect()
{
    return m_WindowRect;
}

int CSticky::SetModifyTime()
{
    m_Time = QDateTime::currentDateTime();
    emit sigUpdate();
    return 0;
}

QDateTime CSticky::GetModifyTime()
{
    return m_Time;
}

CSticky::POLICY CSticky::GetPolicy()
{
    return m_Policy;
}

int CSticky::SetPolicy(POLICY p)
{
    m_Policy = p;
    emit sigUpdate();
    return 0;
}

int CSticky::SetWindowHide(bool bHide)
{
    m_bWindowHide = bHide;
    emit sigUpdate();
    return 0;
}

bool CSticky::GetWindowHide()
{
    return m_bWindowHide;
}

#ifndef QT_NO_DATASTREAM
QDataStream& operator<<(QDataStream &d, const CSticky &s)
{
    d << (int)s.m_Policy;
    return d << s.m_bWindowHide << s.m_WindowRect 
             << s.m_Time << s.m_szContent;
}

QDataStream& operator>>(QDataStream &d, CSticky &s)
{
    int p;
    d >> p;
    s.m_Policy = (CSticky::POLICY)p;
    d >> s.m_bWindowHide >> s.m_WindowRect >> s.m_Time >> s.m_szContent;
    return d;
}
#endif
