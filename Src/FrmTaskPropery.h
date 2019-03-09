#ifndef FRMTASKPROPERY_H
#define FRMTASKPROPERY_H

#include <QWidget>
#include <QStandardItemModel>
#include "TasksList.h"
#include "ViewTaskProperty.h"

namespace Ui {
class CFrmTaskProperty;
}

class CFrmTaskProperty : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTaskProperty(CTasksList *plstTasks, QWidget *parent = nullptr);
    virtual ~CFrmTaskProperty();
    
private slots:
    void on_pbSave_clicked();
    void on_pbCancle_clicked();
    
private:
    Ui::CFrmTaskProperty *ui;

    CTasksList *m_plstTasks;
};

#endif // FRMTASKPROPERY_H
