// 作者：康林 <kl222@126.com>

#include "DlgTaskActivity.h"
#include "FrmCustomActivity.h"
#include "DlgContainer.h"
#include "ui_DlgTaskActivity.h"
#include <QScrollArea>
#include <QtDebug>
#include <QInputDialog>
#include <QMessageBox>

CDlgTaskActivity::CDlgTaskActivity(CTaskActivity *task, QWidget *parent) :
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
    case CTaskActivity::CustomDay:
    case CTaskActivity::CustomWeek:
    case CTaskActivity::CustomMonth:
    case CTaskActivity::CustomYear:
        ui->rbCustom->setChecked(true);
        break;
    default:
        
        qDebug() << "task->GetRepeat():" << task->GetRepeat() << " is not know";
    }
    m_CustomNumber = task->GetCustomNumber();
    m_Week = task->GetWeek();
    m_Effective = task->GetEffective();
    m_UntilDate = task->GetUntil();
    m_LoopCount = task->GetLoopCount();
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
    m_Task->SetCustomNumber(m_CustomNumber);
    m_Task->SetWeek(m_Week);
    m_Task->SetEffective(m_Effective);
    m_Task->SetUntil(m_UntilDate);
    m_Task->SetLoopCount(m_LoopCount);
    
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
    CFrmCustomActivity* p = new CFrmCustomActivity();
    p->SetRepeat(m_Repeat);
    p->SetNumber(m_CustomNumber);
    p->SetWeek(m_Week);
    p->SetEffective(m_Effective);
    p->SetUntil(m_UntilDate);
    p->SetLoopCount(m_LoopCount);
    
    CDlgContainer dlg;
    dlg.SetWidget(p);
#if defined (Q_OS_ANDROID)
    dlg.showMaximized();
#endif
    if(QDialog::Accepted == dlg.ExtendExec())
    {
        m_Repeat = p->GetRepeat();
        m_CustomNumber = p->GetNumber();
        m_Week = p->GetWeek();
        m_Effective = p->GetEffective();
        m_UntilDate = p->GetUntil();
        m_LoopCount = p->GetLoopCount();
    }
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

void CDlgTaskActivity::on_dtStart_dateChanged(const QDate &date)
{
    if(date > ui->dtEnd->date())
        ui->dtEnd->setDate(date);
    if(date == ui->dtEnd->date())
        if(ui->tmStart->time() > ui->tmEnd->time())
            ui->tmEnd->setTime(ui->tmStart->time().addSecs(3600));
}

void CDlgTaskActivity::on_dtEnd_dateChanged(const QDate &date)
{
    if(date < ui->dtStart->date())
        ui->dtStart->setDate(date);
    if(date == ui->dtEnd->date())
        if(ui->tmStart->time() > ui->tmEnd->time())
            ui->tmStart->setTime(ui->tmEnd->time().addSecs(-3600));
}

void CDlgTaskActivity::on_tmStart_timeChanged(const QTime &time)
{
    if(ui->dtStart->date() == ui->dtEnd->date())
        if(time > ui->tmEnd->time())
            ui->tmEnd->setTime(time.addSecs(3600));
}

void CDlgTaskActivity::on_tmEnd_timeChanged(const QTime &time)
{
    if(ui->dtStart->date() == ui->dtEnd->date())
        if(time < ui->tmStart->time())
            ui->tmStart->setTime(time.addSecs(-3600));
}
