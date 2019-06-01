#ifndef FRMCUSTOMACTIVITY_H
#define FRMCUSTOMACTIVITY_H

#include <QWidget>
#include <QDate>
#include <QVector>

#include "TaskActivity.h"

namespace Ui {
class CFrmCustomActivity;
}

class CFrmCustomActivity : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmCustomActivity(QWidget *parent = nullptr);
    ~CFrmCustomActivity();
    
    int SetRepeat(CTaskActivity::_ENUM_REPEAT r);
    CTaskActivity::_ENUM_REPEAT GetRepeat() const;
    int SetNumber(int n);
    int GetNumber() const;
    void SetWeek(int w);
    int GetWeek() const;
    int SetEffective(CTaskActivity::_ENUM_EFFECTIVE e);
    CTaskActivity::_ENUM_EFFECTIVE GetEffective() const;
    int SetUntil(QDate d);
    QDate GetUntil();
    int SetLoopCount(int n);
    int GetLoopCount();
    
private slots:
    void on_rbWeeks_clicked();
    void on_rbDays_clicked();
    void on_rbMonths_clicked();
    void on_rbYears_clicked();
    void on_rbAlways_clicked();
    void on_rbUntil_clicked();
    void on_rbLoopCount_clicked();
    
    void on_cmbType_currentIndexChanged(int index);
    
private:
    Ui::CFrmCustomActivity *ui;
    
    CTaskActivity::_ENUM_REPEAT m_Repeat;
};

#endif // FRMCUSTOMACTIVITY_H
