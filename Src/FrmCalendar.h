#ifndef FRMCALENDAR_H
#define FRMCALENDAR_H

#include <QWidget>
#include "tasks_export.h"

class CLunarCalendar;

namespace Ui {
class CFrmCalendar;
}

class TASKS_EXPORT CFrmCalendar : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmCalendar(QWidget *parent = nullptr);
    virtual ~CFrmCalendar();
    
private:
    Ui::CFrmCalendar *ui;
    CLunarCalendar *m_pCalendar;
};

#endif // FRMCALENDAR_H
