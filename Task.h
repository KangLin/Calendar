#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QTime>

class CTask : public QObject
{
    Q_OBJECT
public:
    explicit CTask(QObject *parent = nullptr);
    /**
     * @brief CTask
     * @param nInterval: milliseconds
     * @param parent
     */
    explicit CTask(int nInterval, QObject *parent = nullptr);
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
    
public slots:
    virtual int slotStart();

    /**
     * @brief Check if the task can run
     * @return 
     */
    virtual int slotCheck();
    
protected:
    /**
     * @brief Run the task
     * @return 
     */
    virtual int onRun();
   
private:
    int m_nId;
    QString m_szName;
    QTime m_Time;
    int m_nInterval;
};

#endif // TASK_H
