#include "FrmCalendar.h"
#include "ui_FrmCalendar.h"
#include "LunarCalendar.h"
#include <QGridLayout>

CFrmCalendar::CFrmCalendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmCalendar)
{
    ui->setupUi(this);
    m_pCalendar = new CLunarCalendar(this);
    m_pCalendar->show();

    QGridLayout *pGridLayout = new QGridLayout(this);
    pGridLayout->addWidget(m_pCalendar);
}

CFrmCalendar::~CFrmCalendar()
{
    delete ui;
}
