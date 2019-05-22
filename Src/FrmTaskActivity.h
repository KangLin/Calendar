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
    explicit CFrmTaskActivity(QSharedPointer<CTaskActivity> task,
                              QWidget *parent = nullptr);
    virtual ~CFrmTaskActivity() override;

    int SetTask(QSharedPointer<CTaskActivity> task);
    int ApplyTask();

private:
    Ui::CFrmTaskActivity *ui;
    QSharedPointer<CTaskActivity> m_Task;

protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;
};

#endif // FRMACTIVITY_H
