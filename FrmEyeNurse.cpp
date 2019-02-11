#include "FrmEyeNurse.h"
#include "ui_FrmEyeNurse.h"

#include "TaskPrompt.h"
#include "TaskLockScreen.h"

CFrmEyeNurse::CFrmEyeNurse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmEyeNurse)
{
    ui->setupUi(this);
    
    m_TrayIconMenu.addAction(
                QIcon(":/icon/Close"),
                tr("Exit"),
                this,
                SLOT(slotExit(bool)));
    m_pShow = m_TrayIconMenu.addAction(tr("Show"), this, SLOT(slotShow(bool)));
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    
    //TODO: Load configure
    
    VisionProtectionTasks();
}

CFrmEyeNurse::~CFrmEyeNurse()
{
    delete ui;
    m_TaskList.RemoveAll();
}

int CFrmEyeNurse::VisionProtectionTasks()
{
    m_TaskList.RemoveAll();
    QSharedPointer<CTasks> tasks(new CTasks());
    QSharedPointer<CTask> task(new CTask(40 * 60 *1000));
    task->SetName("Work");
    task->SetInterval((ui->sbRestInterval->value() - ui->sbPrompTime->value())
                      * 60 * 1000);
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskPrompt(
                                     "Lock screen and rest"
                                     ));
    prompt->SetName("Will want to lock the screen");
    prompt->SetInterval(ui->sbPrompTime->value());
    prompt->SetPromptInterval(ui->sbPromptInterval->value());
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    lock->SetName("Lock");
    lock->SetInterval(ui->sbRestTime->value());
    tasks->Add(lock);
    m_TaskList.Add(tasks);
    m_TaskList.Start();
    return 0;
}

void CFrmEyeNurse::slotExit(bool checked)
{
    Q_UNUSED(checked);
    qApp->quit();
}

void CFrmEyeNurse::slotShow(bool checked)
{
    Q_UNUSED(checked);
    if(this->isHidden())
    {
        show();
        m_pShow->setText(tr("Hide"));
    }else {
        hide();
        m_pShow->setText(tr("Show"));
    }
}

void CFrmEyeNurse::on_pbOK_clicked()
{
    VisionProtectionTasks();
    //TODO: Save configure
    
    hide();
    m_pShow->setText(tr("Show"));
}

void CFrmEyeNurse::on_bpCancle_clicked()
{
    hide();
    m_pShow->setText(tr("Show"));
}
