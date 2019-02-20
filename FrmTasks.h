#ifndef FRMTASKS_H
#define FRMTASKS_H

#include <QWidget>
#include "Tasks.h"

namespace Ui {
class CFrmTasks;
}

class CFrmTasks : public QWidget
{
    Q_OBJECT

public:
    explicit CFrmTasks(QSharedPointer<CTasks> tasks = QSharedPointer<CTasks>(),
                       bool readOnly = false,
                       QWidget *parent = nullptr);
    virtual ~CFrmTasks();

    int SetTasks(QSharedPointer<CTasks> tasks = QSharedPointer<CTasks>());

Q_SIGNALS:
    void Change();
    
private Q_SLOTS:
    void on_pbAdd_clicked();
    void on_pbRemove_clicked();
    void on_pbClose_clicked();
    void on_vsLength_valueChanged(int value);
    void on_pbPrevious_clicked();
    void on_pbNext_clicked();
    void on_pbApply_clicked();
    
protected:
    virtual void closeEvent(QCloseEvent *event);
    
private:
    int SetTask(QSharedPointer<CTask> task);
    int InitTaskComboBox();
    int SetSlider(int value);
    
private:
    Ui::CFrmTasks *ui;
    QSharedPointer<CTasks> m_Tasks;
};

#endif // FRMTASKS_H
