#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QTimer>
#include "TasksList.h"
#include <QMenu>
#include <QSystemTrayIcon>

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
    void slotTimeout();

    void slotExit(bool checked);
    void slotSettings(bool checked);
    
protected:
    void closeEvent(QCloseEvent* e);

private:
    Ui::MainWindow *ui;
    QTimer m_Timer;
    CTasksList m_lstTasks;

    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;

    QSharedPointer<CTasks> VisionProtectionTasks(CTasksList &taskList);
};

#endif // MAINWINDOW_H
