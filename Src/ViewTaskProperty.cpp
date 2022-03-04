// 作者：康林 <kl222@126.com>

#include "ViewTaskProperty.h"
#include <QDebug>
#include <QMetaProperty>

CViewTaskProperty::CViewTaskProperty(QSharedPointer<CTask> task, QWidget *parent) : QTableView (parent)
{
    bool check = connect(&m_Model, SIGNAL(itemChanged(QStandardItem*)),
                         this, SLOT(slotItemChange(QStandardItem*)));
    Q_ASSERT(check);
    setModel(&m_Model);
    
    m_Model.setColumnCount(2);
    m_Model.setHeaderData(0, Qt::Horizontal, tr("Property"));
    m_Model.setHeaderData(1, Qt::Horizontal, tr("Value"));
    
    m_Task = task;
    SetProperty(m_Task);   
}

int CViewTaskProperty::SetProperty(QSharedPointer<CTask> task)
{
    int nRet = 0;
    
    if(!task)
    {
        qWarning() << "CFrmTaskPropery::InitProperty: task is null";
        return -1;
    }
    m_Task = task;
    const QMetaObject* pObj = task->metaObject();
    int nCount = pObj->propertyCount();
    for(int i = 0; i < nCount; i++)
    {
        QMetaProperty p = pObj->property(i);
        QStandardItem *pName = new QStandardItem(p.name());
        pName->setEditable(false);
        QStandardItem *pValue = new QStandardItem(p.read(task.data()).toString());
        if(p.isWritable())
            pValue->setEnabled(true);
        else 
            pValue->setEditable(false);
        
        QList<QStandardItem*> lstItems;
        lstItems.push_back(pName);
        lstItems.push_back(pValue);
        m_Model.appendRow(lstItems);
    }
    return nRet;
}

void CViewTaskProperty::slotItemChange(QStandardItem *item)
{
    QModelIndex index = item->index();
    QModelIndex i = item->model()->index(index.row(), 0);
    QVariant name = item->model()->data(i, Qt::DisplayRole);
    QVariant value = item->data(Qt::DisplayRole);
    if(m_Task)
    {
        //qDebug() << "name:" << name << "value:" << value;
        m_Task->setProperty(name.toString().toStdString().c_str(), value);
    }
}
