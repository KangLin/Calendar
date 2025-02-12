// 作者：康林 <kl222@126.com>

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
    Q_PROPERTY(bool enable READ GetEnable WRITE SetEnable)
    Q_PROPERTY(QString title READ GetTitle WRITE SetTitle)
    Q_PROPERTY(QString content READ GetContent WRITE SetContent)
    Q_PROPERTY(bool end READ End)
    Q_PROPERTY(int length READ Length)
    Q_PROPERTY(int currentIndex READ GetCurrentIndex)
    Q_PROPERTY(QIcon icon READ GetIcon WRITE SetIcon)
    
public:
    Q_INVOKABLE explicit CTasks(QObject *parent = nullptr);
    CTasks(const CTasks &tasks);
    virtual ~CTasks();

    Q_INVOKABLE int GetId();
    Q_INVOKABLE int SetId(int id);
    Q_INVOKABLE virtual bool GetEnable() const;
    Q_INVOKABLE virtual int SetEnable(bool bEnable);
    Q_INVOKABLE int SetTitle(const QString &szTitle);
    Q_INVOKABLE QString GetTitle();
    Q_INVOKABLE int SetContent(const QString &szContent);
    Q_INVOKABLE QString GetContent();
    Q_INVOKABLE int SetIcon(QIcon icon);
    Q_INVOKABLE QIcon GetIcon();
    Q_INVOKABLE bool End();

    Q_INVOKABLE virtual int Add(QSharedPointer<CTask> task);
    Q_INVOKABLE virtual int Insert(QSharedPointer<CTask> task, int nIndex);
    /*Q_INVOKABLE virtual int InsertAfter(QSharedPointer<CTask> newTask,
                          QSharedPointer<CTask> task = QSharedPointer<CTask>());//*/
    Q_INVOKABLE virtual int Remove(QSharedPointer<CTask> task);
    
    Q_INVOKABLE virtual QSharedPointer<CTask> Get(int nIdTask);
    /**
     * @brief Get current task
     * @return 
     */
    Q_INVOKABLE virtual QSharedPointer<CTask> GetCurrent();
    virtual QSharedPointer<CTask> GetIndex(int nIndex);
    Q_INVOKABLE virtual int GetCurrentIndex();
    Q_INVOKABLE virtual int Length();
    
    typedef QVector<QSharedPointer<CTask> >::iterator POSITION;
    POSITION GetFirst();
    QSharedPointer<CTask> GetNext(POSITION &pos);
    
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
    int m_CurrentPostion;
    QVector<QSharedPointer<CTask> > m_Task;
    int m_nIdTask;
    int m_nId;
    bool m_bEnable;
    QString m_szTitle;
    QString m_szContent;
    QIcon m_Icon;
};

Q_DECLARE_METATYPE(CTasks)

#endif // TASKS_H
