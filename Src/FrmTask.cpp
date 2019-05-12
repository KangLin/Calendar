#include "FrmTask.h"
#include "ui_FrmTask.h"

CFrmTask::CFrmTask(QSharedPointer<CTask> task, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTask)
{
    ui->setupUi(this);
    SetTask(task);
}

CFrmTask::~CFrmTask()
{
    delete ui;
}

int CFrmTask::SetTask(QSharedPointer<CTask> task)
{
    //ui->gpTask->setTitle(tr("Task: ") + task->objectName());
    ui->leTaskID->setText(QString::number(task->GetId()));
    ui->leTaskTitle->setText(task->GetTitle());
    ui->teTaskContent->setText(task->GetContent());
    ui->spInterval->setValue(task->GetInterval() / 60000);
    ui->spPromptInterval->setValue(task->GetPromptInterval() / 1000);
    
    m_Task = task;
    return 0;
}

int CFrmTask::ApplyTask()
{
    m_Task->SetId(ui->leTaskID->text().toInt());
    m_Task->SetTitle(ui->leTaskTitle->text());
    m_Task->SetContent(ui->teTaskContent->toPlainText());
    m_Task->SetInterval(ui->spInterval->value() * 60000);
    m_Task->SetPromptInterval(ui->spPromptInterval->value() * 1000);
    return 0;
}
