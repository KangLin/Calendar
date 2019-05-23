#include "FrmCalendar.h"
#include "ui_FrmCalendar.h"
#include "LunarCalendar.h"
#include <QVBoxLayout>
#include <QDate>
#include <QAction>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>

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
    m_ToolBar(this)
{
    bool check = false;
    setWindowTitle(tr("Calendar"));
    
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
    
    m_listView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    setLayout(pLayout);
    pLayout->addWidget(&m_ToolBar);
    pLayout->addWidget(m_pCalendar);
    pLayout->addWidget(&m_listView);

}

CFrmCalendar::~CFrmCalendar()
{
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
    QDir d;
    if(d.exists(szFile))
    {
        QMessageBox::StandardButton n = QMessageBox::warning(this,
                          tr("File exist"),
                          tr("%1 is existed, replace it?").arg(szFile),
                          QMessageBox::Ok | QMessageBox::Cancel);
        if(QMessageBox::Ok != n)
            return;        
    }
    
    int nRet = m_TasksList.SaveSettings(szFile);
    if(0 == nRet)
    {
        QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                      QSettings::IniFormat);
        set.setValue("TasksAcitvityList", szFile);
    }
}

void CFrmCalendar::slotViewWeek(bool checked)
{
    if(checked)
        m_pCalendar->SetViewType(CLunarCalendar::ViewTypeWeek);
    else
        m_pCalendar->SetViewType(CLunarCalendar::ViewTypeMonth);

//    updateGeometry();
}

void CFrmCalendar::slotCalendarHead(bool checked)
{
    m_pCalendar->ShowHead(checked);
    m_pCalendar->ShowTime(false);
    m_pCalendar->ShowDate(true);
}

void CFrmCalendar::slotAdd()
{
    CDlgTaskActivity task;
#if defined (Q_OS_ANDROID)
    task.showMaximized();
#endif
    if(QDialog::Accepted == task.exec())
    {
        QSharedPointer<CTasks> tasks(new CTasks());
        tasks->Add(task.GetTask());
        m_TasksList.Add(tasks);
    }
}

void CFrmCalendar::slotDelete()
{   
}

void CFrmCalendar::slotModify()
{  
}

int CFrmCalendar::onHandle(QDate date)
{
    int nRet = 0;
    Q_UNUSED(date);
    
    return nRet;
}
