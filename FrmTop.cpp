#include "FrmTop.h"
#include "ui_FrmTop.h"
#include <QGuiApplication>
#include <QScreen>

CFrmTop::CFrmTop(QWidget *parent) :
    QWidget(parent,
            Qt::FramelessWindowHint
            | Qt::X11BypassWindowManagerHint  //这个标志是在x11下有用,查看帮助QWidget::showFullScreen()
            | Qt::Tool
            | Qt::WindowStaysOnTopHint
            | Qt::CustomizeWindowHint),
    ui(new Ui::CFrmTop)
{
    ui->setupUi(this);
    m_bMoveable = false;
    QRect rect = this->geometry();
    rect.setX((QGuiApplication::primaryScreen()->availableGeometry().width()
               - ui->lbPrompt->geometry().width()) / 2);
    rect.setY((QGuiApplication::primaryScreen()->availableGeometry().height()
               - ui->lbPrompt->geometry().height()) / 2);
    rect.setWidth(ui->lbPrompt->geometry().width());
    rect.setHeight(ui->lbPrompt->geometry().height());
    setGeometry(rect);
    //setStyleSheet ("venus--TitleBar {background-color: rgb(0,0,0);color: rgb(255,255,255);}");
    setStyleSheet("background-color:rgb(0,0,0);color:rgb(0,255,0);");
    //setStyleSheet("border-radius:100px;");
}

CFrmTop::~CFrmTop()
{
    delete ui;
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
