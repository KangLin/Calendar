#include "DlgOption.h"
#include "ui_DlgOption.h"
#include "Global/TasksTools.h"
#include "Global/GlobalDir.h"
#include <QSettings>

CDlgOption::CDlgOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgOption)
{
    ui->setupUi(this);
    
    ui->cbRunFromBoot->setChecked(CTasksTools::IsStartRunCurrentUser());
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
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
        CTasksTools::InstallStartRunCurrentUser();
    }
    else
    {
        CTasksTools::RemoveStartRunCurrentUser();
    }
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    if(ui->cbShowMainWindows->checkState() == Qt::Checked)
        set.setValue("Options/MainWindow/Show", true);
    else
        set.setValue("Options/MainWindow/Show", false);
}
