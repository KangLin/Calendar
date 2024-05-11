#ifndef DLGOPTION_H
#define DLGOPTION_H

#include <QDialog>

namespace Ui {
class CDlgOption;
}

class CDlgOption : public QDialog
{
    Q_OBJECT
    
public:
    explicit CDlgOption(QWidget *parent = nullptr);
    ~CDlgOption();
    
private slots:
    void on_buttonBox_accepted();
    void on_cbAutomation_toggled(bool checked);

private:
    Ui::CDlgOption *ui;
};

#endif // DLGOPTION_H
