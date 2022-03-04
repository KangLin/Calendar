// 作者：康林 <kl222@126.com>

#include "FrmCalendar.h"
#include "LunarCalendar.h"
#include "DlgContainer.h"
#include "DlgTaskActivity.h"
#include "TaskActivity.h"
#include "RabbitCommonDir.h"

#include <QVBoxLayout>
#include <QDate>
#include <QAction>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QResizeEvent>

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
    setWindowIcon(QIcon(":/icon/App"));

    m_listView.setModel(m_pModel);
    m_listView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    check = connect(&m_listView, SIGNAL(doubleClicked(const QModelIndex &)),
                    this, SLOT(slotViewDoubleClicked(const QModelIndex&)));
    Q_ASSERT(check);
    m_listView.setContextMenuPolicy(Qt::CustomContextMenu);
    check = connect(&m_listView,
                SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(slotViewCustomContextMenuRequested(const QPoint &)));
    Q_ASSERT(check);
    m_TasksList.setObjectName("TasksActivityList");
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(), 
                  QSettings::IniFormat);
    QString szFile = set.value("TasksAcitvityList").toString();
    Load(szFile);
    m_TasksList.Start();

    m_pCalendar = new CLunarCalendar(this);
    m_pCalendar->SetTouchUpDownFunction(CLunarCalendar::TouchChangeView);
    m_pCalendar->SetTaskHandle(QSharedPointer<CTasksHandler>(
                                   new CTasksHandler(this)));
    m_pCalendar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    //m_pCalendar->SetViewType(CLunarCalendar::ViewTypeWeek);
    if(!QLocale::system().name().compare("zh_CN", Qt::CaseInsensitive)
            || !QLocale::system().name().compare("zh_TW", Qt::CaseInsensitive)
            || !QLocale::system().name().compare("zh_HK", Qt::CaseInsensitive))
        m_pCalendar->SetCalendarType((CLunarCalendar::_CalendarType)(CLunarCalendar::CalendarTypeLunar|CLunarCalendar::CalendarTypeSolar));
    else
        m_pCalendar->SetCalendarType(CLunarCalendar::CalendarTypeSolar);
#if defined (Q_OS_ANDROID)
    m_pCalendar->ShowHead(false);
#else
    m_pCalendar->ShowHead(true);
#endif
    m_pCalendar->ShowTime(false);
    m_pCalendar->ShowDate(true);
    m_pCalendar->ShowWeeks(false);
    check = connect(m_pCalendar, SIGNAL(sigSelectionChanged()),
                         this, SLOT(slotSelectionChanged()));
    Q_ASSERT(check);

    QAction* pAction = nullptr;
    pAction = new QAction(QIcon(":/icon/File"), tr("Open"), this);
    pAction->setStatusTip(tr("Open"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotLoad()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Save"), tr("Save As"), this);
    pAction->setStatusTip(tr("Save As"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotSaveAs()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    
    m_ToolBar.addSeparator();
    pAction = new QAction(QIcon(":/icon/Add"), tr("Add"), this);
    pAction->setStatusTip(tr("Add"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Delete"), tr("Delete"), this);
    pAction->setStatusTip(tr("Delete"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotDelete()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Edit"), tr("Modify"), this);
    pAction->setStatusTip(tr("Modify"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotModify()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    m_ToolBar.addSeparator();   
    pAction = new QAction(QIcon(":/icon/Refresh"), tr("Refresh"), this);
    pAction->setStatusTip(tr("Modify"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotRefresh()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    m_ToolBar.addSeparator();
#if defined (Q_OS_ANDROID)
    pAction = new QAction(QIcon(":/image/Today"), tr("Today"), this);
    pAction->setStatusTip(tr("Today"));
    check = connect(pAction, SIGNAL(triggered()),
                    m_pCalendar, SLOT(soltShowToday()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);    
#else
    pAction = new QAction(QIcon(":/icon/ViewWeek"), tr("Week"), this);
    pAction->setStatusTip(tr("Week"));
    pAction->setCheckable(true);
    //pAction->setChecked(true);
    check = connect(pAction, SIGNAL(triggered(bool)),
                    this, SLOT(slotViewWeek(bool)));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Tools"), tr("Tools"), this);
    pAction->setStatusTip(tr("Tools"));
    pAction->setCheckable(true);
    pAction->setChecked(true);
    check = connect(pAction, SIGNAL(triggered(bool)),
                    this, SLOT(slotCalendarHead(bool)));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
#endif

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
        QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
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
                szFile = RabbitCommon::CDir::Instance()->GetDirUserXml()
                                + QDir::separator()
                                + "TasksAcitvityList.xml";
            }
        }

        if(!szFile.isEmpty())
        {
            int nRet = m_TasksList.SaveSettings(szFile);
            if(0 == nRet)
            {
                QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                              QSettings::IniFormat);
                set.setValue("TasksAcitvityList", szFile);
                m_bModify = false;
            }
        }
    }
}

int CFrmCalendar::Load(const QString &szFile)
{
    int nRet = m_TasksList.LoadSettings(szFile);
    if(nRet)
        return nRet;

    return 0;
}

void CFrmCalendar::slotSelectionChanged()
{
    if(!m_pCalendar)
        return;
    QDate date = m_pCalendar->SelectedDate();
    m_pModel->clear();
    CTasksList::POSTION pos = m_TasksList.GetFirst();
    QSharedPointer<CTasks> tasks = m_TasksList.GetNext(pos);
    while(tasks)
    {
        CTasks::POSTION posTask = tasks->GetFirst();
        QSharedPointer<CTask> task = tasks->GetNext(posTask);
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
        tasks = m_TasksList.GetNext(pos);
    };
}

void CFrmCalendar::slotLoad()
{
#ifdef RABBITCOMMON
    QString szFile = RabbitCommon::CDir::GetOpenFileName(this,
                    tr("Load"), QString(), tr("xml(*.xml);;All files(*.*)"));
    Load(szFile);
#endif
}

void CFrmCalendar::slotSaveAs()
{
#ifdef RABBITCOMMON
    QString szFile = RabbitCommon::CDir::GetSaveFileName(this,
                                tr("Save as ..."), QString(), "*.xml");
    if(szFile.lastIndexOf(".xml") == -1)
        szFile += ".xml";
    int nRet = m_TasksList.SaveSettings(szFile);
    if(0 == nRet)
    {
        QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                      QSettings::IniFormat);
        set.setValue("TasksAcitvityList", szFile);
        m_bModify = false;
    }
#endif
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
    ta->SetDateStart(m_pCalendar->SelectedDate().year(),
                     m_pCalendar->SelectedDate().month(),
                     m_pCalendar->SelectedDate().day());
    ta->SetDateEnd(ta->GetDateStart());
    CDlgTaskActivity* task = new CDlgTaskActivity(ta.data());
    CDlgContainer dlg;
    dlg.SetWidget(task);
    if(QDialog::Accepted == dlg.ExtendExec())
    {
        task->ApplyTask();
        QSharedPointer<CTasks> tasks(new CTasks());
        tasks->Add(ta);
        tasks->SetTitle(task->GetTask()->GetTitle());
        tasks->SetContent(task->GetTask()->GetContent());
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
    CDlgTaskActivity *t = new CDlgTaskActivity((CTaskActivity*)task.data());
    CDlgContainer dlg;
    dlg.SetWidget(t);
    if(QDialog::Accepted == dlg.ExtendExec())
    {
        t->ApplyTask();
        Update();
        m_bModify = true;
    }
}

void CFrmCalendar::slotRefresh()
{
    m_TasksList.Start();
}

void CFrmCalendar::slotViewDoubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    slotModify();
}

void CFrmCalendar::slotViewCustomContextMenuRequested(const QPoint& pos)
{
    m_ListViewMenu.clear();
    QAction* pAction = m_ListViewMenu.addAction(QIcon(":/icon/Add"), tr("Add"));
    bool check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotAdd()));
    Q_ASSERT(check);
    pAction = m_ListViewMenu.addAction(QIcon(":/icon/Delete"), tr("Delete"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotDelete()));
    Q_ASSERT(check);
    pAction = m_ListViewMenu.addAction(QIcon(":/icon/Edit"), tr("Modify"));
    check = connect(pAction, SIGNAL(triggered()), this, SLOT(slotModify()));
    Q_ASSERT(check);
    m_ListViewMenu.popup(m_listView.mapToGlobal(pos));
}

int CFrmCalendar::onHandle(QDate date)
{
    int nCount = 0;
    CTasksList::POSTION pos = m_TasksList.GetFirst();
    QSharedPointer<CTasks> tasks = m_TasksList.GetNext(pos);
    while(tasks)
    {
        CTasks::POSTION posTask = tasks->GetFirst();
        QSharedPointer<CTask> task = tasks->GetNext(posTask);
        if(task)
        {
            const QMetaObject* pObj = task->metaObject();
            if(QString("CTaskActivity") == pObj->className())
            {
                CTaskActivity* pTask = static_cast<CTaskActivity*>(task.data());
                if(pTask->CheckDate(date) == 0)
                {
                    nCount++;
                }
            }
        }
        tasks = m_TasksList.GetNext(pos);
    };
    return nCount;
}

int CFrmCalendar::Update()
{
    m_pCalendar->Update();
    onHandle(m_pCalendar->SelectedDate());
    slotSelectionChanged();
    //m_TasksList.Start();
    return 0;
}
