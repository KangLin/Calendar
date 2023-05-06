// 作者：康林 <kl222@126.com>

#include "FrmTop.h"
#include "ui_FrmTop.h"
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

CFrmTop::CFrmTop(QWidget *parent) :
    QWidget(parent,
            Qt::FramelessWindowHint
            | Qt::X11BypassWindowManagerHint  //这个标志是在x11下有用,查看帮助QWidget::showFullScreen()
            | Qt::Tool
            | Qt::WindowStaysOnTopHint
            | Qt::CustomizeWindowHint),
    ui(new Ui::CFrmTop),
    m_Postion(Center)
{
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    m_pPopupMenu = nullptr;
    m_bMoveable = false;
    SetPostion(m_Postion);
    //setStyleSheet ("venus--TitleBar {background-color: rgb(0,0,0);color: rgb(255,255,255);}");
    //setStyleSheet("background-color:rgb(0,0,0);color:rgb(0,255,0);");
    //setStyleSheet("border-radius:100px;");
}

CFrmTop::~CFrmTop()
{
    delete ui;
}

void CFrmTop::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
}

void CFrmTop::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bMoveable)
    {
        m_oldTop.setX(m_oldTop.x() + (e->screenPos().x() - m_oldPos.x()));
        m_oldTop.setY(m_oldTop.y() + (e->screenPos().y() - m_oldPos.y()));
        if(m_oldTop.x() < 0)
            m_oldTop.setX(0);
        if(m_oldTop.y() < 0)
            m_oldTop.setY(0);
        if(m_oldTop.x() + frameGeometry().width()
                > QGuiApplication::primaryScreen()->geometry().width())
            m_oldTop.setX(QGuiApplication::primaryScreen()->geometry().width()
                          - frameGeometry().width());
        if(m_oldTop.y() + frameGeometry().height()
                > QGuiApplication::primaryScreen()->geometry().height())
            m_oldTop.setY(QGuiApplication::primaryScreen()->geometry().height()
                          - frameGeometry().height());
        m_oldPos = e->screenPos();
        move(m_oldTop);
    }
}

void CFrmTop::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_oldTop = this->pos();
        m_oldPos = e->screenPos();
        m_bMoveable = true;
    }
}

void CFrmTop::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        m_bMoveable = false;
}

void CFrmTop::contextMenuEvent(QContextMenuEvent *event)
{
    if(nullptr == m_pPopupMenu)
    {
        return;
    }
    m_pPopupMenu->exec(event->globalPos());
}

int CFrmTop::SetPopupMenu(QMenu* pMenu)
{
    if(nullptr == pMenu)
        return -1;
    m_pPopupMenu = pMenu;
    /*m_pPopupMenu->addAction(QIcon(":/icon/Close"),
                           tr("Close"), this, SLOT(close()));*/
    return 0;
}

void CFrmTop::SetText(const QString szText)
{
    ui->lbPrompt->setText(szText);
}

int CFrmTop::SetBackgroupImage(const QString szImage)
{
    m_bpBackgroup.load(szImage);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(m_bpBackgroup.scaled(this->geometry().size())));
    setPalette(palette);

    setStyleSheet("");

    return 0;
}

int CFrmTop::SetPostion(POSITION pos)
{
    QRect rect = this->geometry();
    rect.setWidth(ui->lbPrompt->width());
    rect.setHeight(ui->lbPrompt->height());
    setGeometry(rect);
    
    int nWidth = rect.width();
    int nHeight = rect.height();
    nWidth = qMax(nWidth, frameGeometry().width());
    nHeight = qMax(nHeight, frameGeometry().height());
    
    QRect rectScreen = QGuiApplication::primaryScreen()->availableGeometry();
    int nScreenWidth = rectScreen.width();
    int nScreenHeight = rectScreen.height();
    
    m_Postion = pos;
    QPoint leftTopPoint(0, 0);
    switch (m_Postion) {
    case LeftTop:
        leftTopPoint = QPoint(rectScreen.left(), rectScreen.top());
        break;
    case LeftCenter:
        {
            leftTopPoint = QPoint(rectScreen.left(), rectScreen.top() + (nScreenHeight - nHeight) / 2);
        }
        break;
    case LeftBottom:
        {
            leftTopPoint = QPoint(rectScreen.left(), rectScreen.top() + (nScreenHeight - nHeight));
        }
        break;
    case CenterTop:
        {
            leftTopPoint = QPoint(rectScreen.left() + (nScreenWidth - nWidth) / 2,
                                  rectScreen.top());
        }
        break;
    case Center:
        {
            leftTopPoint = QPoint(rectScreen.left() + (nScreenWidth - nWidth) / 2,
                                  rectScreen.top() + (nScreenHeight - nHeight) / 2);
        }
        break;
    case CenterBottom:
        {
            leftTopPoint = QPoint(rectScreen.left() + (nScreenWidth - nWidth) / 2,
                              rectScreen.top() + (nScreenHeight - nHeight));
        }
        break;
    case RightTop:
        {
            leftTopPoint = QPoint(rectScreen.left() + (nScreenWidth - nWidth),
                                  rectScreen.top());
        }
        break;
    case RightCenter:
        {
            leftTopPoint = QPoint(rectScreen.left() + (nScreenWidth - nWidth),
                             rectScreen.top() + (nScreenHeight - nHeight) / 2);
        }
        break;
    case RightBottom:
        {
            leftTopPoint = QPoint(rectScreen.left() + (nScreenWidth - nWidth),
                          rectScreen.top() + (nScreenHeight - nHeight));
        }
        break;
    }
    
    move(leftTopPoint);
    
    return 0;
}

void CFrmTop::showEvent(QShowEvent *event)
{
    SetPostion(m_Postion);
}
