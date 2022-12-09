// 作者：康林 <kl222@126.com>

#include "DlgContainer.h"
#include "ui_DlgContainer.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>

CDlgContainer::CDlgContainer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDlgContainer)
{
    ui->setupUi(this);
}

CDlgContainer::~CDlgContainer()
{
    delete ui;
}

int CDlgContainer::SetWidget(QWidget *pWidget)
{
    if(!pWidget)
        return -1;
    
    setWindowTitle(pWidget->windowTitle());
    setWindowIcon(pWidget->windowIcon());
    ui->scrollArea->setWidget(pWidget);
    
    return 0;
}

int CDlgContainer::ShowButton(bool bShow)
{
    ui->pbOk->setVisible(bShow);
    ui->pbCancle->setVisible(bShow);
    return 0;
}

int CDlgContainer::ExtendExec()
{
#if defined (Q_OS_ANDROID)
    showMaximized();
#endif
    return exec();
}

void CDlgContainer::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    
    if(!ui->scrollArea->widget())
        return;
    
    ensurePolished();

    QMargins cm = ui->scrollArea->widget()->contentsMargins();
    int nWidth = ui->scrollArea->geometry().width();
    int nHeight = ui->scrollArea->geometry().height();
    int otherWidth = geometry().width() - nWidth + ui->scrollArea->geometry().y();
    int otherHeght = geometry().height() - nHeight + ui->scrollArea->geometry().x();
    int boardWidth = frameGeometry().width() - nWidth;
    int boardHeight = frameGeometry().height() - nHeight;
    
    QRect rectWidget = ui->scrollArea->widget()->frameGeometry();
    rectWidget.setWidth(rectWidget.width() + cm.left() + cm.right());
    rectWidget.setHeight(rectWidget.height() + cm.top() + cm.bottom());
    QRect rectDesktop = QGuiApplication::primaryScreen()->availableGeometry();
    int nDesktopWidth = rectDesktop.width();
    int nDesktopHeight = rectDesktop.height();

    qDebug() << "CDlgContainer::showEvent:" << frameGeometry() << geometry() 
             << ui->scrollArea->geometry() << rectWidget << "otherWidth:" << otherWidth
             << "oHeight:" << otherHeght << "boardWidth:" << boardWidth
             << "boardHeight:" << boardHeight;
    
    if(nWidth < rectWidget.width())
    {
        if(rectWidget.width() > rectDesktop.width() - boardWidth)
            nWidth = rectDesktop.width() - boardWidth;
        else
            nWidth = rectWidget.width();
    }
    if(nHeight < rectWidget.height())
    {
        if(rectWidget.height() > rectDesktop.height() - boardHeight)
            nHeight = rectDesktop.height() - boardHeight;
        else
            nHeight = rectWidget.height();
    }
    
    QRect rect = geometry();
    rect.setWidth(nWidth + otherWidth);
    rect.setHeight(nHeight + otherHeght);
    setGeometry(rect);
    
    QPoint point((nDesktopWidth - frameGeometry().width()) / 2,
                  (nDesktopHeight - frameGeometry().height()) / 2);
    move(point);
    qDebug() << "CDlgContainer::showEvent:" << frameGeometry();
}

void CDlgContainer::on_pbOk_clicked()
{
    this->accept();
}

void CDlgContainer::on_pbCancle_clicked()
{
    this->reject();
}
