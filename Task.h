#ifndef TASK_H
#define TASK_H

#pragma once

#include <QObject>
#include <QTime>
#include <QTimer>

class CTask : public QObject
{
    Q_OBJECT
public:
    explicit CTask(QObject *parent = nullptr);
    /**
     * @brief CTask
     * @param nInterval: The interval between Start() and onRun(), in milliseconds
     * @param nPromptInterval: if is 0, don't prompt
     * @param parent
     */
    explicit CTask(int nInterval,
                   int nPromptInterval = 0,
                   QObject *parent = nullptr);
    virtual ~CTask();
    
    virtual int GetId();
    virtual int SetId(int id);
    virtual QString GetName();
    virtual int SetName(QString szName);
    virtual int SetTitle(QString szTitle);
    virtual QString GetTitle();
    virtual int SetContent(QString szContent);
    virtual QString GetContent();
    virtual int GetInterval();
    virtual int SetInterval(int nInterval);

    virtual int LoadSettings();
    virtual int SaveSettings();

    virtual int Start();

    /**
     * @brief Check if the task can run
     * @return 
     */
    virtual int Check();
    virtual bool End();

protected slots:
    virtual void slotPrompt();
    
protected:
    virtual int onStart();
    /**
     * @brief Run the task
     * @return 
     */
    virtual int onRun();

protected:
    int Elapsed();
    int Remaining();
    QString szRemaining();
    
private:
    int m_nId;
    QString m_szName;
    QString m_szTitle;
    QString m_szContent;
    QTime m_Time;
    int m_nInterval;
    QTimer m_PromptTimer;
    int m_nPromptInterval;
    
    int Init();    
};

#endif // TASK_H
