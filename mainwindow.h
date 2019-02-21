#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>

#include "TasksList.h"
#include "FrmTasksList.h"

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();
    
private Q_SLOTS:
    void slotExit(bool checked);
    void slotShow(bool checked);
    void slotAbout(bool checked);
    void slotStartRun(bool checked);
    
    void slotActivated(QSystemTrayIcon::ActivationReason reason);
    void on_actionExit_E_triggered();

    
private:
    int Load(QString szFile = QString());
    
private:
    Ui::CMainWindow *ui;
    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;
    QAction* m_pShow;
    QAction* m_pStartRun;
    
    CTasksList m_TasksList;
    CFrmTasksList *m_pFrmTasksList;
};

#endif // MAINWINDOW_H
