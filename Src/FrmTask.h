#ifndef FRMTASK_H
#define FRMTASK_H

#include <QWidget>
#include "Task.h"

namespace Ui {
class CFrmTask;
}

class CFrmTask : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTask(QSharedPointer<CTask> task = QSharedPointer<CTask>(),
                      QWidget *parent = nullptr);
    ~CFrmTask();
    
    int SetTask(QSharedPointer<CTask> task);
    int ApplyTask();
    
private:
    Ui::CFrmTask *ui;
    
    QSharedPointer<CTask> m_Task;
};

#endif // FRMTASK_H
