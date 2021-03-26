#ifndef CTHREADTASKS_H
#define CTHREADTASKS_H

#include <QThread>

class CTasksList;

class CThreadTasks : public QThread
{
    Q_OBJECT
    
public:
    explicit CThreadTasks(CTasksList *parent = nullptr);
    virtual ~CThreadTasks();
    
    int Quit();

protected:
    virtual void run() override;

private:
    bool m_bExit;
    CTasksList* m_pTaskList;
    
};

#endif // CTHREADTASKS_H
