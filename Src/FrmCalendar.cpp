#include "FrmCalendar.h"
#include "ui_FrmCalendar.h"
#include "LunarCalendar.h"
#include <QVBoxLayout>
#include <QDate>
#include <QAction>
#include "FrmTaskActivity.h"
#include "TaskActivity.h"
#include "TasksList.h"

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
    ui(new Ui::CFrmCalendar),
    m_ToolBar(this)
{
    ui->setupUi(this);
    
    bool check = false;
    
    QAction* pAction = nullptr;
    pAction = new QAction(QIcon(":/icon/Add"), tr("Add"), this);
    check = connect(pAction, SIGNAL(triggered()),
                    this, SLOT(slotAddTask()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Delete"), tr("Delete"), this);
    check = connect(pAction, SIGNAL(triggered()),
                    this, SLOT(slotDeleteTask()));
    Q_ASSERT(check);
    m_ToolBar.addAction(pAction);
    pAction = new QAction(QIcon(":/icon/Edit"), tr("Modify"), this);
    check = connect(pAction, SIGNAL(triggered()),
                    this, SLOT(slotModifyTask()));
    Q_ASSERT(check);
    m_ToolBar.addSeparator();
    m_ToolBar.addAction(pAction); 
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
    //m_pCalendar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_pCalendar->SetViewType(CLunarCalendar::ViewTypeWeek);
    //m_pCalendar->SetCalendarType(CLunarCalendar::CalendarTypeSolar);
    m_pCalendar->ShowHead(false);
    m_pCalendar->ShowTime(false);
    m_pCalendar->ShowDate(true);
    m_pCalendar->ShowWeeks(false);
    
    check = connect(m_pCalendar, SIGNAL(sigSelectionChanged()),
                         this, SLOT(slotSelectionChanged()));
    Q_ASSERT(check);
    
    m_listView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    setLayout(pLayout);
    pLayout->addWidget(&m_ToolBar);
    pLayout->addWidget(m_pCalendar);
    pLayout->addWidget(&m_listView);
    
//    QSharedPointer<CTaskActivity> task(new CTaskActivity());
//    task->SetTypeDate(CTaskActivity::Lunar);
//    task->SetPlace("place");
//    task->SetDateStart(2012,1,1);
//    task->SetTimeStart(QTime::currentTime());
//    task->AddPrompt();
//    QSharedPointer<CTasks> tasks(new CTasks());
//    tasks->Add(task);
//    CTasksList taskslist, tl;
//    taskslist.Add(tasks);
//    taskslist.SaveSettings("testTask.xml");
    
//    tl.LoadSettings("testTask.xml");
}

CFrmCalendar::~CFrmCalendar()
{
    delete ui;
}

void CFrmCalendar::slotSelectionChanged()
{
    if(!m_pCalendar)
        return;
    QDate date = m_pCalendar->SelectedDate();
    Q_UNUSED(date);    
    //TODO: update list view
    
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

void CFrmCalendar::slotAddTask()
{
    CFrmTaskActivity* pTask = new CFrmTaskActivity();
    pTask->show();
}

void CFrmCalendar::slotDeleteTask()
{
    
}

void CFrmCalendar::slotModifyTask()
{
    
}

int CFrmCalendar::onHandle(QDate date)
{
    int nRet = 0;
    Q_UNUSED(date);
    
    return nRet;
}
