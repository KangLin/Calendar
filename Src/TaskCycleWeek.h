#ifndef TASKCYCLEWEEK_H
#define TASKCYCLEWEEK_H

#include <QObject>
#include "Task.h"

class CTaskCycleWeek : public CTask
{
    Q_OBJECT
public:
    explicit CTaskCycleWeek(QObject *parent = nullptr);
    
signals:
    
public slots:
};

#endif // TASKCYCLEWEEK_H
