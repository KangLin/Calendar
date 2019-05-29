#include "FrmTasks.h"
#include "ui_FrmTasks.h"
#include "ObjectFactory.h"
#include <QtDebug>
#include <QFileDialog>

CFrmTasks::CFrmTasks(QWidget *parent)
    : QWidget (parent),
    ui(new Ui::CFrmTasks)
{
    ui->setupUi(this);
    InitTaskComboBox();
}

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
    {
        return -1;
    }
    m_Tasks = tasks;
    if(!m_Tasks)
    {
        setEnabled(false);
        return -2;
    }
    setEnabled(true);
    if(!tasks->GetIcon().isNull())
    {
        ui->pbTasksIcon->setIcon(tasks->GetIcon());
        setWindowIcon(tasks->GetIcon());
    }
    ui->leTasksTitle->setText(m_Tasks->GetTitle());
    ui->leTasksID->setText(QString::number(m_Tasks->GetId()));
    ui->teTasksContent->setText(m_Tasks->GetContent());
    
    SetSlider(m_Tasks->GetCurrentIndex());
    
    return nRet;
}

int CFrmTasks::SetTask(QSharedPointer<CTask> task)
{
    if(!task)
    {
        qCritical() << "CFrmTasks::SetTask: The task is null";
        return -1;
    }
    if(!task->GetIcon().isNull())
    {
        ui->pbTaskIcon->setIcon(task->GetIcon());
        ui->gpTask->setWindowIcon(task->GetIcon());
    }
    //ui->gpTask->setTitle(tr("Task: ") + task->objectName());
    ui->leTaskID->setText(QString::number(task->GetId()));
    ui->leTaskTitle->setText(task->GetTitle());
    ui->teTaskContent->setText(task->GetContent());
    ui->spInterval->setValue(task->GetInterval() / 60000);
    ui->spPromptInterval->setValue(task->GetPromptInterval() / 1000);

    if(!m_Tasks)
    {
        qCritical() << "CFrmTasks::SetTask: The m_Tasks is null";
        Q_ASSERT(false);
        return -1;
    }
    if(m_Tasks->GetCurrent() == task)
    {
        ui->lbStartTime->setText(tr("Start: %1").arg(
                                     QTime::currentTime().addMSecs(
                                         -1 * task->Elapsed()).toString()));
        ui->lbStartTime->show();
        ui->gpTask->setChecked(true);
        ui->gpTask->setCheckable(true);
        ui->gpTask->setToolTip(tr("There is current task in tasks.")
                               + "\n" + task->GetDescription());
    }else{
        ui->lbStartTime->hide();
        ui->gpTask->setChecked(false);
        ui->gpTask->setCheckable(false);
        ui->gpTask->setToolTip(task->GetDescription());
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
    ui->cbTask->addItem("CTaskActivity");
    return 0;
}

int CFrmTasks::SetSlider(int value)
{
    if(!m_Tasks)
    {
        qCritical() << "CFrmTasks::SetSlider: The m_Tasks is null";
        return -1;
    }
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
    if(!m_Tasks)
    {
        qCritical() << "CFrmTasks::on_pbAdd_clicked: The m_Tasks is null";
        return;
    }
    m_Tasks->Insert(task, m_Tasks->GetIndex(ui->vsLength->value())->GetId());
    //SetTask(task);
    SetSlider(ui->vsLength->value() + 1);
}

void CFrmTasks::on_pbRemove_clicked()
{
    if(!m_Tasks)
    {
        qCritical() << "CFrmTasks::on_pbRemove_clicked: The m_Tasks is null";
        return;
    }
    int nPos = ui->vsLength->value();
    m_Tasks->Remove(m_Tasks->GetIndex(nPos));
    SetTasks();
    SetSlider(nPos);
}

void CFrmTasks::on_pbClose_clicked()
{
    close();
}

void CFrmTasks::on_vsLength_valueChanged(int value)
{
    if(!m_Tasks)
    {
        qCritical() << "CFrmTasks::on_vsLength_valueChanged: The m_Tasks is null";
        return;
    }
    SetTask(m_Tasks->GetIndex(value));
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
    if(!m_Tasks)
        return;
    QSharedPointer<CTask> task = m_Tasks->GetIndex(ui->vsLength->value());
    if(!task)
        return;
    m_Tasks->SetTitle(ui->leTasksTitle->text());
    m_Tasks->SetContent(ui->teTasksContent->toPlainText());
    
    task->SetTitle(ui->leTaskTitle->text());
    task->SetContent(ui->teTaskContent->toPlainText());
    task->SetInterval(ui->spInterval->value() * 60 * 1000);
    task->SetPromptInterval(ui->spPromptInterval->value() * 1000);
    emit Changed();
}

void CFrmTasks::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if(!m_Tasks)
    {
        qCritical() << "CFrmTasks::closeEvent the m_Tasks is null";
        return;
    }
    m_Tasks.clear();
}

void CFrmTasks::on_leTasksTitle_editingFinished()
{
    m_Tasks->SetTitle(ui->leTasksTitle->text());
}

void CFrmTasks::on_teTasksContent_textChanged()
{
    m_Tasks->SetContent(ui->teTasksContent->toPlainText());
}

void CFrmTasks::on_leTaskTitle_editingFinished()
{
    m_Tasks->GetIndex(ui->vsLength->value())->SetTitle(ui->leTaskTitle->text());
}

void CFrmTasks::on_teTaskContent_textChanged()
{
    m_Tasks->GetIndex(ui->vsLength->value())->SetContent(ui->teTaskContent->toPlainText());
}

void CFrmTasks::on_spPromptInterval_valueChanged(int arg1)
{
    m_Tasks->GetIndex(ui->vsLength->value())->SetPromptInterval(arg1 * 1000);
}

void CFrmTasks::on_spInterval_valueChanged(int arg1)
{
    m_Tasks->GetIndex(ui->vsLength->value())->SetInterval(arg1 * 60 * 1000);
}

void CFrmTasks::on_pbTasksIcon_clicked()
{
    QFileDialog fd(this, tr("Open file"), QString(), tr("png(*.png);;icon(*.icon);;jpg(*.jpg);;bmp(*.bmp);;All files(*.*)"));
    int n = fd.exec();
    if(QDialog::Rejected == n)
        return;
    m_Tasks->SetIcon(QIcon(fd.selectedFiles().at(0)));
    ui->pbTasksIcon->setIcon(m_Tasks->GetIcon());    
}

void CFrmTasks::on_pbTaskIcon_clicked()
{
    QFileDialog fd(this, tr("Open file"), QString(), tr("png(*.png);;icon(*.icon);;jpg(*.jpg);;bmp(*.bmp);;All files(*.*)"));
    int n = fd.exec();
    if(QDialog::Rejected == n)
        return;
    int v = ui->vsLength->value();
    QSharedPointer<CTask> t = m_Tasks->GetIndex(v);
    if(!t)
        return;
    t->SetIcon(QPixmap(fd.selectedFiles().at(0)));
    ui->pbTaskIcon->setIcon(t->GetIcon());
}
