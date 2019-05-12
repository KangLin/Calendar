#ifndef FRMACTIVITY_H
#define FRMACTIVITY_H

#include <QWidget>
#include <QSharedPointer>
#include "TaskActivity.h"

namespace Ui {
class CFrmTaskActivity;
}

class CFrmTaskActivity : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTaskActivity(QWidget *parent = nullptr);
    explicit CFrmTaskActivity(CTaskActivity* task,
                              QWidget *parent = nullptr);
    virtual ~CFrmTaskActivity() override;
    
    int SetTask(CTaskActivity *task);
    int ApplyTask();

private:
    Ui::CFrmTaskActivity *ui;
    CTaskActivity* m_Task;
    
    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // FRMACTIVITY_H
