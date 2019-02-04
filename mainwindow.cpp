#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TaskTrayIconPrompt.h"
#include "TaskLockScreen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool check = false;
    check = connect(&m_Timer, SIGNAL(timeout()),
                    this, SLOT(slotTimeout()));
    Q_ASSERT(check);
      
    QAction* pExit = m_TrayIconMenu.addAction(
                QIcon(":/icon/close"),
                tr("Exit"),
                this,
                SLOT(slotExit(bool)));

    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    
    VisionProtectionTasks(m_lstTasks);
    m_lstTasks.Start();
    m_Timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimeout()
{
    m_lstTasks.Check();
}

void MainWindow::on_pbAdd_clicked()
{
    QSharedPointer<CTasks> tasks(new CTasks());
 
    QSharedPointer<CTask> prompt(new CTaskTrayIconPrompt(
                                     "Lock screen and rest",
                                     "Rest", QIcon(":/icon/app"),5000));
    prompt->SetName("Will want to lock the screen");
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen(3000, 1000));
    lock->SetName("Lock");
    tasks->Add(lock);
    m_lstTasks.Add(tasks);
}

void MainWindow::on_pbRemove_clicked()
{
    m_lstTasks.RemoveAll();
}

void MainWindow::slotExit(bool checked)
{
    qApp->quit();
}

QSharedPointer<CTasks> MainWindow::VisionProtectionTasks(CTasksList &taskList)
{
    QSharedPointer<CTasks> tasks(new CTasks());
    QSharedPointer<CTask> task(new CTask(40 * 60 *1000));
    task->SetName("Work");
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskTrayIconPrompt(
                                     "Lock screen and rest",
                                     "Rest"));
    prompt->SetName("Will want to lock the screen");
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    lock->SetName("Lock");
    tasks->Add(lock);
    taskList.Add(tasks);
    return tasks;
}
