#ifndef FRMTASKSLIST_H
#define FRMTASKSLIST_H

#include <QStandardItemModel>
#include <QWidget>
#include "TasksList.h"

namespace Ui {
class CFrmTasksList;
}

class CFrmTasksList : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTasksList(QWidget *parent = nullptr);
    explicit CFrmTasksList(CTasksList *pTasks, QWidget *parent = nullptr);
    ~CFrmTasksList();
    
public Q_SLOTS:
    void slotNew();
    void slotRemove();
    
private Q_SLOTS:
    void on_lvTasks_clicked(const QModelIndex &index);
    
    void on_lvTasks_indexesMoved(const QModelIndexList &indexes);
    
private:
    int Init();

private:
    Ui::CFrmTasksList *ui;
    CTasksList *m_TasksList;
    QStandardItemModel m_Model;
};

#endif // FRMTASKSLIST_H
