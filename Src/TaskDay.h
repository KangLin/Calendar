#ifndef TASKDAY_H
#define TASKDAY_H

#include <QObject>
#include "TaskPromptDelay.h"

class CTaskDay : public CTaskPromptDelay
{
    Q_OBJECT
public:
    explicit CTaskDay(QObject *parent = nullptr);
    
    virtual int Start() override;
    virtual int onStart() override;
    virtual int onRun() override;
    
public slots:
    
private:
    int Init();
    
    QDateTime m_StartTime, m_EndTime;
    QDateTime m_ActualStartTime, m_ActualEndTime;

};

#endif // TASKDAY_H
