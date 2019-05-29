#ifndef FRMTOPACTIVITY_H
#define FRMTOPACTIVITY_H

#include "FrmTop.h"
#include <QMenu>
#include <QTimer>
#include <QTime>

class CFrmTopActivity : public CFrmTop
{
    Q_OBJECT
public:
    explicit CFrmTopActivity(QWidget *parent = nullptr);

    int StartTimer(int nMsec = 1000 * 60 * 5);
    
private Q_SLOTS:
    void slotDelay5Minute(bool checked);
    void slotDelayCustomize(bool checked);
    
private:
    QMenu m_Menu;
    QTimer m_Timer;
    QTime m_StartTime;
    
    int AddDelay(int nMinute);
};

#endif // FRMTOPACTIVITY_H
