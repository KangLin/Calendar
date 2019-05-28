#include "DlgTaskActivity.h"
#include "ui_DlgTaskActivity.h"
#include <QScrollArea>
#include <QtDebug>
#include <QInputDialog>
#include <QMessageBox>

CDlgTaskActivity::CDlgTaskActivity(CTaskActivity *task,
                                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgTaskActivity)
{
    //setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    m_Task = task;
    Init();
}

CDlgTaskActivity::~CDlgTaskActivity()
{
    qDebug() << "CDlgTaskActivity::~CDlgTaskActivity()";
    delete ui;
}

int CDlgTaskActivity::Init()
{
    m_pModelPrompt = new QStandardItemModel(this);
    ui->lstPromt->setModel(m_pModelPrompt);
    SetTask(m_Task);
    return 0;
}

CTaskActivity *CDlgTaskActivity::GetTask()
{
    return m_Task;
}

int CDlgTaskActivity::SetTask(CTaskActivity *task)
{
    if(!task) return -1;
    
    m_Task = task;
    ui->leTitle->setText(m_Task->GetTitle());
    ui->lePlace->setText(m_Task->GetPlace());
    ui->leAccount->setText(m_Task->GetAccount());
    ui->teContent->setText(m_Task->GetContent());
    CTaskActivity::CDate date;
    m_Task->GetDateStart(date);
    ui->dtStart->setDate(QDate(date.Year, date.Month, date.Day));
    m_Task->GetDateEnd(date);
    ui->dtEnd->setDate(QDate(date.Year, date.Month, date.Day));
    ui->tmStart->setTime(m_Task->GetTimeStart());
    ui->tmEnd->setTime(m_Task->GetTimeEnd());

    m_TypeDate = task->GetTypeDate();
    if(task->GetTypeDate() == CTaskActivity::Lunar)
        ui->rbLunar->setChecked(true);
    if(task->GetTypeDate() == CTaskActivity::Solar)
        ui->rbSolar->setChecked(true);
    m_Repeat = task->GetRepeat();
    switch (task->GetRepeat())
    {
    case CTaskActivity::Once:
        ui->rbOnce->setChecked(true);
        break;
    case CTaskActivity::EveryDay:
        ui->rbEveryDay->setChecked(true);
        break;
    case CTaskActivity::Weekly:
        ui->rbWeekly->setChecked(true);
        break;
    case CTaskActivity::Monthly:
        ui->rbMonthly->setChecked(true);
        break;
    case CTaskActivity::EveryYear:
        ui->rbEveryYear->setChecked(true);
        break;
    default:
        qDebug() << "task->GetRepeat():" << task->GetRepeat() << " is not know";
    }
    m_pModelPrompt->clear();
    QString szPrompt = m_Task->GetPrompt();
    QStringList lstPrompt = szPrompt.split(',');
    foreach(QString s, lstPrompt)
    {
        QStandardItem* pItem = new QStandardItem(s + tr(" Minutes"));
        pItem->setData(s);
        m_pModelPrompt->appendRow(pItem);
    }
    return 0;
}

int CDlgTaskActivity::ApplyTask()
{
    m_Task->SetTitle(ui->leTitle->text());
    m_Task->SetPlace(ui->lePlace->text());
    m_Task->SetAccount(ui->leAccount->text());
    m_Task->SetContent(ui->teContent->toPlainText());
    if(ui->dtStart->date() > ui->dtEnd->date())
        ui->dtStart->setDate(ui->dtEnd->date());
    m_Task->SetDateStart(ui->dtStart->date().year(),
                         ui->dtStart->date().month(),
                         ui->dtStart->date().day());
    m_Task->SetDateEnd(ui->dtEnd->date().year(),
                       ui->dtEnd->date().month(),
                       ui->dtEnd->date().day());
    m_Task->SetTimeStart(ui->tmStart->time());
    m_Task->SetTimeEnd(ui->tmEnd->time());
    m_Task->SetTypeDate(m_TypeDate);
    m_Task->SetRepeat(m_Repeat);

    QString szPrompt;

    int i = 0;
    m_Task->SetPrompt(""); //Clear
    while(1)
    {
        QStandardItem* pItem = m_pModelPrompt->item(i++);
        if(pItem)
            m_Task->AddPrompt(pItem->data().toString().toInt());
        else 
            break;
    }

    return 0;
}

void CDlgTaskActivity::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
}

void CDlgTaskActivity::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
}

void CDlgTaskActivity::on_pbOk_clicked()
{
    ApplyTask();
    accept();
}

void CDlgTaskActivity::on_pbCancel_clicked()
{
    this->reject();
}

void CDlgTaskActivity::on_rbSolar_clicked()
{
    m_TypeDate = CTaskActivity::Solar;
}

void CDlgTaskActivity::on_rbLunar_clicked()
{
    m_TypeDate = CTaskActivity::Lunar;
}

void CDlgTaskActivity::on_rbOnce_clicked()
{
    m_Repeat = CTaskActivity::Once;
}

void CDlgTaskActivity::on_rbEveryDay_clicked()
{
    m_Repeat = CTaskActivity::EveryDay;
}

void CDlgTaskActivity::on_rbWeekly_clicked()
{
    m_Repeat = CTaskActivity::Weekly;
}

void CDlgTaskActivity::on_rbMonthly_clicked()
{
    m_Repeat = CTaskActivity::Monthly;
}

void CDlgTaskActivity::on_rbEveryYear_clicked()
{
    m_Repeat = CTaskActivity::EveryYear;
}

void CDlgTaskActivity::on_rbCustom_clicked()
{
    m_Repeat = CTaskActivity::Custom;
}

void CDlgTaskActivity::on_pbPromptAdd_clicked()
{
    bool ok = false;
    int n = QInputDialog::getInt(this,
                                 tr("Prompt"),
                                 tr("prompt (Unit: minute)"),
                                 -5,
                                 -2147483647,
                                 2147483647,
                                 1,
                                 &ok);
    if(!ok)
        return;
    
    QStandardItem* pItem = new QStandardItem(QString::number(n) + tr(" Minutes"));
    pItem->setData(n);
    m_pModelPrompt->appendRow(pItem);
}

void CDlgTaskActivity::on_pbPromptRemove_clicked()
{
    m_pModelPrompt->removeRow(ui->lstPromt->currentIndex().row());
}
