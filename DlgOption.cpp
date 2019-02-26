#include "DlgOption.h"
#include "ui_DlgOption.h"
#include "Global/Tool.h"
#include "Global/GlobalDir.h"
#include <QSettings>

CDlgOption::CDlgOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgOption)
{
    ui->setupUi(this);
    
    if(CTool::IsStartRunOnceCurrentUser())
        ui->cbRunFromBoot->setChecked(true);
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    bool bShow = set.value("MainWindow/Show", false).toBool();
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
        CTool::InstallStartRunOnceCurrentUser();
    }
    else
    {
        CTool::RemoveStartRunOnceCurrentUser();
    }
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    if(ui->cbShowMainWindows->checkState() == Qt::Checked)
        set.setValue("MainWindow/Show", true);
    else
        set.setValue("MainWindow/Show", false);
    
}
