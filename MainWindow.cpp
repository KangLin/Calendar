#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DlgAbout/DlgAbout.h"
#include "Global/Tool.h"
#include "Global/GlobalDir.h"
#include "FrmUpdater.h"
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
#include <DlgOption.h>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    LoadStyle();
    ui->setupUi(this);
    m_TrayIconMenu.addAction(
                QIcon(":/icon/Close"),
                tr("Exit"),
                this,
                SLOT(slotExit()));

    QString szShow = tr("Hide");
    if(isHidden())
        szShow = tr("Show");
    m_pShow = m_TrayIconMenu.addAction(windowIcon(), szShow,
                                       this, SLOT(slotShow()));
    m_TrayIconMenu.addAction(QIcon(":/icon/App"),
                             tr("About"),
                             this,
                             SLOT(slotAbout()));

    m_pStartRun = m_TrayIconMenu.addAction(tr("Enable run from boot"),
                                           this, SLOT(slotStartRun(bool)));
    m_pStartRun->setCheckable(true);
    m_pStartRun->setChecked(CTool::IsStartRunOnceCurrentUser());
    
    bool check = connect(&m_TrayIcon,
                    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this,
                    SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));
    Q_ASSERT(check);
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    m_TrayIcon.show();

    m_pFrmTasksList = new CFrmTasksList(this);
    if(m_pFrmTasksList)
    {
        bool check = connect(ui->actionNew_N, SIGNAL(triggered()),
                             m_pFrmTasksList, SLOT(slotNew()));
        Q_ASSERT(check);
        check = connect(ui->actionRemove_R, SIGNAL(triggered()),
                        m_pFrmTasksList, SLOT(slotRemove()));
        Q_ASSERT(check);
        check = connect(ui->actionLoad_L, SIGNAL(triggered()),
                        m_pFrmTasksList, SLOT(slotLoad()));
        Q_ASSERT(check);
        check = connect(ui->actionSaveAs_S, SIGNAL(triggered()),
                        m_pFrmTasksList, SLOT(slotSaveAs()));
        Q_ASSERT(check);
        check = connect(ui->actionRefresh_F, SIGNAL(triggered()),
                        m_pFrmTasksList, SLOT(slotRefresh()));
        Q_ASSERT(check);
    }
    
    setCentralWidget(m_pFrmTasksList);
}

CMainWindow::~CMainWindow()
{
    delete ui;
    if(m_pFrmTasksList)
        delete m_pFrmTasksList;
}

void CMainWindow::slotAbout()
{
    static CDlgAbout dlg;
    if(dlg.isHidden())
        dlg.exec();
}

void CMainWindow::slotExit()
{
    qApp->quit();
}

void CMainWindow::slotShow()
{
    if(isHidden())
    {   show();
        m_pShow->setText(tr("Hide"));
    }
    else {
        hide();
        m_pShow->setText(tr("Show"));
    }
}

void CMainWindow::slotStartRun(bool checked)
{
    if(checked)
    {
        CTool::InstallStartRunOnceCurrentUser();
    }
    else
    {
        CTool::RemoveStartRunOnceCurrentUser();
    }
}

void CMainWindow::slotActivated(QSystemTrayIcon::ActivationReason r)
{
    if(QSystemTrayIcon::ActivationReason::Trigger == r)
        slotShow();
}

void CMainWindow::on_actionExit_E_triggered()
{
    qApp->quit();
}

void CMainWindow::on_actionAbout_A_triggered()
{
    slotAbout();
}

void CMainWindow::closeEvent(QCloseEvent *e)
{
    e->ignore();
    hide();
}

int CMainWindow::LoadStyle()
{
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    QString szFile = set.value("Sink",
                     CGlobalDir::Instance()->GetDirApplication()
                     + QDir::separator()
                     + "Resource/dark/style.qss").toString();
    return  LoadStyle(szFile);
}

int CMainWindow::LoadStyle(const QString &szFile)
{
    if(szFile.isEmpty())
        qApp->setStyleSheet("");
    else
    {
        QFile file(szFile);  
        if(file.open(QFile::ReadOnly))
        {
            QString stylesheet= file.readAll();
            qApp->setStyleSheet(stylesheet);
            file.close();
        }
        else
        {
            qDebug() << "file open file fail:" << szFile;                       
        }
    }
    return 0;
}

void CMainWindow::on_actionSink_S_triggered()
{
    QString szFile = QFileDialog::getOpenFileName(this, tr("Open sink"));
    if(szFile.isEmpty())
        return;
    LoadStyle(szFile);
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    set.setValue("Sink", szFile);
}

void CMainWindow::on_actionOption_O_triggered()
{
    CDlgOption dlg(this);
    dlg.exec();
}

void CMainWindow::on_actionUpdate_U_triggered()
{
    CFrmUpdater *fu = new CFrmUpdater();
    fu->show();
}

void CMainWindow::on_actionSticky_list_L_triggered()
{
    m_frmStickyList.show();
}
