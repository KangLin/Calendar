#include "FrmFullScreen.h"
#include "ui_FrmFullScreen.h"
#include <QDebug>

CFrmFullScreen::CFrmFullScreen(QWidget *parent) :
    QWidget(parent,
            Qt::FramelessWindowHint
            | Qt::X11BypassWindowManagerHint  //这个标志是在x11下有用,查看帮助QWidget::showFullScreen()  
            | Qt::Tool
            | Qt::WindowStaysOnTopHint
            | Qt::CustomizeWindowHint),
    ui(new Ui::CFrmFullScreen)
{
    ui->setupUi(this);
    setStyleSheet("background-color:rgb(0,0,0);color:rgb(0,255,0);");
}

CFrmFullScreen::~CFrmFullScreen()
{
    delete ui;
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
