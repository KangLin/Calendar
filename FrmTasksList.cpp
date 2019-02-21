#include "FrmTasksList.h"
#include "ui_FrmTasksList.h"
#include <QModelIndex>

CFrmTasksList::CFrmTasksList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTasksList)
{
    ui->setupUi(this);
    m_TasksList = nullptr;
    Init();
}

CFrmTasksList::CFrmTasksList(CTasksList* pTasks, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::CFrmTasksList)
{
    ui->setupUi(this);
    m_TasksList = pTasks;
    Init();
}

CFrmTasksList::~CFrmTasksList()
{
    delete ui;
}

int CFrmTasksList::Init()
{
    int nRet = 0;
    ui->tasks->hide();
    ui->lvTasks->setModel(&m_Model);
    
    if(nullptr == m_TasksList)
        return -1;
    
    int nIndex = 0;
    while(QSharedPointer<CTasks> p = m_TasksList->Get(nIndex++))
    {
        QStandardItem *title = new QStandardItem(p->GetTitle());
        title->setToolTip(p->GetContent());
        m_Model.appendRow(title);
    }
    ui->lvTasks->setCurrentIndex(m_Model.index(0, 0));
    return nRet;
}

void CFrmTasksList::on_lvTasks_clicked(const QModelIndex &index)
{
    QSharedPointer<CTasks> p = m_TasksList->Get(index.row());
    if(nullptr == p)
        return;
    ui->tasks->SetTasks(p);
    ui->tasks->show();
}

void CFrmTasksList::slotNew()
{
    QSharedPointer<CTasks> tasks(new CTasks());
    tasks->SetTitle(tr("New tasks"));
    m_TasksList->Add(tasks);
    QSharedPointer<CTask> task(new CTask());
    task->SetTitle(tr("New task"));
    task->SetContent(tr("If the task is not you need, please select a task from combox, new it, and remove the task."));
    tasks->Add(task);
    QStandardItem *title = new QStandardItem(tasks->GetTitle());
    title->setToolTip(tasks->GetContent());
    m_Model.appendRow(title);
    ui->lvTasks->setCurrentIndex(m_Model.index(m_Model.rowCount() - 1, 0));
    on_lvTasks_clicked(ui->lvTasks->currentIndex());
}

void CFrmTasksList::slotRemove()
{
    m_TasksList->Remove(m_TasksList->Get(ui->lvTasks->currentIndex().row()));
    m_Model.removeRow(ui->lvTasks->currentIndex().row());
    on_lvTasks_clicked(ui->lvTasks->currentIndex());
}

void CFrmTasksList::on_lvTasks_indexesMoved(const QModelIndexList &indexes)
{
    QSharedPointer<CTasks> p = m_TasksList->Get(indexes.at(0).row());
    if(nullptr == p)
        return;
    ui->tasks->SetTasks(p);
    ui->tasks->show();
}
