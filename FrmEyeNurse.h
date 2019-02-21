#ifndef FRMEYENURSE_H
#define FRMEYENURSE_H

#pragma once

#include <QWidget>
#include "TasksList.h"
#include "FrmTasks.h"
#include <QMenu>
#include <QSystemTrayIcon>

namespace Ui {
class CFrmEyeNurse;
}

class CFrmEyeNurse : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmEyeNurse(QWidget *parent = nullptr);
    ~CFrmEyeNurse();
    
private Q_SLOTS:
    void slotExit(bool checked);
    void slotShow(bool checked);
    void slotAbout(bool checked);
    void slotStartRun(bool checked);
    
    void slotActivated(QSystemTrayIcon::ActivationReason reason);
    void slotChange();
    
protected:
    virtual void closeEvent(QCloseEvent *event);
    
private:
    Ui::CFrmEyeNurse *ui;
    
    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;
    QAction* m_pShow;
    QAction* m_pStartRun;
    
    CTasksList m_TasksList;
    int VisionProtectionTasks();
    
    CFrmTasks m_frmTasks;
};

#endif // FRMEYENURSE_H
