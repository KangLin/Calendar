// 作者：康林 <kl222@126.com>

#include "FrmTasksList.h"
#include "TaskPromptDelay.h"
#include "ui_FrmTasksList.h"
#include "RabbitCommonDir.h"

#include <QModelIndex>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

CFrmTasksList::CFrmTasksList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTasksList)
{
    ui->setupUi(this);
    Init();
}

CFrmTasksList::~CFrmTasksList()
{
    delete ui;
}

int CFrmTasksList::Init()
{
    int nRet = 0;
    this->layout()->addWidget(&m_ToolBar);
    this->layout()->addWidget(&m_lvTasks);
    this->layout()->addWidget(&m_FrmTasks);
    
    m_lvTasks.setModel(&m_Model);
    m_FrmTasks.hide();
    bool check = connect(&m_FrmTasks, SIGNAL(Changed()),
                         this, SLOT(slotSaveAs()));
    Q_ASSERT(check);
    check = connect(&m_lvTasks, SIGNAL(doubleClicked(const QModelIndex)),
                         this, SLOT(on_lvTasks_clicked(const QModelIndex)));
    Q_ASSERT(check);
    m_ToolBar.addAction(ui->actionLoad_L);
    m_ToolBar.addAction(ui->actionSaveAs_S);
    m_ToolBar.addSeparator();
    m_ToolBar.addAction(ui->actionNew_N);
    m_ToolBar.addAction(ui->actionRemove_R);
    m_ToolBar.addAction(ui->actionRefresh_F);
    check = connect(ui->actionNew_N, SIGNAL(triggered()),
                         this, SLOT(slotNew()));
    Q_ASSERT(check);
    check = connect(ui->actionRemove_R, SIGNAL(triggered()),
                    this, SLOT(slotRemove()));
    Q_ASSERT(check);
    check = connect(ui->actionLoad_L, SIGNAL(triggered()),
                    this, SLOT(slotLoad()));
    Q_ASSERT(check);
    check = connect(ui->actionSaveAs_S, SIGNAL(triggered()),
                    this, SLOT(slotSaveAs()));
    Q_ASSERT(check);
    check = connect(ui->actionRefresh_F, SIGNAL(triggered()),
                    this, SLOT(slotRefresh()));
    Q_ASSERT(check);
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    QString szFile = set.value("TasksList").toString();
    nRet = Load(szFile);
    
    return nRet;
}

void CFrmTasksList::slotRefresh()
{
    m_Model.clear();
    CTasksList::POSITION pos = m_TasksList.GetFirst();
    while(QSharedPointer<CTasks> p = m_TasksList.GetNext(pos))
    {
        QStandardItem *pItem = new QStandardItem(p->GetIcon(), p->GetTitle());
        if(!pItem) return;
        pItem->setToolTip(p->GetContent());
        pItem->setData(p->GetId());
        pItem->setCheckable(true);
        if(p->GetEnable())
            pItem->setCheckState(Qt::Checked);
        m_Model.appendRow(pItem);
    }
    m_lvTasks.setCurrentIndex(m_Model.index(0, 0));
    //TODO: 
    m_TasksList.Start();
}

int CFrmTasksList::Load(QString szFile)
{
    int nRet = m_TasksList.LoadSettings(szFile);
    if(nRet)
        return nRet;
    
    slotRefresh();
    
    return 0; //m_TasksList.Start();
}

void CFrmTasksList::slotLoad()
{
    QString szFile = QFileDialog::getOpenFileName(this,
                       tr("Load"), QString(), tr("xml(*.xml);;All files(*.*)"));
    Load(szFile);
}

void CFrmTasksList::slotSaveAs()
{
    QString szFile = QFileDialog::getSaveFileName(this,
                                         tr("Save as ..."), QString(), "*.xml");
    if(szFile.lastIndexOf(".xml") == -1)
        szFile += ".xml";
    
    int nRet = m_TasksList.SaveSettings(szFile);
    if(0 == nRet)
    {
        QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                      QSettings::IniFormat);
        set.setValue("TasksList", szFile);
    }
    slotRefresh();
}

void CFrmTasksList::on_lvTasks_clicked(const QModelIndex &index)
{
    QStandardItem* pItem = m_Model.item(m_lvTasks.currentIndex().row());
    if(!pItem)
    {
        m_FrmTasks.SetTasks();
        m_FrmTasks.hide();
        return;
    }
    QSharedPointer<CTasks> p = m_TasksList.Get(pItem->data().toInt());
    if(nullptr == p)
    {
        m_FrmTasks.SetTasks();
        m_FrmTasks.hide();
        return;
    }
    m_FrmTasks.SetTasks(p);
    m_FrmTasks.show();
}

void CFrmTasksList::slotNew()
{
    //TODO：增加一个常用任务的组合框列表供用户选择  
    QSharedPointer<CTasks> tasks(new CTasks());
    tasks->SetTitle(tr("New tasks"));
    tasks->SetIcon(QIcon::fromTheme("task"));
    tasks->SetContent(tr("After 5 minutes, the prompt will show 5 minutes, repeat"));
    m_TasksList.Add(tasks);
    //TODO:如果这里是新的，原来没有开始过。是否增加重新开始菜单？  
    //m_TasksList.Start();
    QSharedPointer<CTask> task(new CTask(5 * 60 * 1000));
    task->SetTitle(tr("New task"));
    task->SetContent(tr("If the task is not you need, please select a task from combox, new it, and remove the task."));
    tasks->Add(task);
    QSharedPointer<CTask> taskPrompt(new CTaskPromptDelay());
    task->SetTitle(tr("New prompt task"));
    task->SetContent(tr("If the task is not you need, please select a task from combox, new it, and remove the task."));
    tasks->Add(taskPrompt);
    
    QStandardItem *pItem = new QStandardItem(tasks->GetIcon(), tasks->GetTitle());
    if(!pItem) return;
    pItem->setToolTip(tasks->GetContent());
    pItem->setData(tasks->GetId());
    m_Model.appendRow(pItem);
    m_lvTasks.setCurrentIndex(m_Model.index(m_Model.rowCount() - 1, 0));
    on_lvTasks_clicked(m_lvTasks.currentIndex());
}

void CFrmTasksList::slotRemove()
{
    QStandardItem* pItem = m_Model.item(m_lvTasks.currentIndex().row());
    if(!pItem) return;
    m_TasksList.Remove(m_TasksList.Get(pItem->data().toInt()));
    m_Model.removeRow(m_lvTasks.currentIndex().row());
    on_lvTasks_clicked(m_lvTasks.currentIndex());
}

void CFrmTasksList::on_lvTasks_indexesMoved(const QModelIndexList &indexes)
{
    QStandardItem* pItem = m_Model.item(indexes.at(0).row());
    if(!pItem) return;
    QSharedPointer<CTasks> p = m_TasksList.Get(pItem->data().toInt());
    if(nullptr == p)
        return;
    m_FrmTasks.SetTasks(p);
    m_FrmTasks.show();
}

void CFrmTasksList::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    m_TasksList.RemoveAll();
}
