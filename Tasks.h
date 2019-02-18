#ifndef TASKS_H
#define TASKS_H

#pragma once

#include <QObject>
#include "Task.h"
#include <QVector>
#include <QSharedPointer>

class CTasks : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ GetId WRITE SetId)
    Q_PROPERTY(bool end READ End)
    
public:
    Q_INVOKABLE explicit CTasks(QObject *parent = nullptr);
    CTasks(const CTasks &tasks);
    virtual ~CTasks();

    Q_INVOKABLE int GetId();
    Q_INVOKABLE int SetId(int id);
    Q_INVOKABLE bool End();

    Q_INVOKABLE virtual int Add(QSharedPointer<CTask> task);
    Q_INVOKABLE virtual int Remove(QSharedPointer<CTask> task);

    /**
     * @brief Start: Initialize here
     * @return 
     */
    Q_INVOKABLE virtual int Start();
    /**
     * @brief Check the current task is run
     * @return 
     */
    Q_INVOKABLE virtual int Check();
    
    virtual int LoadSettings(const QDomElement &e);
    virtual int SaveSettings(QDomElement &e);    

protected:
    /**
     * @brief Get current task
     * @return 
     */
    virtual QSharedPointer<CTask> Get();

private:
    int m_nCurrent;
    QVector<QSharedPointer<CTask>> m_vTask;

    int m_nId;
};

Q_DECLARE_METATYPE(CTasks)

#endif // TASKS_H
