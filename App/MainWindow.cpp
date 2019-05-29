#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DlgAbout/DlgAbout.h"
#include "Global/TasksTools.h"
#include "Global/GlobalDir.h"
#include "FrmUpdater/FrmUpdater.h"
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
#include <DlgOption.h>
#include <QScrollArea>
#include <QSize>
#include <QScrollBar>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow),
    m_Table(this)
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
    m_pStartRun->setChecked(CTasksTools::IsStartRunCurrentUser());
    
    bool check = connect(&m_TrayIcon,
                    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this,
                    SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));
    Q_ASSERT(check);
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    m_TrayIcon.show();
    
    m_Table.addTab(&m_frmCalendar, m_frmCalendar.windowIcon(), m_frmCalendar.windowTitle());
    m_Table.addTab(&m_frmStickyList, m_frmStickyList.windowIcon(), m_frmStickyList.windowTitle());
    m_Table.addTab(&m_FrmTasksList, m_FrmTasksList.windowIcon(), m_FrmTasksList.windowTitle());
    m_Table.setTabPosition(QTabWidget::South);
    
#if defined (Q_OS_ANDROID)
    m_Table.setGeometry(this->geometry());
    QScrollArea *pScrollArea = new QScrollArea(this);
    pScrollArea->setGeometry(this->geometry());
    pScrollArea->setWidget(&m_Table);
    pScrollArea->show();
    setCentralWidget(pScrollArea);
#else
    setCentralWidget(&m_Table);
#endif
    
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    m_Table.setCurrentIndex(set.value("Options/MainWindow/TableView", 0).toInt());
    
#ifdef RABBITCOMMON
    m_frmUpdater.SetTitle(QPixmap(":/icon/App"));
#endif
}

CMainWindow::~CMainWindow()
{
    delete ui;
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    set.setValue("Options/MainWindow/TableView", m_Table.currentIndex());
}

void CMainWindow::slotAbout()
{
#ifdef RABBITCOMMON
    CDlgAbout about(this);
    about.m_AppIcon = QPixmap(":/icon/App");
    about.m_szHomePage = "https://github.com/KangLin/Tasks";
    if(about.isHidden())
        about.exec();
#endif
}

void CMainWindow::slotExit()
{
    qApp->quit();
}

void CMainWindow::slotShow()
{
    qDebug() << "CMainWindow::slotShow()";
    
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
    if(CTasksTools::IsStartRunCurrentUser())
    {
        CTasksTools::RemoveStartRunCurrentUser();
    }
    else
    {
        CTasksTools::InstallStartRunCurrentUser();
    }
    
    if(CTasksTools::IsStartRunCurrentUser())
        m_pStartRun->setChecked(true);
    else
        m_pStartRun->setChecked(false);
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
#ifdef RABBITCOMMON
    #if defined (Q_OS_ANDROID)
        m_frmUpdater.showMaximized();
    #else
        m_frmUpdater.show();
    #endif
#endif
}

void CMainWindow::on_actionSticky_list_L_triggered()
{
    this->takeCentralWidget();
    setCentralWidget(&m_frmStickyList);
    m_frmStickyList.show();
}

void CMainWindow::on_actionTasks_list_A_triggered()
{
    this->takeCentralWidget();
    setCentralWidget(&m_FrmTasksList);
    m_FrmTasksList.show();
}

void CMainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
#if defined (Q_OS_ANDROID)
    QScrollArea *pScrollArea = dynamic_cast<QScrollArea *>(centralWidget());
    pScrollArea->resize(event->size());
    QSize s = m_Table.size();
    int width = pScrollArea->width();
    int height = pScrollArea->height();
    if(!pScrollArea->verticalScrollBar()->isHidden())
        width -= pScrollArea->verticalScrollBar()->frameGeometry().width();
    if(!pScrollArea->horizontalScrollBar()->isHidden())
        height -= pScrollArea->horizontalScrollBar()->frameGeometry().height();
    
    if(s.width() < width)
        s.setWidth(width);
    if(s.height() < height)
        s.setHeight(height);
    if(s != m_Table.size())
        m_Table.resize(s);
#endif
}

void CMainWindow::hideEvent(QHideEvent *event)
{
    m_pShow->setText(tr("Show"));
}
