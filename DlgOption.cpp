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
    
    ui->cbRunFromBoot->setChecked(CTool::IsStartRunOnceCurrentUser());
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    bool bShow = set.value("Options/MainWindow/Show", false).toBool();
    ui->cbShowMainWindows->setChecked(bShow);
    bShow = set.value("Options/Sticky/Show", false).toBool();
    ui->cbStickyList->setChecked(bShow);
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
        set.setValue("Options/MainWindow/Show", true);
    else
        set.setValue("Options/MainWindow/Show", false);
    if(ui->cbStickyList->checkState() == Qt::Checked)
        set.setValue("Options/Sticky/Show", true);
    else
        set.setValue("Options/Sticky/Show", false);
}
