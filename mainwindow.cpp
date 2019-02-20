#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TaskTrayIconPrompt.h"
#include "TaskPromptDelay.h"
#include "TaskLockScreen.h"
#include "TaskPrompt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_TrayIconMenu.addAction(
                QIcon(":/icon/Close"),
                tr("Exit"),
                this,
                SLOT(slotExit(bool)));
    m_TrayIconMenu.addAction(QIcon(":/icon/Settings"),
                             tr("Settings"),
                             this,
                             SLOT(slotSettings(bool)));
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    VisionProtectionTasks(m_lstTasks);
    m_lstTasks.Start();
}

MainWindow::~MainWindow()
{
    delete ui;
    m_lstTasks.RemoveAll();
}

void MainWindow::on_pbAdd_clicked()
{
    QSharedPointer<CTasks> tasks(new CTasks());

    QSharedPointer<CTaskPrompt> prompt(new CTaskPromptDelay(
                                     tr("Delay")));
    prompt->SetInterval(10000);
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen(3000, 1000));
    lock->setObjectName("Lock");
    //tasks->Add(lock);
    tasks->Start();
    m_lstTasks.Add(tasks);
    
    m_frmTasks.SetTasks(tasks);
}

void MainWindow::on_pbRemove_clicked()
{
    m_lstTasks.RemoveAll();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);
    hide();
    e->ignore();
}

void MainWindow::slotExit(bool checked)
{
    Q_UNUSED(checked);
    qApp->quit();
}

void MainWindow::slotSettings(bool checked)
{
    Q_UNUSED(checked);
    this->show();
}

QSharedPointer<CTasks> MainWindow::VisionProtectionTasks(CTasksList &taskList)
{
    QSharedPointer<CTasks> tasks(new CTasks());
    QSharedPointer<CTask> task(new CTask(40 * 60 *1000));
    task->setObjectName("Work");
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskPrompt(
                                     "Lock screen and rest"
                                     ));
    prompt->setObjectName("Will want to lock the screen");
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    lock->setObjectName("Lock");
    tasks->Add(lock);
    taskList.Add(tasks);
    return tasks;
}

void MainWindow::on_pushButton_clicked()
{
    m_frmTasks.show();
}
