#include "FrmTasks.h"
#include "ui_FrmTasks.h"

CFrmTasks::CFrmTasks(QSharedPointer<CTasks> tasks, bool readOnly, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTasks)
{
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    m_Tasks = tasks;
    SetTasks(m_Tasks);
    if(readOnly)
    {
        ui->pbAdd->hide();
        ui->pbRemove->setVisible(false);
        ui->pbApply->setVisible(false);
    }
}

CFrmTasks::~CFrmTasks()
{
    delete ui;
}

int CFrmTasks::SetTasks(QSharedPointer<CTasks> tasks)
{
    int nRet = 0;
    if(!tasks)
        tasks = m_Tasks;
    if(!tasks)
        return -1;
    m_Tasks = tasks;
    
    ui->vsLength->setRange(0, tasks->Length() - 1);
    ui->vsLength->setValue(tasks->GetCurrentIndex());
    ui->leTasksTitle->setText(tasks->GetTitle());
    ui->leTasksID->setText(QString::number(tasks->GetId()));
    ui->teTasksContent->setText(tasks->GetContent());
    
    SetTask(tasks->Get());
    return nRet;
}

int CFrmTasks::SetTask(QSharedPointer<CTask> task)
{
    if(!task)
        return -1;
    ui->leTaskID->setText(QString::number(task->GetId()));
    ui->leTaskTitle->setText(task->GetTitle());
    ui->teTaskContent->setText(task->GetContent());
    ui->spInterval->setValue(task->GetInterval() / 60000);
    ui->spPromptInterval->setValue(task->GetPromptInterval() / 1000);

    if(m_Tasks->Get() == task)
    {
        ui->gpTask->setChecked(true);
        ui->gpTask->setCheckable(true);
        ui->gpTask->setToolTip(tr("There is current task in tasks"));
    }else{
        ui->gpTask->setChecked(false);
        ui->gpTask->setCheckable(false);
        ui->gpTask->setToolTip(tr("Task"));
    }

    return 0;
}

void CFrmTasks::on_pbAdd_clicked()
{
    QSharedPointer<CTask> task(new CTask());
    task->SetTitle(tr("New task"));
    m_Tasks->Add(task);
    SetTask(task);
    ui->vsLength->setRange(0, m_Tasks->Length() - 1);
    ui->vsLength->setValue(m_Tasks->Length() - 1);
}

void CFrmTasks::on_pbRemove_clicked()
{
    m_Tasks->Remove(m_Tasks->Get(ui->vsLength->value()));
    SetTasks();
    emit Change();
}

void CFrmTasks::on_pbClose_clicked()
{
    close();
}

void CFrmTasks::on_vsLength_valueChanged(int value)
{
    SetTask(m_Tasks->Get(value));
}

void CFrmTasks::on_pbPrevious_clicked()
{
    ui->vsLength->triggerAction(QSlider::SliderSingleStepSub);
}

void CFrmTasks::on_pbNext_clicked()
{
    ui->vsLength->triggerAction(QSlider::SliderSingleStepAdd);
}

void CFrmTasks::on_pbApply_clicked()
{
    QSharedPointer<CTask> task = m_Tasks->Get(ui->vsLength->value());
    if(!task)
        return;
    m_Tasks->SetTitle(ui->leTasksTitle->text());
    m_Tasks->SetContent(ui->teTasksContent->toPlainText());
    
    task->SetTitle(ui->leTaskTitle->text());
    task->SetContent(ui->teTaskContent->toPlainText());
    task->SetInterval(ui->spInterval->value() * 60 * 1000);
    task->SetPromptInterval(ui->spPromptInterval->value() * 1000);
    emit Change();
}

void CFrmTasks::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    m_Tasks.clear();
}
