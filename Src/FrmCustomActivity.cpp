#include "FrmCustomActivity.h"
#include "ui_FrmCustomActivity.h"

CFrmCustomActivity::CFrmCustomActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmCustomActivity)
{
    ui->setupUi(this);

    ui->cmbType->addItem(tr("Days"));
    ui->cmbType->addItem(tr("Weeks"));
    ui->cmbType->addItem(tr("Months"));
    ui->cmbType->addItem(tr("Years"));
    
    ui->wdtWeek->setVisible(false);
    ui->rbAlways->click();
}

CFrmCustomActivity::~CFrmCustomActivity()
{
    delete ui;
}

void CFrmCustomActivity::on_rbDays_clicked()
{
    ui->wdtWeek->setVisible(false);
    ui->cmbType->setCurrentIndex(0);
    m_Repeat = CTaskActivity::CustomDay;
}

void CFrmCustomActivity::on_rbWeeks_clicked()
{
    ui->wdtWeek->setVisible(true);
    ui->cmbType->setCurrentIndex(1);
    m_Repeat = CTaskActivity::CustomWeek;
}

void CFrmCustomActivity::on_rbMonths_clicked()
{
    ui->wdtWeek->setVisible(false);
    ui->cmbType->setCurrentIndex(2);
    m_Repeat = CTaskActivity::CustomMonth;
}

void CFrmCustomActivity::on_rbYears_clicked()
{
    ui->wdtWeek->setVisible(false);
    ui->cmbType->setCurrentIndex(3);
    m_Repeat = CTaskActivity::CustomYear;
}

void CFrmCustomActivity::on_rbAlways_clicked()
{
    ui->deUntil->setVisible(false);
    ui->spCount->setVisible(false);
}

void CFrmCustomActivity::on_rbUntil_clicked()
{
    ui->deUntil->setVisible(true);
    ui->spCount->setVisible(false);
}

void CFrmCustomActivity::on_rbCount_clicked()
{
    ui->deUntil->setVisible(false);
    ui->spCount->setVisible(true);
}

int CFrmCustomActivity::GetNumber()
{
    return ui->spNumber->value();
}

void CFrmCustomActivity::on_cmbType_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->rbDays->click();
        break;
    case 1:
        ui->rbWeeks->click();
        break;
    case 2:
        ui->rbMonths->click();
        break;
    case 3:
        ui->rbYears->click();
        break;
    }
}

void CFrmCustomActivity::SetWeek(Qt::DayOfWeek week)
{
    switch (week) {
    case Qt::DayOfWeek::Monday:
        ui->cbMonday->setChecked(true);
        break;
    case Qt::DayOfWeek::Tuesday:
        ui->cbTuesday->setChecked(true);
        break;
    case Qt::DayOfWeek::Wednesday:
        ui->cbWednesday->setChecked(true);
        break;
    case Qt::DayOfWeek::Thursday:
        ui->cbThursday->setChecked(true);
        break;
    case Qt::DayOfWeek::Friday:
        ui->cbFriday->setChecked(true);
        break;
    case Qt::DayOfWeek::Saturday:
        ui->cbSaturday->setChecked(true);
        break;
    case Qt::DayOfWeek::Sunday:
        ui->cbSunday->setChecked(true);
    }
}

QVector<int> CFrmCustomActivity::GetWeek()
{
    QVector<int> r;
    if(ui->cbMonday->isChecked())
        r.push_back(Qt::DayOfWeek::Monday);
    if(ui->cbTuesday->isChecked())
        r.push_back(Qt::DayOfWeek::Tuesday);
    if(ui->cbWednesday->isChecked())
        r.push_back(Qt::DayOfWeek::Wednesday);
    if(ui->cbThursday->isChecked())
        r.push_back(Qt::DayOfWeek::Thursday);
    if(ui->cbFriday->isChecked())
        r.push_back(Qt::DayOfWeek::Friday);
    if(ui->cbSaturday->isChecked())
        r.push_back(Qt::DayOfWeek::Saturday);
    if(ui->cbSunday->isChecked())
        r.push_back(Qt::DayOfWeek::Sunday);
    return r;
}

QDate CFrmCustomActivity::GetUntil()
{
    return ui->deUntil->date();
}

int CFrmCustomActivity::GetCount()
{
    return ui->spCount->value();
}
