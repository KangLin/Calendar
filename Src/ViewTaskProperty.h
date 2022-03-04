// 作者：康林 <kl222@126.com>

#ifndef VIEWTASKPROPERTY_H
#define VIEWTASKPROPERTY_H

#include <QTableView>
#include <QObject>
#include <QStandardItemModel>
#include <QStandardItem>
#include "Task.h"

class CViewTaskProperty : public QTableView
{
    Q_OBJECT
public:
    CViewTaskProperty(QSharedPointer<CTask> task = QSharedPointer<CTask>(),
                      QWidget *parent = nullptr);
    
    int SetProperty(QSharedPointer<CTask> task);
    
private Q_SLOTS:
    void slotItemChange(QStandardItem* item);
    
private:
    QStandardItemModel m_Model;
    QSharedPointer<CTask> m_Task;
    
    
};

#endif // VIEWTASKPROPERTY_H
