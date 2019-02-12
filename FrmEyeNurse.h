#ifndef FRMEYENURSE_H
#define FRMEYENURSE_H

#pragma once

#include <QWidget>
#include "TasksList.h"

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
    
private slots:
    void slotExit(bool checked);
    void slotShow(bool checked);
    void slotAbout(bool checked);
    
    void on_pbOK_clicked();
    void on_bpCancle_clicked();
    void on_sbRestInterval_editingFinished();
    void on_sbPrompTime_editingFinished();
    void on_sbPromptInterval_editingFinished();
    
protected:
    virtual void closeEvent(QCloseEvent *event);
    
private:
    Ui::CFrmEyeNurse *ui;
    
    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;
    QAction* m_pShow;
    
    CTasksList m_TaskList;
    int VisionProtectionTasks();
};

#endif // FRMEYENURSE_H
