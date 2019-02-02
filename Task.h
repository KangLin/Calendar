#ifndef TASK_H
#define TASK_H

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
    virtual int SetInterval(int nInterval);
    virtual int GetInterval();
    virtual bool End();
    virtual int LoadSettings();
    virtual int SaveSettings();
    
    virtual int Start();

    /**
     * @brief Check if the task can run
     * @return 
     */
    virtual int Check();
    
protected slots:
    virtual void slotPrompt();
    
protected:
    /**
     * @brief Run the task
     * @return 
     */
    virtual int onRun();
    virtual int onStart();

protected:
    int Elapsed();
    int Remaining();
    
private:
    int m_nId;
    QString m_szName;
    QTime m_Time;
    int m_nInterval;
    QTimer m_PromptTimer;
    int m_nPromptInterval;
    
    int Init();    
};

#endif // TASK_H
