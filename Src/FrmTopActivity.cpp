// 作者：康林 <kl222@126.com>

#include "FrmTopActivity.h"
#include <QInputDialog>
#include "DlgContainer.h"
#include "DlgTaskActivity.h"

CFrmTopActivity::CFrmTopActivity(QWidget *parent): CFrmTop(parent)
{
    Qt::WindowFlags flags = windowFlags()
            & ~(Qt::FramelessWindowHint |
                Qt::X11BypassWindowManagerHint |  //这个标志是在x11下有用,查看帮助QWidget::showFullScreen()
                Qt::Tool |
                //Qt::WindowStaysOnTopHint |
                Qt::CustomizeWindowHint
                );
    setWindowFlags(flags);
    setAttribute(Qt::WA_DeleteOnClose, true);
    
    m_Menu.addAction(QIcon(":/icon/Close"), tr("Close"),
                     this, SLOT(deleteLater()));
    m_Menu.addAction(tr("Delay 5 Minute"),
                  this, SLOT(slotDelay5Minute(bool)));
    m_Menu.addAction(tr("Customize delay"),
                     this, SLOT(slotDelayCustomize(bool)));
    SetPopupMenu(&m_Menu);
    
    bool check = connect(&m_Timer, SIGNAL(timeout()), this, SLOT(deleteLater()));
    Q_ASSERT(check);
    StartTimer();
}

int CFrmTopActivity::StartTimer(int nMsec)
{
    m_StartTime = QTime::currentTime();
    m_Timer.start(nMsec);
    m_StartTime.start();
    return 0;
}

void CFrmTopActivity::slotDelay5Minute(bool checked)
{
    Q_UNUSED(checked);
    AddDelay(5);
}

void CFrmTopActivity::slotDelayCustomize(bool checked)
{
    Q_UNUSED(checked);
    bool ok = false;
    int n = QInputDialog::getInt(this,
                                 tr("Customize delay"),
                                 tr("Delay minute"),
                                 10,
                                 1,
                                 60 * 60 * 24,
                                 1,
                                 &ok);
    if(!ok)
        return;
    AddDelay(n);
}

int CFrmTopActivity::AddDelay(int nMinute)
{
    StartTimer((nMinute + m_Timer.interval() - m_StartTime.elapsed()) * 60 * 1000);
    return 0;
}

int CFrmTopActivity::SetTask(CTaskActivity *task)
{
    m_pTask = task;
    return 0;
}

void CFrmTopActivity::mouseReleaseEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button())
    {
        CDlgTaskActivity* pTask = new CDlgTaskActivity(m_pTask);
        CDlgContainer dlg;
        dlg.SetWidget(pTask);
        bool check = connect(this, SIGNAL(destroyed()),
                             &dlg, SLOT(reject()));
        Q_ASSERT(check);
        if(QDialog::Accepted == dlg.ExtendExec())
        {
            pTask->ApplyTask();
        }
        close();
    }
}
