#include "FrmFullScreen.h"
#include "ui_FrmFullScreen.h"

CFrmFullScreen::CFrmFullScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmFullScreen)
{
    setWindowFlags(Qt::FramelessWindowHint);    // 设置窗口标志
    ui->setupUi(this);
}

CFrmFullScreen::~CFrmFullScreen()
{
    delete ui;
}

int CFrmFullScreen::Prompt(const QString szPrompt, int nValue, int nMin, int nMax, bool bInverted)
{
    ui->lbText->setText(szPrompt);
    ui->progressBar->reset();
    ui->progressBar->setInvertedAppearance(bInverted);
    ui->progressBar->setRange(nMin, nMax);
    ui->progressBar->setValue(nValue);
    return 0;
}
