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
    m_pCalendar->SetShowWeeks(false);
    m_pCalendar->SetShowTools(false);
    m_pCalendar->show();

    QGridLayout *pGridLayout = new QGridLayout(this);
    pGridLayout->addWidget(m_pCalendar);
    pGridLayout->addWidget(&m_listView);
}

CFrmCalendar::~CFrmCalendar()
{
    delete ui;
}
