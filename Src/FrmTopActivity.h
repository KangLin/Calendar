#ifndef FRMTOPACTIVITY_H
#define FRMTOPACTIVITY_H

#include "FrmTop.h"
#include <QMenu>
#include <QTimer>
#include <QTime>
#include "TaskActivity.h"

class CFrmTopActivity : public CFrmTop
{
    Q_OBJECT
public:
    explicit CFrmTopActivity(QWidget *parent = nullptr);

    int StartTimer(int nMsec = 1000 * 60 * 5);
    int SetTask(CTaskActivity* task);
    
private Q_SLOTS:
    void slotDelay5Minute(bool checked);
    void slotDelayCustomize(bool checked);
    
private:
    QMenu m_Menu;
    QTimer m_Timer;
    QTime m_StartTime;
    
    int AddDelay(int nMinute);
    
    CTaskActivity* m_pTask;

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // FRMTOPACTIVITY_H
