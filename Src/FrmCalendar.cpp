#include "FrmCalendar.h"
#include "ui_FrmCalendar.h"
#include "LunarCalendar.h"
#include <QGridLayout>
#include <QDate>

CFrmCalendar::CFrmCalendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmCalendar)
{
    ui->setupUi(this);
    CLunarCalendar::InitTranslator();
    m_pCalendar = new CLunarCalendar(this);
    m_pCalendar->SetShowWeeks(false);
    //m_pCalendar->SetShowTools(false);
    m_pCalendar->show();
    m_pCalendar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    bool check = connect(m_pCalendar, SIGNAL(sigSelectionChanged()),
                         this, SLOT(slotSelectionChanged()));
    Q_ASSERT(check);
    
    m_listView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    QGridLayout *pGridLayout = new QGridLayout(this);
    pGridLayout->addWidget(m_pCalendar);
    pGridLayout->addWidget(&m_listView);
}

CFrmCalendar::~CFrmCalendar()
{
    delete ui;
}

void CFrmCalendar::slotSelectionChanged()
{
    if(!m_pCalendar)
        return;
    QDate date = m_pCalendar->SelectedDate();
    //TODO: update list view
}
