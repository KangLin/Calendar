#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DlgAbout/DlgAbout.h"
#include "Global/TasksTools.h"
#include "RabbitCommonDir.h"
#include <QSettings>
#include <QDebug>
#include <QFileDialog>
#include <DlgOption.h>
#include <QScrollArea>
#include <QSize>
#include <QScrollBar>

#ifdef RABBITCOMMON
    #include "FrmUpdater/FrmUpdater.h"
    #include "RabbitCommonTools.h"
#endif

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow),
    m_Table(this)
{
    //TODO: Modify style
#if !defined (Q_OS_ANDROID)
    LoadStyle();
#endif
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
    m_pStartRun->setChecked(RabbitCommon::CTools::IsStartRun());
    
    bool check = connect(&m_TrayIcon,
                    SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                    this,
                    SLOT(slotActivated(QSystemTrayIcon::ActivationReason)));
    Q_ASSERT(check);
    m_TrayIcon.setContextMenu(&m_TrayIconMenu);
    m_TrayIcon.setIcon(this->windowIcon());
    m_TrayIcon.setToolTip(this->windowTitle());
    m_TrayIcon.show();

    m_Table.addTab(&m_frmCalendar,
                   m_frmCalendar.windowIcon(), m_frmCalendar.windowTitle());
    m_Table.addTab(&m_frmStickyList,
                   m_frmStickyList.windowIcon(), m_frmStickyList.windowTitle());
#if defined (Q_OS_ANDROID)
    QScrollArea *pScrollArea = new QScrollArea(&m_Table);
    if(pScrollArea)
    {
        pScrollArea->setWidget(&m_FrmTasksList);
        pScrollArea->show();
        pScrollArea->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
        m_Table.addTab(pScrollArea, m_FrmTasksList.windowIcon(),
                       m_FrmTasksList.windowTitle());        
    }
    m_Table.installEventFilter(this);
#else
    m_Table.addTab(&m_FrmTasksList, m_FrmTasksList.windowIcon(),
                   m_FrmTasksList.windowTitle());    
#endif
    m_Table.setTabPosition(QTabWidget::South);
    setCentralWidget(&m_Table);
    
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    m_Table.setCurrentIndex(set.value("Options/MainWindow/TableView", 0).toInt());
}

CMainWindow::~CMainWindow()
{
    delete ui;
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
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
#if defined (Q_OS_ANDROID)
        about.showMaximized();
#endif
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
    {   
#if defined (Q_OS_ANDROID)
        showMaximized();
#else
        show();
#endif
        m_pShow->setText(tr("Hide"));
    }
    else {
        hide();
        m_pShow->setText(tr("Show"));
    }
}

void CMainWindow::slotStartRun(bool checked)
{
    if(RabbitCommon::CTools::IsStartRun())
    {
        RabbitCommon::CTools::RemoveStartRun();
    }
    else
    {
        RabbitCommon::CTools::InstallStartRun();
    }
    
    if(RabbitCommon::CTools::IsStartRun())
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
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    QString szFile = set.value("Sink",
                           #if defined (Q_OS_ANDROID)
                               QString("assets:/")
                           #else
                               RabbitCommon::CDir::Instance()->GetDirApplicationInstallRoot()
                               + QDir::separator()
                           #endif
                               + "Resource/dark/style.qss").toString();
    //qDebug() << "LoadStyle:" << szFile;
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
    QString szFile;
    szFile = RabbitCommon::CDir::OpenFileDialog(this, tr("Open sink"));
    
    LoadStyle(szFile);
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    set.setValue("Sink", szFile);
}

void CMainWindow::on_actionOption_O_triggered()
{
    CDlgOption dlg(this);
#if defined (Q_OS_ANDROID)
    dlg.showMaximized();
#endif
    dlg.exec();
}

void CMainWindow::on_actionUpdate_U_triggered()
{
#ifdef RABBITCOMMON
    CFrmUpdater* m_pfrmUpdater = new CFrmUpdater();
    m_pfrmUpdater->SetTitle(QPixmap(":/icon/App"));
    #if defined (Q_OS_ANDROID)
        m_pfrmUpdater->showMaximized();
    #else
        m_pfrmUpdater->show();
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
    m_Table.resize(event->size());
}

void CMainWindow::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    m_pShow->setText(tr("Show"));
}

bool CMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(&m_Table != watched)
        return false;

    switch (event->type()) {
    case QEvent::Resize:
        {
            QScrollArea *pScrollArea 
                    = dynamic_cast<QScrollArea*>(m_Table.widget(2));
            if(!pScrollArea) break;
            CFrmTasksList* pFrmTasksList 
                    = dynamic_cast<CFrmTasksList*>(pScrollArea->widget());
            if(&m_FrmTasksList != pFrmTasksList)
                break;
            
            QResizeEvent *resizeEvent = dynamic_cast<QResizeEvent*>(event);
            pScrollArea->resize(resizeEvent->size());
            
            //qDebug() << "tab:" << resizeEvent->size() << m_Table.currentIndex() << pScrollArea->size();
            
            QSize s = resizeEvent->size();
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
            if(s != pFrmTasksList->size())
                pFrmTasksList->resize(s);
        }   
        break;
    default:
        break;
    }
    return false;
}
