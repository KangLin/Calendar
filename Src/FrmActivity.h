#ifndef FRMACTIVITY_H
#define FRMACTIVITY_H

#include <QWidget>
#include "Activity.h"

namespace Ui {
class CFrmActivity;
}

class CFrmActivity : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmActivity(QWidget *parent = nullptr);
    virtual ~CFrmActivity() override;
    
private:
    Ui::CFrmActivity *ui;
    CActivity m_Activity;
    
    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // FRMACTIVITY_H
