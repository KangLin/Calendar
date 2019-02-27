#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QCloseEvent>
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
    void on_actionAbout_A_triggered();   
    void on_actionSink_S_triggered();
    void on_actionOption_O_triggered();
    void on_actionUpdate_U_triggered();

protected:
    virtual void closeEvent(QCloseEvent *e);
    
private:
    int LoadStyle();
    int LoadStyle(const QString &szFile);
    
private:
    Ui::CMainWindow *ui;
    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;
    QAction* m_pShow;
    QAction* m_pStartRun;
    
    CFrmTasksList *m_pFrmTasksList;

};

#endif // MAINWINDOW_H
