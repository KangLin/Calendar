#include "TaskTrayIconPrompt.h"
#include <QDebug>

CTaskTrayIconPrompt::CTaskTrayIconPrompt(QObject *parent)
    : CTask(parent),
      m_TrayIcon(this)
{
    m_Icon = QIcon(":/icon/app");
    Init();
}

CTaskTrayIconPrompt::CTaskTrayIconPrompt(const QString szMessage,
                         const QString szTitle,
                         const QIcon icon,
                         int nInterval,
                         int nPromptInterval,
                         QObject *parent) 
    : CTask(nInterval, nPromptInterval, parent),
      m_TrayIcon(this)
{
    m_szMessage = szMessage;
    m_szTitle = szTitle;
    m_Icon = icon;
    Init();
}

int CTaskTrayIconPrompt::Init()
{
    SetName(tr("Tray icon prompt"));
    
    /*bool check = connect(&m_TrayIcon,
              SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
              SLOT(slotTrayIconActive(QSystemTrayIcon::ActivationReason)));
    Q_ASSERT(check);
    
    QAction* pExit = m_TrayIconMenu.addAction(
                QIcon(":/icons/close"),
                tr("Exit"));*/

    //m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(m_Icon);
    
    return 0;
}

void CTaskTrayIconPrompt::slotPrompt()
{
    if(QSystemTrayIcon::isSystemTrayAvailable())
    {   
        QTime tm(0, 0);
        tm = tm.addMSecs(Remaining());
        QString szRemaining = m_szMessage + "\n"
                + "Remaining: " + tm.toString("HH:mm:ss");
        if(Remaining() > 10000)
            m_TrayIcon.showMessage(m_szTitle, szRemaining);
        else if(Remaining() > 3000)
            m_TrayIcon.showMessage(m_szTitle, szRemaining, QSystemTrayIcon::Information, 1000);
        else
            qDebug() << "Title: " <<  m_szTitle << "Remaining: " << szRemaining;
    }
}

int CTaskTrayIconPrompt::onStart()
{
    int nRet = 0;
    if(QSystemTrayIcon::isSystemTrayAvailable())
    {
        m_TrayIcon.show();
        slotPrompt();
    }
    return nRet;
}

int CTaskTrayIconPrompt::onRun()
{
    int nRet = 0;
    m_TrayIcon.hide();
    return nRet;
}

void CTaskTrayIconPrompt::slotTrayIconActive(QSystemTrayIcon::ActivationReason reason)
{
}
