#ifndef FRMCALENDAR_H
#define FRMCALENDAR_H

#include <QWidget>
#include <QListView>
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
    QListView m_listView;
};

#endif // FRMCALENDAR_H
