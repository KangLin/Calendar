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
    Q_PROPERTY(QString name READ GetName WRITE SetName)
    Q_PROPERTY(bool end READ End)
    
public:
    explicit CTasks(QObject *parent = nullptr);
    virtual ~CTasks();

    int GetId();
    int SetId(int id);
    QString GetName();
    int SetName(QString szName);
    bool End();

    virtual int Add(QSharedPointer<CTask> task);
    virtual int Remove(QSharedPointer<CTask> task);

    virtual int Start();
    virtual int Check();

protected:
    /**
     * @brief Get current task
     * @return 
     */
    virtual QSharedPointer<CTask> Get();

signals:
private:
    int m_nCurrent;
    QVector<QSharedPointer<CTask>> m_vTask;

    int m_nId;
    QString m_szName;
};

#endif // TASKS_H
