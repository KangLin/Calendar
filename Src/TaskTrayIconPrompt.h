#ifndef TASKTRAYICONPROMPT_H
#define TASKTRAYICONPROMPT_H

#pragma once

#include "Task.h"

#include <QTimer>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTime>

class CTaskTrayIconPrompt : public CTask
{
    Q_OBJECT
public:
    CTaskTrayIconPrompt(QObject *parent = nullptr);
    CTaskTrayIconPrompt(const QString szMessage,
                const QString szTitle = tr("Prompt"),
                int nInterval = 5 * 60 * 1000,
                int nPromptInterval = 60 * 1000,
                const QIcon icon = QIcon(":/icon/App"),
                QObject *parent = nullptr);

protected:
    virtual int onRun();
    virtual int onStart();

protected Q_SLOTS:
    virtual void slotPrompt();
    void slotTrayIconActive(QSystemTrayIcon::ActivationReason reason);

private:
    QMenu m_TrayIconMenu;
    QSystemTrayIcon m_TrayIcon;
    QString m_szTitle;
    QString m_szMessage;
    QIcon m_Icon;
    
    int Init();
};

#endif // TASKTRAYICONPROMPT_H
