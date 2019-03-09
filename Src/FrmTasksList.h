#ifndef FRMTASKSLIST_H
#define FRMTASKSLIST_H

#include <QStandardItemModel>
#include <QWidget>
#include <QCloseEvent>
#include <QToolBar>
#include <QListView>
#include "TasksList.h"
#include "FrmTasks.h"
#include "tasks_export.h"

namespace Ui {
class CFrmTasksList;
}

class TASKS_EXPORT CFrmTasksList : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTasksList(QWidget *parent = nullptr);
    virtual ~CFrmTasksList();

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
    CFrmTasks m_FrmTasks;
    QStandardItemModel m_Model;
    QListView m_lvTasks;
    QToolBar m_ToolBar;
};

#endif // FRMTASKSLIST_H
