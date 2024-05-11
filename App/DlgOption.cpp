#include "DlgOption.h"
#include "ui_DlgOption.h"
#include "Global/TasksTools.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include <QSettings>
#include "LunarCalendar.h"
#include <QLoggingCategory>

static Q_LOGGING_CATEGORY(log, "Rabbit.LunarCalendar.Option")

CDlgOption::CDlgOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgOption)
{
    ui->setupUi(this);
    
    ui->cbRunFromBoot->setChecked(RabbitCommon::CTools::IsStartRun());
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    bool bShow = set.value("Options/MainWindow/Show", false).toBool();
    ui->cbShowMainWindows->setChecked(bShow);
    int nType = set.value("Options/Calendar/Type", 0).toInt();
    if(0 == nType)
        ui->cbAutomation->setChecked(true);
    if(static_cast<int>(CLunarCalendar::_CalendarType::CalendarTypeSolar) & nType)
        ui->cbSolar->setChecked(true);
    if(static_cast<int>(CLunarCalendar::_CalendarType::CalendarTypeLunar) & nType)
        ui->cbLunar->setChecked(true);
}

CDlgOption::~CDlgOption()
{
    delete ui;
}

void CDlgOption::on_buttonBox_accepted()
{
    if(ui->cbRunFromBoot->checkState() == Qt::Checked)
        RabbitCommon::CTools::InstallStartRun();
    else
        RabbitCommon::CTools::RemoveStartRun();

    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    set.setValue("Options/MainWindow/Show", ui->cbShowMainWindows->isChecked());
    if(ui->cbAutomation->isChecked())
         set.setValue("Options/Calendar/Type", 0);
    else {
        int nType = 0;
        nType = set.value("Options/Calendar/Type", 0).toInt();
        if(ui->cbSolar->isChecked()) 
        {
            nType |= static_cast<int>(CLunarCalendar::_CalendarType::CalendarTypeSolar);
        } else {
            nType &= ~static_cast<int>(CLunarCalendar::_CalendarType::CalendarTypeSolar);
        }
        if(ui->cbLunar->isChecked()) {
            nType |= static_cast<int>(CLunarCalendar::_CalendarType::CalendarTypeLunar);
        } else {
            nType &= ~static_cast<int>(CLunarCalendar::_CalendarType::CalendarTypeLunar);
        }
        set.setValue("Options/Calendar/Type", nType);
    }
}

void CDlgOption::on_cbAutomation_toggled(bool checked)
{
    qDebug(log) << "on_cbAutomation_clicked";
    if(checked) {
        ui->cbLunar->setEnabled(false);
        ui->cbSolar->setEnabled(false);
    } else {
        ui->cbLunar->setEnabled(true);
        ui->cbSolar->setEnabled(true);
    }
}
