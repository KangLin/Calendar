#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DlgAbout/DlgAbout.h"
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
    #include "FrmStyle.h"
#endif

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow),
    m_Table(this)
{
    ui->setupUi(this);

    m_TrayIconMenu.addAction(
                QIcon::fromTheme("window-close"),
                tr("Exit"),
                this,
                SLOT(slotExit()));

    QString szShow = tr("Hide");
    if(isHidden())
        szShow = tr("Show");
    m_pShow = m_TrayIconMenu.addAction(windowIcon(), szShow,
                                       this, SLOT(slotShow()));
    m_TrayIconMenu.addAction(windowIcon(), tr("About"),
                             this, SLOT(slotAbout()));

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

#if defined (Q_OS_ANDROID)
    QScrollArea *pScrollArea = new QScrollArea(&m_Table);
    if(pScrollArea)
    {
        //pScrollArea->installEventFilter(this);
        pScrollArea->setWidgetResizable(true);
        //pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //m_frmCalendar.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        pScrollArea->setWidget(&m_frmCalendar);
        pScrollArea->show();
        pScrollArea->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
        m_Table.addTab(pScrollArea, m_frmCalendar.windowIcon(),
                       m_frmCalendar.windowTitle());
        
    }
    pScrollArea = new QScrollArea(&m_Table);
    if(pScrollArea)
    {
        //pScrollArea->installEventFilter(this);
        pScrollArea->setWidgetResizable(true);
        pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pScrollArea->setWidget(&m_FrmTasksList);
        pScrollArea->show();
        pScrollArea->viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
        m_Table.addTab(pScrollArea, m_FrmTasksList.windowIcon(),
                       m_FrmTasksList.windowTitle());
    }

    m_Table.installEventFilter(this);
#else
    m_Table.addTab(&m_frmCalendar,
                   m_frmCalendar.windowIcon(), m_frmCalendar.windowTitle());
    m_Table.addTab(&m_FrmTasksList, m_FrmTasksList.windowIcon(),
                   m_FrmTasksList.windowTitle());
#endif
    m_Table.addTab(&m_frmStickyList,
                   m_frmStickyList.windowIcon(), m_frmStickyList.windowTitle());
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
    QIcon icon = windowIcon();
    if(icon.isNull()) return;
    auto sizeList = icon.availableSizes();
    if(sizeList.isEmpty()) return;
    QPixmap p = icon.pixmap(*sizeList.begin());
    about.m_AppIcon = p.toImage();
    about.m_szHomePage = "https://github.com/KangLin/Calendar";
    about.m_szCopyrightStartTime = "2019";
    about.m_szVersionRevision = Calendar_VERSION_REVISION;
    if(about.isHidden())
#if defined (Q_OS_ANDROID)
        about.showMaximized();
#endif
        about.exec();
#endif
}

void CMainWindow::on_actionUpdate_U_triggered()
{
#ifdef RABBITCOMMON
    CFrmUpdater* m_pfrmUpdater = new CFrmUpdater();
    QIcon icon = windowIcon();
    if(icon.isNull()) return;
    auto sizeList = icon.availableSizes();
    if(sizeList.isEmpty()) return;
    QPixmap p = icon.pixmap(*sizeList.begin());
    m_pfrmUpdater->SetTitle(p.toImage());
    m_pfrmUpdater->SetInstallAutoStartup();
    #if defined (Q_OS_ANDROID)
        m_pfrmUpdater->showMaximized();
    #else
        m_pfrmUpdater->show();
    #endif
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

void CMainWindow::on_actionOption_O_triggered()
{
    CDlgOption dlg(this);
#if defined (Q_OS_ANDROID)
    dlg.showMaximized();
#endif
    dlg.exec();
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

void CMainWindow::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event)
    m_pShow->setText(tr("Show"));
}

bool CMainWindow::eventResizeTable(QTabWidget *pTabWidget, QResizeEvent *event)
{
    if(!pTabWidget || !event) return false;
    for(int i = 0; i < pTabWidget->count(); i++)
    {
        QScrollArea *pScrollArea
                = dynamic_cast<QScrollArea*>(pTabWidget->widget(i));
        if(!pScrollArea) continue;
        qDebug() << "eventResizeTable" << event->size();
        if(pScrollArea->metaObject()->className() != QString("QScrollArea"))
        {
            qDebug() << "objectName:" << pScrollArea->metaObject()->className();
            return false;
        }
        
        QSize s = event->size();
        pScrollArea->resize(s);
    }
    return false;
}

bool CMainWindow::eventResizeScrollArea(QScrollArea *pScrollArea, QResizeEvent *event)
{
    if(!pScrollArea || !event) return false;
    QWidget* pForm = dynamic_cast<QWidget*>(pScrollArea->widget());
    if(!pForm) return true;
    QSize s = event->size();
    QSize sMin = pForm->minimumSizeHint();
    
    QSize sNew = s;
    qDebug() << "eventResizeScrollArea" << s << sMin
             << pScrollArea->size() << pScrollArea->contentsRect();
    if(s.width() < sMin.width())
        sNew.setWidth(sMin.width());
    if(s.height() < sMin.height())
        sNew.setHeight(sMin.height());
    //pForm->setMinimumSize(pForm->minimumSizeHint());
    pForm->resize(sNew);
    //pForm->adjustSize();
    return false;
}

bool CMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Resize:
        if(&m_Table == watched)
        {
            return eventResizeTable(dynamic_cast<QTabWidget*>(watched), 
                                    dynamic_cast<QResizeEvent*>(event));
        } 
        if(watched->metaObject()->className() == QString("QScrollArea"))
        {
            return eventResizeScrollArea(dynamic_cast<QScrollArea*>(watched),
                                         dynamic_cast<QResizeEvent*>(event));
        }
        
        break;
    default:
        break;
    }
    return false;
}

void CMainWindow::on_actionStyle_triggered()
{
    CFrmStyle* p = new CFrmStyle();
    p->show();
}
