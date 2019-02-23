#ifndef FRMTASKSLIST_H
#define FRMTASKSLIST_H

#include <QStandardItemModel>
#include <QWidget>
#include <QCloseEvent>
#include "TasksList.h"

namespace Ui {
class CFrmTasksList;
}

class CFrmTasksList : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTasksList(QWidget *parent = nullptr);
    ~CFrmTasksList();

public Q_SLOTS:
    void slotNew();
    void slotRemove();
    void slotLoad();
    void slotSaveAs();
    void slotRefresh();
    
private Q_SLOTS:
    void on_lvTasks_clicked(const QModelIndex &index);
    void on_lvTasks_indexesMoved(const QModelIndexList &indexes);

protected:
    virtual void closeEvent(QCloseEvent *event);
    
private:
    int Init();
    int Load(QString szFile = QString());
    
private:
    Ui::CFrmTasksList *ui;
    
    CTasksList m_TasksList;
    QStandardItemModel m_Model;
};

#endif // FRMTASKSLIST_H
