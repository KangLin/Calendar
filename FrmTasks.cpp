#include "FrmTasks.h"
#include "ui_FrmTasks.h"
#include "ObjectFactory.h"

CFrmTasks::CFrmTasks(QSharedPointer<CTasks> tasks,
                     bool readOnly, 
                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTasks)
{
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    
    InitTaskComboBox();
    
    if(readOnly)
    {
        ui->pbAdd->setVisible(false);
        ui->pbRemove->setVisible(false);
        ui->cbTask->setVisible(false);
        //ui->pbApply->setVisible(false);
    }
    
    m_Tasks = tasks;
    SetTasks(m_Tasks);    
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

    ui->leTasksTitle->setText(m_Tasks->GetTitle());
    ui->leTasksID->setText(QString::number(m_Tasks->GetId()));
    ui->teTasksContent->setText(m_Tasks->GetContent());
    
    SetSlider(m_Tasks->GetCurrentIndex());
    
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

int CFrmTasks::InitTaskComboBox()
{
    //TODO: Add task derived class
    ui->cbTask->addItem("CTask");
    ui->cbTask->addItem("CTaskPrompt");
    ui->cbTask->addItem("CTaskLockScreen");
    ui->cbTask->addItem("CTaskPromptDelay");
    return 0;
}

int CFrmTasks::SetSlider(int value)
{
    ui->vsLength->setRange(0, m_Tasks->Length() - 1);
    if(value > m_Tasks->Length() - 1)
        value = m_Tasks->Length() - 1;
    ui->vsLength->setValue(value);
    on_vsLength_valueChanged(value);
    return 0;
}

void CFrmTasks::on_pbAdd_clicked()
{
    QSharedPointer<CTask> task(qobject_cast<CTask*>(
                                   CObjectFactory::createObject(
              ui->cbTask->currentText().toStdString().c_str())));
    task->SetTitle(tr("New ") + task->objectName());
    m_Tasks->Insert(task, ui->vsLength->value() + 1);
    //SetTask(task);
    SetSlider(ui->vsLength->value() + 1);
}

void CFrmTasks::on_pbRemove_clicked()
{
    int nPos = ui->vsLength->value();
    m_Tasks->Remove(m_Tasks->Get(nPos));
    SetTasks();
    SetSlider(nPos);
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
