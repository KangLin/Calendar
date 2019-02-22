#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DlgAbout/DlgAbout.h"
#include "Global/Tool.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    m_TrayIconMenu.addAction(
                QIcon(":/icon/Close"),
                tr("Exit"),
                this,
                SLOT(slotExit(bool)));
#if !(defined (_DEBUG) || defined(DEBUG))
    hide();
#endif
    QString szShow = tr("Hide");
    if(isHidden())
        szShow = tr("Show");
    m_pShow = m_TrayIconMenu.addAction(windowIcon(), szShow,
                                       this, SLOT(slotShow(bool)));
    m_TrayIconMenu.addAction(QIcon(":/icon/App"),
                             tr("About"),
                             this,
                             SLOT(slotAbout(bool)));

    m_pStartRun = m_TrayIconMenu.addAction(tr("Enable run from boot"), this, SLOT(slotStartRun(bool)));
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
    this->setCentralWidget(m_pFrmTasksList);
}

CMainWindow::~CMainWindow()
{
    delete ui;
    if(m_pFrmTasksList)
        delete m_pFrmTasksList;
}

void CMainWindow::slotAbout(bool checked)
{
    Q_UNUSED(checked);
    static CDlgAbout dlg;
    if(dlg.isHidden())
        dlg.exec();
}

void CMainWindow::slotExit(bool checked)
{
    Q_UNUSED(checked);
    qApp->quit();
}

void CMainWindow::slotShow(bool checked)
{
    Q_UNUSED(checked);
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
        slotShow(true);
}

void CMainWindow::on_actionExit_E_triggered()
{
    qApp->quit();
}

void CMainWindow::on_actionAbout_A_triggered()
{
    slotAbout(true);
}
