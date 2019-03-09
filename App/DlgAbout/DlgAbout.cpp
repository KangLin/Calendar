/*++
Copyright (c) Kang Lin studio, All Rights Reserved

Author:
    Kang Lin(kl222@126.com）

Module Name:

    DlgAbout.cpp

Abstract:

    This file contains about dialog implement.
 */

#include "DlgAbout.h"
#include "ui_DlgAbout.h"
#include <QFile>
#include <QDir>
#include "Global/GlobalDir.h"
/*
 * Author: KangLin(Email:kl222@126.com)
 */
#include <QDateTime>

CDlgAbout::CDlgAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgAbout)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_QuitOnClose, false);
    ui->lbVersion->setText(tr(" Version: ") + BUILD_VERSION + tr(" Arch:") + BUILD_ARCH);
    ui->lbDate->setText(tr("Build date:%1 %2").arg(__DATE__, __TIME__));
    ui->lbAuthor->setText(tr("Author: KangLin\nEmail:kl222@126.com"));
    ui->lbHome->setOpenExternalLinks(true);
    QString szHomePage = "https://github.com/KangLin/Tasks.git";
    ui->lbHome->setText(tr("Home page:") + "<a href=\"" + szHomePage + "\">"
                        + szHomePage + "</a>");
    ui->lbCopyright->setText(tr(" Copyright (C) 2018 - %1 KangLin Studio").arg(
                                 QString::number(QDate::currentDate().year())));

    AppendFile(ui->txtChange, "ChangeLog");
    AppendFile(ui->txtLicense, "LICENSE");
    AppendFile(ui->txtThinks, "Authors");
}

CDlgAbout::~CDlgAbout()
{
    delete ui;
}

int CDlgAbout::AppendFile(QTextEdit* pEdit, const QString &szFile)
{
    QString szFileLocation;
#if defined (Q_OS_ANDROID)
    szFileLocation = ":/file/" + szFile + "_" + QLocale().system().name();
#else
    szFileLocation = CGlobalDir::Instance()->GetDirApplication() + QDir::separator()
            + szFile + "_" + QLocale().system().name() + ".md";
    QDir d;
    if(!d.exists(szFileLocation))
        szFileLocation = CGlobalDir::Instance()->GetDirApplication() 
                + QDir::separator() + szFile + ".md";
#endif
    
    QFile readme(szFileLocation);
    if(readme.open(QFile::ReadOnly))
    {
        pEdit->append(readme.readAll());
        //把光标移动文档开始处  
        QTextCursor cursor =   pEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        pEdit->setTextCursor(cursor);
        readme.close();
    }
    return 0;
}

void CDlgAbout::on_pushButton_clicked()
{
    close();
}
