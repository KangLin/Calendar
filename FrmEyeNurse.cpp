#include "FrmEyeNurse.h"
#include "ui_FrmEyeNurse.h"
#include "TaskLockScreen.h"
#include "TaskPromptDelay.h"
#include "DlgAbout/DlgAbout.h"
#include <QMessageBox>
#include "Global/Tool.h"
#include "Global/GlobalDir.h"
#include <QDir>
#include "FrmTaskPropery.h"
#include <QDebug>
#include "FrmTasks.h"

CFrmEyeNurse::CFrmEyeNurse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmEyeNurse)
{
    ui->setupUi(this);

    bool check = connect(&m_frmTasks, SIGNAL(Change()),
                         this, SLOT(slotChange()));
    Q_ASSERT(check);
    
    m_TrayIconMenu.addAction(
                QIcon(":/icon/Close"),
                tr("Exit"),
                this,
                SLOT(slotExit(bool)));
    m_pShow = m_TrayIconMenu.addAction(QIcon(":/icon/EyeNurse"), tr("Show"), this, SLOT(slotShow(bool)));
    m_TrayIconMenu.addAction(QIcon(":/icon/App"),
                             tr("About"),
                             this,
                             SLOT(slotAbout(bool)));
    QString szStartRun = tr("Enable run from boot");
    if(CTool::IsStartRunOnceCurrentUser())
    {
        szStartRun = tr("Disable run from boot");
    }
    m_pStartRun = m_TrayIconMenu.addAction(szStartRun, this, SLOT(slotStartRun(bool)));
    m_pStartRun->setCheckable(true);
    m_pStartRun->setChecked(CTool::IsStartRunOnceCurrentUser());
    
    check = connect(&m_TrayIcon,
                    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this,
                    SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));
    Q_ASSERT(check);
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    m_TrayIcon.show();
    
    // Load configure
    m_TasksList.setObjectName("EyeNurse");
    int nRet = m_TasksList.LoadSettings();
    if(nRet)
        VisionProtectionTasks();
    
    m_TasksList.Start();
}

CFrmEyeNurse::~CFrmEyeNurse()
{
    delete ui;
}

int CFrmEyeNurse::VisionProtectionTasks()
{
    m_TasksList.RemoveAll();
    m_TasksList.setObjectName("EyeNurse");
    QSharedPointer<CTasks> tasks(new CTasks());
    tasks->SetTitle(tr("Eye nurse"));
    tasks->SetContent(tr("Protect eyesight"));
    QSharedPointer<CTask> task(new CTask(40 * 60 *1000));
    task->SetTitle(tr("Work"));
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskPrompt(
                                     tr("Will want to lock the screen"),
                                     tr("Prompt to lock the screen and rest")
                                     ));
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    tasks->Add(lock);
    m_TasksList.Add(tasks);

    return 0;
}

void CFrmEyeNurse::slotAbout(bool checked)
{
    Q_UNUSED(checked);
    static CDlgAbout dlg;
    if(dlg.isHidden())
        dlg.exec();
}

void CFrmEyeNurse::slotExit(bool checked)
{
    Q_UNUSED(checked);
    qApp->quit();
}

void CFrmEyeNurse::slotShow(bool checked)
{
    Q_UNUSED(checked);
    
    if(!m_frmTasks.isHidden())
        return;
    m_frmTasks.SetTasks(m_TasksList.Get(0));
    m_frmTasks.show();
}

void CFrmEyeNurse::slotStartRun(bool checked)
{
    if(checked)
    {
        CTool::InstallStartRunOnceCurrentUser();
        m_pStartRun->setText(tr("Disable run from boot"));
    }
    else
    {
        CTool::RemoveStartRunOnceCurrentUser();
        m_pStartRun->setText(tr("Enable run from boot"));
    }
}

void CFrmEyeNurse::slotActivated(QSystemTrayIcon::ActivationReason r)
{
    if(QSystemTrayIcon::ActivationReason::Trigger == r)
        slotShow(true);
}

void CFrmEyeNurse::slotChange()
{
    m_TasksList.SaveSettings();
}

void CFrmEyeNurse::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
