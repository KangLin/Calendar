#include "FrmCalendar.h"
#include "ui_FrmCalendar.h"
#include "LunarCalendar.h"
#include <QGridLayout>
#include <QDate>

class CTasksHandler : public CLunarCalendar::CGetTaskHandler
{
public:
    CTasksHandler(CFrmCalendar* pFrmCalendar);
    virtual ~CTasksHandler();
    
    virtual int onHandle(QDate date);
private:
    CFrmCalendar* m_pFrmCalendar;
};

CTasksHandler::CTasksHandler(CFrmCalendar* pFrmCalendar)
    : CLunarCalendar::CGetTaskHandler()
{
    m_pFrmCalendar = pFrmCalendar;
}

CTasksHandler::~CTasksHandler()
{
}

int CTasksHandler::onHandle(QDate date)
{
    return m_pFrmCalendar->onHandle(date);
}

CFrmCalendar::CFrmCalendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmCalendar)
{
    ui->setupUi(this);
    CLunarCalendar::InitResource();
    m_pCalendar = new CLunarCalendar(this);
    m_pCalendar->SetTaskHandle(QSharedPointer<CTasksHandler>(
                                   new CTasksHandler(this)));
    m_pCalendar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_pCalendar->SetViewType(CLunarCalendar::ViewTypeWeek);
    m_pCalendar->ShowWeeks(false);
    //m_pCalendar->ShowHead(false);
    m_pCalendar->ShowTime(false);
    //m_pCalendar->SetCalendarType(CLunarCalendar::CalendarTypeSolar);
    m_pCalendar->show();
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

int CFrmCalendar::onHandle(QDate date)
{
    int nRet = 0;
    
    return nRet;
}
