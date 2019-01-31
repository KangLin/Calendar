#ifndef TASLIST_H
#define TASLIST_H

#include <QObject>
#include "Tasks.h"
#include <QList>
#include <QSharedPointer>

class CTasksList : public QObject
{
    Q_OBJECT
public:
    explicit CTasksList(QObject *parent = nullptr);
    
    int Add(QSharedPointer<CTasks> tasks);
    int Remove(QSharedPointer<CTasks> tasks);
    int RemoveAll();

public slots:
    int slotStart();
    int slotCheck();
    
private:
    QList<QSharedPointer<CTasks>> m_lstTasks;
};

#endif // TASLIST_H
