#include "StickyModel.h"

CStickyModel::CStickyModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant CStickyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int CStickyModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_Stickys.length();
}

QVariant CStickyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    QSharedPointer<CSticky> s = m_Stickys.at(index.row());
    if(!s)
        return QVariant();
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return s->GetContent();
    }
    return QVariant();
}

bool CStickyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    QSharedPointer<CSticky> s = m_Stickys.at(index.row());
    if(!s)
        return false;
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        s->SetContent(value.toString());
        break;
    }
    m_Modify = true;
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags CStickyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CStickyModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    m_Stickys.removeAt(row);
    endRemoveRows();
    return true;
}

bool CStickyModel::IsModify()
{
    return m_Modify;
}

int CStickyModel::Add(QSharedPointer<CSticky> s)
{
    if(!s)
        return -1;
    m_Stickys.push_front(s);
    insertRow(0, QModelIndex());
    emit dataChanged(index(0), index(0));
    return 0;
}

int CStickyModel::Delete(QSharedPointer<CSticky> s)
{
    if(!s)
        return -1;
    int n = m_Stickys.indexOf(s);
    if(n < 0 || n >= m_Stickys.length())
        return -2;
    m_Stickys.removeOne(s);
    emit dataChanged(index(n), index(n));
    return 0;
}

#ifndef QT_NO_DATASTREAM
QDataStream& operator<<(QDataStream &d, const CStickyModel &m)
{
    int nLength = m.m_Stickys.length();
    d << nLength;
    while (nLength) {
        d << *(m.m_Stickys.at(--nLength));
    }
    return d;
}

QDataStream& operator>>(QDataStream &d, CStickyModel &m)
{
    int nLength;
    d >> nLength;
    if(nLength <= 0)
        return d;
    while(nLength--)
    {
        QSharedPointer<CSticky> s;
        d >> *s;
        m.m_Stickys.push_front(s);
    }
    return d;
}
#endif
