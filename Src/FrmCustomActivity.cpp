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

void CFrmCustomActivity::on_rbLoopCount_clicked()
{
    ui->deUntil->setVisible(false);
    ui->spCount->setVisible(true);
}

int CFrmCustomActivity::SetRepeat(CTaskActivity::_ENUM_REPEAT r)
{
    switch (r) {
    case CTaskActivity::CustomDay:
        ui->rbDays->click();
        break;
    case CTaskActivity::CustomWeek:
        ui->rbWeeks->click();
        break;
    case CTaskActivity::CustomMonth:
        ui->rbMonths->click();
        break;
    case CTaskActivity::CustomYear:
        ui->rbYears->click();
        break;
    default:
        break;
    }
    return 0;
}

CTaskActivity::_ENUM_REPEAT CFrmCustomActivity::GetRepeat() const
{
    return m_Repeat;
}

int CFrmCustomActivity::SetNumber(int n)
{
    ui->spNumber->setValue(n);
    return 0;
}

int CFrmCustomActivity::GetNumber() const
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

void CFrmCustomActivity::SetWeek(int w)
{
    if(1 & w)
        ui->cbMonday->setChecked(true);
    else
        ui->cbMonday->setChecked(false);
    
    if(2 & w)
        ui->cbTuesday->setChecked(true);
    else
        ui->cbTuesday->setChecked(false);
    
    if(4 & w)
        ui->cbWednesday->setChecked(true);
    else
        ui->cbWednesday->setChecked(false);
    
    if(8 & w)
        ui->cbThursday->setChecked(true);
    else
        ui->cbThursday->setChecked(false);
    
    if(16 & w)
        ui->cbFriday->setChecked(true);
    else
        ui->cbFriday->setChecked(false);
    
    if(32 & w)
        ui->cbSaturday->setChecked(true);
    else
        ui->cbSaturday->setChecked(false);
    
    if(64 & w)
        ui->cbSunday->setChecked(true);
    else
        ui->cbSunday->setChecked(false);
}

int CFrmCustomActivity::GetWeek() const
{
    int w = 0;
    QVector<int> r;
    if(ui->cbMonday->isChecked())
        w |= 1;
    if(ui->cbTuesday->isChecked())
        w |= 2;
    if(ui->cbWednesday->isChecked())
        w |= 4;
    if(ui->cbThursday->isChecked())
        w |= 8;
    if(ui->cbFriday->isChecked())
        w |= 16;
    if(ui->cbSaturday->isChecked())
        w |= 32;
    if(ui->cbSunday->isChecked())
        w |= 64;
    return w;
}

int CFrmCustomActivity::SetEffective(CTaskActivity::_ENUM_EFFECTIVE e)
{
    switch (e) {
    case CTaskActivity::Always:
        ui->rbAlways->click();
        break;
    case CTaskActivity::Until:
        ui->rbUntil->click();
        break;
    case CTaskActivity::LoopCount:
        ui->rbLoopCount->click();
        break;
    }
    return 0;
}

CTaskActivity::_ENUM_EFFECTIVE CFrmCustomActivity::GetEffective() const
{
    if(ui->rbAlways->isChecked())
        return CTaskActivity::Always;
    if(ui->rbUntil->isChecked())
        return CTaskActivity::Until;
    if(ui->rbLoopCount->isChecked())
        return CTaskActivity::LoopCount;
    return CTaskActivity::Always;
}

int CFrmCustomActivity::SetUntil(QDate d)
{
    ui->deUntil->setDate(d);
    return 0;
}

QDate CFrmCustomActivity::GetUntil()
{
    return ui->deUntil->date();
}

int CFrmCustomActivity::SetLoopCount(int n)
{
    ui->spCount->setValue(n);
    return 0;
}

int CFrmCustomActivity::GetLoopCount()
{
    return ui->spCount->value();
}
