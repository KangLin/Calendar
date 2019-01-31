#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "TaskWork.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool check = false;
    check = connect(&m_Timer, SIGNAL(timeout()),
                    &m_lstTasks, SLOT(slotCheck()));
    Q_ASSERT(check);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbAdd_clicked()
{
    QSharedPointer<CTask> task(new CTaskWork());
    task->SetInterval(2*1000);
    QSharedPointer<CTasks> tasks(new CTasks());
    tasks->Add(task);
    m_lstTasks.Add(tasks);
    m_Timer.start(1000);
}

void MainWindow::on_pbRemove_clicked()
{
    m_lstTasks.RemoveAll();
}
