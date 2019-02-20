#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QTimer>
#include "TasksList.h"
#include <QMenu>
#include <QSystemTrayIcon>
#include "FrmTasks.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbAdd_clicked();
    void on_pbRemove_clicked();

    void slotExit(bool checked);
    void slotSettings(bool checked);
    
    void on_pushButton_clicked();
    
protected:
    void closeEvent(QCloseEvent* e);

private:
    Ui::MainWindow *ui;

    CTasksList m_lstTasks;

    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;

    CFrmTasks m_frmTasks;
    QSharedPointer<CTasks> VisionProtectionTasks(CTasksList &taskList);
};

#endif // MAINWINDOW_H
