// 作者：康林 <kl222@126.com>

#ifndef TASK_H
#define TASK_H

#pragma once

#include <QObject>
#include <QElapsedTimer>
#include <QTime>
#include <QDomElement>
#include <QIcon>

class CTask : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ GetTitle WRITE SetTitle)
    Q_PROPERTY(QString content READ GetContent WRITE SetContent)
    Q_PROPERTY(int id READ GetId WRITE SetId)
    Q_PROPERTY(int interval READ GetInterval WRITE SetInterval)
    Q_PROPERTY(int promptInterval READ GetPromptInterval WRITE SetPromptInterval)
    Q_PROPERTY(bool end READ End)
    Q_PROPERTY(QString description READ GetDescription)
    Q_PROPERTY(QIcon icon READ GetIcon WRITE SetIcon)
    Q_PROPERTY(QString startSound READ GetStartSound WRITE SetStartSound)
    Q_PROPERTY(QString runSound READ GetRunSound WRITE SetRunSound)
    
public:
    Q_INVOKABLE explicit CTask(QObject *parent = nullptr);
    /**
     * @brief CTask
     * @param nInterval: The interval between Start() and onRun(), in milliseconds
     * @param nPromptInterval: if is 0, don't prompt
     * @param parent
     */
    Q_INVOKABLE explicit CTask(int nInterval,
                   int nPromptInterval = 0,
                   QObject *parent = nullptr);
    CTask(const CTask &task);
    virtual ~CTask();
    
    Q_INVOKABLE virtual int GetId() const;
    Q_INVOKABLE virtual int SetId(int id);
    Q_INVOKABLE virtual QString GetDescription() const;
    Q_INVOKABLE virtual int SetTitle(QString szTitle);
    Q_INVOKABLE virtual QString GetTitle() const;
    Q_INVOKABLE virtual int SetContent(QString szContent);
    Q_INVOKABLE virtual QString GetContent() const;
    Q_INVOKABLE virtual int SetIcon(QIcon icon);
    Q_INVOKABLE QIcon GetIcon();
    Q_INVOKABLE virtual int GetInterval() const;
    Q_INVOKABLE virtual int SetInterval(int nInterval);
    Q_INVOKABLE virtual int GetPromptInterval() const;
    Q_INVOKABLE virtual int SetPromptInterval(int interval);
    Q_INVOKABLE virtual int SetStartSound(const QString & szSound = QString());
    Q_INVOKABLE virtual QString GetStartSound();
    Q_INVOKABLE virtual int SetRunSound(const QString & szSound = QString());
    Q_INVOKABLE virtual QString GetRunSound();
    Q_INVOKABLE virtual int SetSound(const QString &szStartSound = QString(),
                                     const QString &szRunSound = QString());
    
    Q_INVOKABLE virtual int LoadSettings(const QDomElement &e);
    Q_INVOKABLE virtual int SaveSettings(QDomElement &e);

    /**
     * @brief Start task, Initialize here. Note: first clean
     * @return 
     */
    virtual int Start();
    /**
     * @brief Check if the task can run
     * @return : 0, The task is finished. other, The task is continue.
     */
    virtual int Check();
    /**
     * @brief End
     * @return : true: The task is remove from tasks list
     *           false: The task remain in tasks list 
     */
    virtual bool End();

    int Elapsed();
protected Q_SLOTS:
    virtual void slotPrompt();
    
protected:
    virtual int onStart();
    /**
     * @brief Run the task
     * @return 
     */
    virtual int onRun();

protected:
    int Remaining();
    QString szRemaining();
    
    //QTimer m_PromptTimer;
    QTime m_PromptTime;
    int m_nPromptInterval;
    QString m_szStartSound, m_szRunSound;

private:
    int m_nId;
    QString m_szTitle;
    QString m_szContent;
    QIcon m_Icon;
    
    QElapsedTimer m_Time;
    int m_nInterval;
    
    int Init();    
};

Q_DECLARE_METATYPE(CTask)

#endif // TASK_H
