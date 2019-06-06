#ifndef FRMACTIVITY_H
#define FRMACTIVITY_H

#include <QDialog>
#include <QSharedPointer>
#include <QStandardItemModel>
#include "TaskActivity.h"

namespace Ui {
class CDlgTaskActivity;
}

class CDlgTaskActivity : public QDialog
{
    Q_OBJECT

public:
    explicit CDlgTaskActivity(CTaskActivity* task,
                              QWidget *parent = nullptr);
    virtual ~CDlgTaskActivity() override;

    int SetTask(CTaskActivity* task);
    CTaskActivity* GetTask();
    int ApplyTask();

private:
    int Init();
    
private:
    Ui::CDlgTaskActivity *ui;
    CTaskActivity* m_Task;
    QStandardItemModel *m_pModelPrompt;
    CTaskActivity::_TYPE_DATE m_TypeDate;
    CTaskActivity::_ENUM_REPEAT m_Repeat;
    int m_CustomNumber;
    int m_Week;
    CTaskActivity::_ENUM_EFFECTIVE m_Effective;
    QDate m_UntilDate;
    int m_LoopCount;
    
protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void hideEvent(QHideEvent *event) override;

private slots:
    void on_rbSolar_clicked();
    void on_rbLunar_clicked();
    void on_rbOnce_clicked();
    void on_rbEveryDay_clicked();
    void on_rbWeekly_clicked();
    void on_rbMonthly_clicked();
    void on_rbEveryYear_clicked();
    void on_rbCustom_clicked();
    void on_pbPromptAdd_clicked();
    void on_pbPromptRemove_clicked();
    void on_dtStart_dateChanged(const QDate &date);
    void on_dtEnd_dateChanged(const QDate &date);
    void on_tmStart_timeChanged(const QTime &time);
    void on_tmEnd_timeChanged(const QTime &time);
};

#endif // FRMACTIVITY_H
