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
    
    CTaskActivity::_ENUM_REPEAT m_Repeat;
    int GetNumber();
    void SetWeek(Qt::DayOfWeek week
               = static_cast<Qt::DayOfWeek>(QDate::currentDate().dayOfWeek()));
    QVector<int> GetWeek();
    
    QDate GetUntil();
    int GetCount();
    
private slots:
    void on_rbWeeks_clicked();
    void on_rbDays_clicked();
    void on_rbMonths_clicked();
    void on_rbYears_clicked();
    void on_rbAlways_clicked();
    void on_rbUntil_clicked();
    void on_rbCount_clicked();
    
    void on_cmbType_currentIndexChanged(int index);
    
private:
    Ui::CFrmCustomActivity *ui;
};

#endif // FRMCUSTOMACTIVITY_H
