// 作者：康林 <kl222@126.com>

#ifndef FRMCALENDAR_H
#define FRMCALENDAR_H

#include <QWidget>
#include <QListView>
#include <QToolBar>
#include <QMenu>
#include <QStandardItemModel>
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
    void slotRefresh();
    void slotViewWeek(bool checked);
    void slotCalendarHead(bool checked);
    void slotViewDoubleClicked(const QModelIndex &index);
    void slotViewCustomContextMenuRequested(const QPoint &pos);
    
private:
    int Load(const QString& szFile);
    int Update();
    
private:
    CLunarCalendar *m_pCalendar;
    QListView m_listView;
    QStandardItemModel* m_pModel;
    QToolBar m_ToolBar;
    bool m_bModify;
    CTasksList m_TasksList;
    QMenu m_ListViewMenu;
};

#endif // FRMCALENDAR_H
