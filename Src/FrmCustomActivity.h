#ifndef FRMCUSTOMACTIVITY_H
#define FRMCUSTOMACTIVITY_H

#include <QWidget>

namespace Ui {
class CFrmCustomActivity;
}

class CFrmCustomActivity : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmCustomActivity(QWidget *parent = nullptr);
    ~CFrmCustomActivity();
    
private slots:
    void on_rbWeeks_clicked();
    
    void on_rbDays_clicked();
    
    void on_rbMonths_clicked();
    
    void on_rbYears_clicked();
    
private:
    Ui::CFrmCustomActivity *ui;
};

#endif // FRMCUSTOMACTIVITY_H
