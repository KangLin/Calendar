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
    QSharedPointer<CTask> work(new CTask(5 * 1000, 1000));
    tasks->Add(work);
    QSharedPointer<CTask> prompt(new CTaskTrayIconPrompt(tr("Lock screen rest"),
                                                 tr("Prompt"),
                                                 QIcon(":/icon/app"),
                                                 5 * 1000,
                                                 1 * 1000));

    tasks->Add(prompt);
    QSharedPointer<CTask> lock(new CTaskLockScreen(5 * 1000, 1 * 1000));
    tasks->Add(lock);
     
    m_lstTasks.Add(tasks);
    m_lstTasks.Start();
    m_Timer.start(1000);
}

void MainWindow::on_pbRemove_clicked()
{
    m_lstTasks.RemoveAll();
}
