#include "FrmEyeNurse.h"
#include "ui_FrmEyeNurse.h"
#include "TaskLockScreen.h"
#include "DlgAbout/DlgAbout.h"
#include <QMessageBox>
#include "Global/Tool.h"
#include "Global/GlobalDir.h"
#include <QDir>
#include "FrmTaskPropery.h"

CFrmEyeNurse::CFrmEyeNurse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmEyeNurse)
{
    ui->setupUi(this);
    QDir d;
    d.mkpath(CGlobalDir::Instance()->GetDirDocument());
                 
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
        szStartRun = tr("Disable run from boot");
    m_pStartRun = m_TrayIconMenu.addAction(szStartRun, this, SLOT(slotStartRun(bool)));
    m_pStartRun->setCheckable(true);
    m_pStartRun->setChecked(CTool::IsStartRunOnceCurrentUser());
    
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    m_TrayIcon.show();
    
    // Load configure
    m_TaskList.setObjectName("EyeNurse");
    int nRet = m_TaskList.LoadSettings();
    if(nRet)
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
    m_TaskList.setObjectName("EyeNurse");
    QSharedPointer<CTasks> tasks(new CTasks());
    tasks->SetTitle(tr("Eye nurse"));
    QSharedPointer<CTask> task(new CTask(40 * 60 *1000));
    task->SetTitle(tr("Work"));
    int nWork = ui->sbRestInterval->value() - ui->sbPrompTime->value();
    if(nWork <= 0)
        nWork = 0;
    else
        nWork = nWork * 60 * 1000;
    task->SetInterval(nWork);
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskPrompt(
                                     tr("Will want to lock the screen"),
                                     tr("Lock screen and rest")
                                     ));
    prompt->SetInterval(ui->sbPrompTime->value() * 60 * 1000);
    prompt->SetPromptInterval(ui->sbPromptInterval->value() * 1000);
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    lock->SetTitle("Lock");
    lock->SetInterval(ui->sbRestTime->value() * 60 * 1000);
    tasks->Add(lock);
    m_TaskList.Add(tasks);
    m_TaskList.Start();
    return 0;
}

void CFrmEyeNurse::slotAbout(bool checked)
{
    Q_UNUSED(checked);
    CDlgAbout dlg(this);
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
    
    CFrmTaskProperty *taskProperty = new CFrmTaskProperty(&m_TaskList);
    taskProperty->show();
    
    return;
    
    if(this->isHidden())
    {
        show();
        m_pShow->setText(tr("Hide"));
    }else {
        hide();
        m_pShow->setText(tr("Show"));
    }
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

void CFrmEyeNurse::on_pbOK_clicked()
{
    VisionProtectionTasks();
    // Save configure
    m_TaskList.SaveSettings();
    hide();
    m_pShow->setText(tr("Show"));
}

void CFrmEyeNurse::on_bpCancle_clicked()
{
    hide();
    m_pShow->setText(tr("Show"));
}

void CFrmEyeNurse::on_sbRestInterval_editingFinished()
{
    if(ui->sbPrompTime->value() <= ui->sbRestInterval->value())
        return;

    QMessageBox::critical(this,
                          tr("Eye nurse"),
                          tr("Reset interval must greate then prompt time"));
    ui->sbRestInterval->setValue(ui->sbPrompTime->value());
}

void CFrmEyeNurse::on_sbPrompTime_editingFinished()
{
    int v = ui->sbPrompTime->value();
    if(ui->sbRestInterval->value() < v)
    {
        QMessageBox::critical(this,
                              tr("Eye nurse"),
                              tr("Reset interval must greate then prompt time"));
        ui->sbPrompTime->setValue(ui->sbRestInterval->value());
    }

    if(ui->sbPromptInterval->value() > v * 60)
    {
        QMessageBox::critical(this, tr("Eye nurse"),
                              tr("Prompt time muse greate then prompt interval"));
        ui->sbPrompTime->setValue(ui->sbPromptInterval->value() / 60 + 1);
    }
}

void CFrmEyeNurse::on_sbPromptInterval_editingFinished()
{
    if(ui->sbPrompTime->value() * 60 >= ui->sbPromptInterval->value())
        return;

    QMessageBox::critical(this, tr("Eye nurse"),
                          tr("Prompt time muse greate then prompt interval"));
    ui->sbPromptInterval->setValue(ui->sbPrompTime->value() * 60);
}

void CFrmEyeNurse::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
