#ifndef FRMCALENDAR_H
#define FRMCALENDAR_H

#include <QWidget>
#include <QListView>
#include <QToolBar>
#include "tasks_export.h"
#include "TasksList.h"

class CLunarCalendar;

class TASKS_EXPORT CFrmCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit CFrmCalendar(QWidget *parent = nullptr);
    virtual ~CFrmCalendar();

    virtual int onHandle(QDate date);

private Q_SLOTS:
    void slotSelectionChanged();
    void slotLoad();
    void slotSaveAs();
    void slotAdd();
    void slotDelete();
    void slotModify();
    void slotViewWeek(bool checked);
    void slotCalendarHead(bool checked);

private:
    int Load(const QString& szFile);
    
private:
    CLunarCalendar *m_pCalendar;
    QListView m_listView;
    QToolBar m_ToolBar;
    
    CTasksList m_TasksList;
};

#endif // FRMCALENDAR_H
