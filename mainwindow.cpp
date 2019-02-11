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
}

void MainWindow::slotTimeout()
{
    m_lstTasks.Check();
}

void MainWindow::on_pbAdd_clicked()
{
    QSharedPointer<CTasks> tasks(new CTasks());
    QSharedPointer<CTask> task(new CTask(5 *1000));
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskTrayIconPrompt(
                                     tr("Lock screen and rest"),
                                     tr("Rest"),
                                     3 * 1000,
                                     1 * 1000));
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen(3 * 1000, 500));
    lock->SetName(tr("Lock"));
    tasks->Add(lock);
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
    task->SetName(tr("Work"));
    tasks->Add(task);
    QSharedPointer<CTask> prompt(new CTaskTrayIconPrompt(
                                     tr("Lock screen and rest"),
                                     tr("Rest")));
    prompt->SetName(tr("Will want to lock the screen prompt"));
    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen());
    lock->SetName(tr("Lock"));
    tasks->Add(lock);
    taskList.Add(tasks);
    return tasks;
}
