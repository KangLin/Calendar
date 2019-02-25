#include "FrmFullScreen.h"
#include "ui_FrmFullScreen.h"
#include <QDebug>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

CFrmFullScreen::CFrmFullScreen(QWidget *parent) :
    QWidget(parent,
            Qt::FramelessWindowHint
            | Qt::X11BypassWindowManagerHint  //这个标志是在x11下有用,查看帮助QWidget::showFullScreen()  
            | Qt::Tool
            | Qt::WindowStaysOnTopHint
            | Qt::CustomizeWindowHint),
    ui(new Ui::CFrmFullScreen)
{
    this->setFixedSize(qApp->desktop()->size());
    resize(qApp->desktop()->size());
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    //setStyleSheet("background-color:rgb(0,0,0);color:rgb(0,255,0);");
    bool check = connect(&m_Timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    Q_ASSERT(check);
    m_Timer.start(1000);
    this->setCursor(Qt::BlankCursor);
}

CFrmFullScreen::~CFrmFullScreen()
{
    qDebug() << "CFrmFullScreen::~CFrmFullScreen()";
    m_Timer.stop();
    delete ui;
}

void CFrmFullScreen::slotTimeout()
{
    ui->timeEdit->setTime(QTime::currentTime());
}

void CFrmFullScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    /*QPainter painter(this);
    if(!m_bpBackgroup.isNull())
        painter.drawImage(this->geometry(), m_bpBackgroup);*/
}

int CFrmFullScreen::Prompt(const QString szPrompt, int nValue, int nMin, int nMax, bool bInverted)
{
    ui->lbText->setText(szPrompt);
    ui->progressBar->reset();
    //ui->progressBar->setInvertedAppearance(bInverted);
    ui->progressBar->setRange(nMin, nMax);
    if(bInverted)
    {
        int n = nMax - nValue;
        qDebug() << "Max:" << nMax << "value:" << nValue << "n:" << n;
        ui->progressBar->setValue(n);
    }
    else
        ui->progressBar->setValue(nValue);
    return 0;
}

int CFrmFullScreen::SetBackgroupImage(const QString szImage)
{
    m_bpBackgroup.load(szImage);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(m_bpBackgroup.scaled(this->geometry().size())));
    setPalette(palette);
    
    setStyleSheet("");
    
    return 0;
}
