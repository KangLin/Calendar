#include "FrmCustomActivity.h"
#include "ui_FrmCustomActivity.h"

CFrmCustomActivity::CFrmCustomActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmCustomActivity)
{
    ui->setupUi(this);

    ui->cmbType->addItem(tr("Years"));
    ui->cmbType->addItem(tr("Months"));
    ui->cmbType->addItem(tr("Weeks"));
    ui->cmbType->addItem(tr("Days"));
    //ui->cmbType->setVisible(false);
    //ui->spNumber->setVisible(false);
    ui->wdtWeek->setVisible(false);
}

CFrmCustomActivity::~CFrmCustomActivity()
{
    delete ui;
}

void CFrmCustomActivity::on_rbWeeks_clicked()
{
    ui->wdtWeek->setVisible(true);
}

void CFrmCustomActivity::on_rbDays_clicked()
{
    ui->wdtWeek->setVisible(false);
}

void CFrmCustomActivity::on_rbMonths_clicked()
{
    ui->wdtWeek->setVisible(false);
}

void CFrmCustomActivity::on_rbYears_clicked()
{
    ui->wdtWeek->setVisible(false);
}
