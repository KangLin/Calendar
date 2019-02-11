#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TaskTrayIconPrompt.h"
#include "TaskLockScreen.h"
#include "TaskPrompt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bool check = false;
    check = connect(&m_Timer, SIGNAL(timeout()),
                    this, SLOT(slotTimeout()));
    Q_ASSERT(check);

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
    //TODO: Add the maximum common divisor
    m_Timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_lstTasks.RemoveAll();
}

void MainWindow::slotTimeout()
{
    m_lstTasks.Check();
}

void MainWindow::on_pbAdd_clicked()
{
    QSharedPointer<CTasks> tasks(new CTasks());

    QSharedPointer<CTaskPrompt> prompt(new CTaskPrompt(
                                     "Lock screen and rest",
                                     5000, 1000));
    prompt->SetName("Will want to lock the screen");
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen(3000, 1000));
    lock->SetName("Lock");
    tasks->Add(lock);
    tasks->Start();
    m_lstTasks.Add(tasks);
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
    qApp->quit();
}

void MainWindow::slotSettings(bool checked)
{
    this->show();
}

QSharedPointer<CTasks> MainWindow::VisionProtectionTasks(CTasksList &taskList)
{
    QSharedPointer<CTasks> tasks(new CTasks());
    QSharedPointer<CTask> task(new CTask(40 * 60 *1000));
    task->SetName("Work");
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskPrompt(
                                     "Lock screen and rest"
                                     ));
    prompt->SetName("Will want to lock the screen");
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    lock->SetName("Lock");
    tasks->Add(lock);
    taskList.Add(tasks);
    return tasks;
}
