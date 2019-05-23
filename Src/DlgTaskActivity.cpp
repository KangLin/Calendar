#include "DlgTaskActivity.h"
#include "ui_DlgTaskActivity.h"
#include <QScrollArea>
#include <QtDebug>
#include <QInputDialog>

CDlgTaskActivity::CDlgTaskActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgTaskActivity),
    m_Task(new CTaskActivity())
{
    //setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    Init();
    
}

CDlgTaskActivity::CDlgTaskActivity(QSharedPointer<CTaskActivity> task,
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
    m_pModel = new QStandardItemModel(this);
    ui->lstPromt->setModel(m_pModel);
    SetTask(m_Task);
    return 0;
}

QSharedPointer<CTaskActivity> CDlgTaskActivity::GetTask()
{
    return m_Task;
}

int CDlgTaskActivity::SetTask(QSharedPointer<CTaskActivity> task)
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

    QString szPrompt = m_Task->GetPrompt();
    QStringList lstPrompt = szPrompt.split(',');
    foreach(QString s, lstPrompt)
    {
        QStandardItem* pItem = new QStandardItem(s + tr(" Minutes"));
        pItem->setData(s);
        m_pModel->appendRow(pItem);
    }
    return 0;
}

int CDlgTaskActivity::ApplyTask()
{
    m_Task->SetTitle(ui->leTitle->text());
    m_Task->SetPlace(ui->lePlace->text());
    m_Task->SetAccount(ui->leAccount->text());
    m_Task->SetContent(ui->teContent->toPlainText());
    m_Task->SetDateStart(ui->dtStart->date().year(),
                         ui->dtStart->date().month(),
                         ui->dtStart->date().day());
    m_Task->SetDateEnd(ui->dtEnd->date().year(),
                       ui->dtEnd->date().month(),
                       ui->dtEnd->date().day());
    m_Task->SetTimeStart(ui->tmStart->time());
    m_Task->SetTimeEnd(ui->tmEnd->time());

    QString szPrompt;    
    
    int i = 0;
    QModelIndex index;
    do
    {
        QStandardItem* pItem = m_pModel->item(i++);
        if(pItem)
            m_Task->AddPrompt(pItem->data().toString().toInt());
    }while(index.isValid());
    
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
    m_Task->SetTypeDate(CTaskActivity::Solar);
}

void CDlgTaskActivity::on_rbLunar_clicked()
{
    m_Task->SetTypeDate(CTaskActivity::Lunar);
}

void CDlgTaskActivity::on_rbOnce_clicked()
{
    m_Task->SetRepeat(CTaskActivity::Once);
}

void CDlgTaskActivity::on_rbEveryDay_clicked()
{
    m_Task->SetRepeat(CTaskActivity::EveryDay);
}

void CDlgTaskActivity::on_rbWeekly_clicked()
{
    m_Task->SetRepeat(CTaskActivity::Weekly);
}

void CDlgTaskActivity::on_rbMonthly_clicked()
{
    m_Task->SetRepeat(CTaskActivity::Monthly);
}

void CDlgTaskActivity::on_rbEveryYear_clicked()
{
    m_Task->SetRepeat(CTaskActivity::EveryYear);
}

void CDlgTaskActivity::on_rbCustom_clicked()
{
    m_Task->SetRepeat(CTaskActivity::Custom);
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
    m_pModel->appendRow(pItem);
}

void CDlgTaskActivity::on_pbPromptRemove_clicked()
{
    m_pModel->removeRow(ui->lstPromt->currentIndex().row());
}
