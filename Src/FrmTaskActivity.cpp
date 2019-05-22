#include "FrmTaskActivity.h"
#include "ui_FrmTaskActivity.h"
#include <QScrollArea>
#include <QtDebug>

CFrmTaskActivity::CFrmTaskActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTaskActivity),
    m_Task(new CTaskActivity())
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
}

CFrmTaskActivity::CFrmTaskActivity(QSharedPointer<CTaskActivity> task,
                                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmTaskActivity)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    SetTask(task);
}

CFrmTaskActivity::~CFrmTaskActivity()
{
    qDebug() << "CFrmTaskActivity::~CFrmTaskActivity()";
    delete ui;
}

int CFrmTaskActivity::SetTask(QSharedPointer<CTaskActivity> task)
{
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
    
    return 0;
}

int CFrmTaskActivity::ApplyTask()
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
    return 0;
}

void CFrmTaskActivity::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
}

void CFrmTaskActivity::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    ApplyTask();
}
