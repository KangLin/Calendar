// 作者：康林 <kl222@126.com>

#ifndef TASLIST_H
#define TASLIST_H

#pragma once

#include <QObject>
#include "Tasks.h"
#include <QMap>
#include <QSharedPointer>
#include <QTimer>
#include <ThreadTasks.h>

/**
 * @brief Define parallel tasks
 */
class CTasksList : public QObject
{
    Q_OBJECT
    
public:
    explicit CTasksList(QObject *parent = nullptr);
    virtual ~CTasksList();
    
    int Add(QSharedPointer<CTasks> tasks);
    int Remove(QSharedPointer<CTasks> tasks);
    int RemoveAll();

    typedef QMap<int, QSharedPointer<CTasks> >::iterator POSITION;
    POSITION GetFirst();
    QSharedPointer<CTasks> GetNext(POSITION &pos);
    QSharedPointer<CTasks> Get(int nId);
    
    /*
     * @brief Start: Initialize here
     * @param nInterval: Check interval.
     *                   If is 0, disable check in the class. check by user
     * @param bForce: force restart
     * @return 
     */
    int Start(int nInterval = 1000, bool bForce = false);
    int Check();

    virtual int LoadSettings(const QDomElement &e);
    virtual int LoadSettings(const QString &szFile = QString());
    virtual int SaveSettings(QDomElement &e);
    virtual int SaveSettings(const QString &szFile = QString());
    
private Q_SLOTS:
    void slotTimeout();

private:
    
private:
    QMap<int, QSharedPointer<CTasks> > m_Tasks;
    QTimer m_Timer;
    int m_nTimerInterval;
    int m_nIdCount;
    CThreadTasks m_Thread;
    bool m_bThread;
};

#endif // TASLIST_H
