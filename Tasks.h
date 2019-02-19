#ifndef TASKS_H
#define TASKS_H

#pragma once

#include <QObject>
#include "Task.h"
#include <QVector>
#include <QSharedPointer>

/**
 * @brief Define a serial task
 */
class CTasks : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ GetId WRITE SetId)
    Q_PROPERTY(QString title READ GetTitle WRITE SetTitle)
    Q_PROPERTY(QString content READ GetContent WRITE SetContent)
    Q_PROPERTY(bool end READ End)
    Q_PROPERTY(int length READ Length)
    Q_PROPERTY(int currentIndex READ GetCurrentIndex)

public:
    Q_INVOKABLE explicit CTasks(QObject *parent = nullptr);
    CTasks(const CTasks &tasks);
    virtual ~CTasks();

    Q_INVOKABLE int GetId();
    Q_INVOKABLE int SetId(int id);
    Q_INVOKABLE int SetTitle(const QString &szTitle);
    Q_INVOKABLE QString GetTitle();
    Q_INVOKABLE int SetContent(const QString &szContent);
    Q_INVOKABLE QString GetContent();
    Q_INVOKABLE bool End();

    Q_INVOKABLE virtual int Add(QSharedPointer<CTask> task);
    Q_INVOKABLE virtual int Insert(QSharedPointer<CTask> task, int nIndex);
    Q_INVOKABLE virtual int Remove(QSharedPointer<CTask> task);
    Q_INVOKABLE virtual QSharedPointer<CTask> Get(int index);
    Q_INVOKABLE virtual int Length();
    Q_INVOKABLE virtual int GetCurrentIndex();
    /**
     * @brief Get current task
     * @return 
     */
    Q_INVOKABLE virtual QSharedPointer<CTask> Get();
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

private:
    int m_nCurrent;
    QVector<QSharedPointer<CTask>> m_vTask;

    int m_nId;
    QString m_szTitle;
    QString m_szContent;
};

Q_DECLARE_METATYPE(CTasks)

#endif // TASKS_H
