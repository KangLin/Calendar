#include "DlgOption.h"
#include "ui_DlgOption.h"
#include "Global/TasksTools.h"
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include <QSettings>

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
}

CDlgOption::~CDlgOption()
{
    delete ui;
}

void CDlgOption::on_buttonBox_accepted()
{
    if(ui->cbRunFromBoot->checkState() == Qt::Checked)
    {
        RabbitCommon::CTools::InstallStartRun();
    }
    else
    {
        RabbitCommon::CTools::RemoveStartRun();
    }
    
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    set.setValue("Options/MainWindow/Show", ui->cbShowMainWindows->isChecked());    
}
