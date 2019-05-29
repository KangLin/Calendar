#include "FrmCalendar.h"
#include "ui_FrmCalendar.h"
#include "LunarCalendar.h"
#include <QVBoxLayout>
#include <QDate>
#include <QAction>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "DlgTaskActivity.h"
#include "TaskActivity.h"
#include "Global/GlobalDir.h"

class CTasksHandler : public CLunarCalendar::CGetTaskHandler
{
public:
    CTasksHandler(CFrmCalendar* pFrmCalendar);
    virtual ~CTasksHandler();
    
    virtual int onHandle(QDate date);
private:
    CFrmCalendar* m_pFrmCalendar;
};

CTasksHandler::CTasksHandler(CFrmCalendar* pFrmCalendar)
    : CLunarCalendar::CGetTaskHandler()
{
    m_pFrmCalendar = pFrmCalendar;
}

CTasksHandler::~CTasksHandler()
{
}

int CTasksHandler::onHandle(QDate date)
{
    return m_pFrmCalendar->onHandle(date);
}

CFrmCalendar::CFrmCalendar(QWidget *parent) :
    QWidget(parent),
    m_pModel(new QStandardItemModel(this)),
    m_ToolBar(this),
    m_bModify(false)
{
    bool check = false;
    setWindowTitle(tr("Calendar"));

    m_listView.setModel(m_pModel);
    m_listView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    check = connect(&m_listView, SIGNAL(doubleClicked(const QModelIndex &)),
                    this, SLOT(slotViewDoubleClicked(const QModelIndex&)));
    Q_ASSERT(check);
    m_TasksList.setObjectName("TasksActivityList");
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(), 
                  QSettings::IniFormat);
    QString szFile = set.value("TasksAcitvityList").toString();
    Load(szFile);
    
    QAction* pAction = nullptr;
    pAction = new QAction(QIcon(":/icon/File"), tr("Open"), this);
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotLoad()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Save"), tr("Save As"), this);
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotSaveAs()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    
    m_ToolBar.addSeparator();
    pAction = new QAction(QIcon(":/icon/Add"), tr("Add"), this);
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Delete"), tr("Delete"), this);
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotDelete()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Edit"), tr("Modify"), this);
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotModify()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);

    m_ToolBar.addSeparator();    
    pAction = new QAction(QIcon(":/icon/ViewWeek"), tr("Week"), this);
    pAction->setCheckable(true);
    pAction->setChecked(true);
    check = connect(pAction, SIGNAL(triggered(bool)),
                    this, SLOT(slotViewWeek(bool)));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Tools"), tr("Tools"), this);
    pAction->setCheckable(true);
    check = connect(pAction, SIGNAL(triggered(bool)),
                    this, SLOT(slotCalendarHead(bool)));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);

    CLunarCalendar::InitResource();
    m_pCalendar = new CLunarCalendar(this);
    m_pCalendar->SetTaskHandle(QSharedPointer<CTasksHandler>(
                                   new CTasksHandler(this)));
    m_pCalendar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    m_pCalendar->SetViewType(CLunarCalendar::ViewTypeWeek);
    //m_pCalendar->SetCalendarType(CLunarCalendar::CalendarTypeSolar);
    m_pCalendar->ShowHead(false);
    m_pCalendar->ShowTime(false);
    m_pCalendar->ShowDate(true);
    m_pCalendar->ShowWeeks(false);

    check = connect(m_pCalendar, SIGNAL(sigSelectionChanged()),
                         this, SLOT(slotSelectionChanged()));
    Q_ASSERT(check);

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    setLayout(pLayout);
    pLayout->addWidget(&m_ToolBar);
    pLayout->addWidget(m_pCalendar);
    pLayout->addWidget(&m_listView);
    
    Update();
}

CFrmCalendar::~CFrmCalendar()
{
    if(m_bModify)
    {
        QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(), 
                      QSettings::IniFormat);
        QString szFile = set.value("TasksAcitvityList").toString();
        if(szFile.isEmpty())
        {
            QMessageBox::StandardButton n
                    = QMessageBox::warning(this, tr("Save"),
                 tr("The calendar is changed, is it save?"),
                           QMessageBox::Ok|QMessageBox::No);
            if(QMessageBox::Ok == n)
            {
                slotSaveAs();
            }    
        } else
            m_TasksList.SaveSettings(szFile);
    }
}

int CFrmCalendar::Load(const QString &szFile)
{
    int nRet = m_TasksList.LoadSettings(szFile);
    if(nRet)
        return nRet;

    return m_TasksList.Start();
}

void CFrmCalendar::slotSelectionChanged()
{
    if(!m_pCalendar)
        return;
    QDate date = m_pCalendar->SelectedDate();
    Q_UNUSED(date);    
    //TODO: update list view
    
}

void CFrmCalendar::slotLoad()
{
    QFileDialog fd(this, tr("Load"), QString(), tr("xml(*.xml);;All files(*.*)"));
    fd.setFileMode(QFileDialog::ExistingFile);
#if defined (Q_OS_ANDROID)
    fd.showMaximized();
#endif
    int n = fd.exec();
    if(QDialog::Rejected == n)
        return;
    Load(fd.selectedFiles().at(0));
}

void CFrmCalendar::slotSaveAs()
{
    QFileDialog fd(this, tr("Save as ..."), QString(), "*.xml");
    //fd.setFileMode(QFileDialog::AnyFile);
    fd.setAcceptMode(QFileDialog::AcceptSave);
#if defined (Q_OS_ANDROID)
    fd.showMaximized();
#endif
    int n = fd.exec();
    if(QDialog::Rejected == n)
        return;
    QString szFile = fd.selectedFiles().at(0);
    if(szFile.lastIndexOf(".xml") == -1)
        szFile += ".xml";
    int nRet = m_TasksList.SaveSettings(szFile);
    if(0 == nRet)
    {
        QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                      QSettings::IniFormat);
        set.setValue("TasksAcitvityList", szFile);
        m_bModify = false;
    }
}

void CFrmCalendar::slotViewWeek(bool checked)
{
    if(checked)
        m_pCalendar->SetViewType(CLunarCalendar::ViewTypeWeek);
    else
        m_pCalendar->SetViewType(CLunarCalendar::ViewTypeMonth);
}

void CFrmCalendar::slotCalendarHead(bool checked)
{
    m_pCalendar->ShowHead(checked);
    m_pCalendar->ShowTime(false);
    m_pCalendar->ShowDate(true);
}

void CFrmCalendar::slotAdd()
{
    QSharedPointer<CTaskActivity> ta(new CTaskActivity());
    CDlgTaskActivity task(ta.data());
#if defined (Q_OS_ANDROID)
    task.showMaximized();
#endif
    if(QDialog::Accepted == task.exec())
    {
        QSharedPointer<CTasks> tasks(new CTasks());
        tasks->Add(ta);
        tasks->SetTitle(task.GetTask()->GetTitle());
        tasks->SetContent(task.GetTask()->GetContent());
        m_TasksList.Add(tasks);
        Update();
        m_bModify = true;
    }
}

void CFrmCalendar::slotDelete()
{
    int n = QMessageBox::warning(this, tr("Warning"), tr("Is sure delete ?"),
                                 QMessageBox::Yes|QMessageBox::No);
    if(QMessageBox::No == n)
        return;
    
    QModelIndex index = m_listView.currentIndex();
    if(!index.isValid())
        return;
    QStandardItem* pItem = m_pModel->itemFromIndex(index);
    QString szId = pItem->data().toString();
    QStringList id = szId.split('_');
    QSharedPointer<CTasks> tasks = m_TasksList.Get(id.at(0).toInt());
    if(!tasks)
        return;
    m_TasksList.Remove(tasks);
    Update();
    m_bModify = true;
}

void CFrmCalendar::slotModify()
{
    QModelIndex index = m_listView.currentIndex();
    if(!index.isValid())
        return;
    QStandardItem* pItem = m_pModel->itemFromIndex(index);
    QString szId = pItem->data().toString();
    QStringList id = szId.split('_');
    QSharedPointer<CTasks> tasks = m_TasksList.Get(id.at(0).toInt());
    if(!tasks)
        return;
    QSharedPointer<CTask> task = tasks->Get(id.at(1).toInt());
    CDlgTaskActivity dlg((CTaskActivity*)task.data());
#if defined (Q_OS_ANDROID)
    task.showMaximized();
#endif
    if(QDialog::Accepted == dlg.exec())
    {
        Update();
        m_bModify = true;
    }
}

void CFrmCalendar::slotViewDoubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    slotModify();
}

int CFrmCalendar::onHandle(QDate date)
{
    int index = 0;
    m_pModel->clear();
    QSharedPointer<CTasks> tasks = m_TasksList.Get(index++);
    while(tasks)
    {
        QSharedPointer<CTask> task = tasks->Get();
        if(task)
        {
            const QMetaObject* pObj = task->metaObject();
            if(QString("CTaskActivity") == pObj->className())
            {
                CTaskActivity* pTask = static_cast<CTaskActivity*>(task.data());
                if(pTask->CheckDate(date) == 0)
                {
                    QStandardItem* pItem = new QStandardItem(pTask->GetTitle());
                    pItem->setData(QString::number(tasks->GetId())
                                   + "_" + QString::number(task->GetId()));
                    m_pModel->appendRow(pItem);
                }
            }
        }
        tasks = m_TasksList.Get(index++);
    }
    return m_pModel->rowCount();
}

int CFrmCalendar::Update()
{
    m_pCalendar->Update();
    onHandle(m_pCalendar->SelectedDate());
    return 0;
}
