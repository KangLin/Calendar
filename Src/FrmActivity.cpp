#include "FrmActivity.h"
#include "ui_FrmActivity.h"
#include <QScrollArea>

CFrmActivity::CFrmActivity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmActivity)
{
    ui->setupUi(this);
}

CFrmActivity::~CFrmActivity()
{
    delete ui;
}

void CFrmActivity::showEvent(QShowEvent *event)
{
}
