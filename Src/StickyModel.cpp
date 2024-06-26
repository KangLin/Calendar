// 作者：康林 <kl222@126.com>

#include "StickyModel.h"

CStickyModel::CStickyModel(QObject *parent)
    : QAbstractListModel(parent)
{
    SetModify(false);
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
    int r = index.row();
    if(r < 0 || r >= m_Stickys.length())
        return QVariant();
    QSharedPointer<CSticky> s = m_Stickys.at(index.row());
    if(!s)
        return QVariant();
    switch (role) {
    case Qt::DisplayRole:
        return s->GetText();
    case Qt::EditRole:
        return s->GetContent();
    }
    return QVariant();
}

bool CStickyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    int r = index.row();
    if(r < 0 || r >= m_Stickys.length())
        return false;
    QSharedPointer<CSticky> s = m_Stickys.at(index.row());
    if(!s)
        return false;
    switch (role) {
    case Qt::DisplayRole:
        s->SetText(value.toString());
        break;
    case Qt::EditRole:
        s->SetContent(value.toString());
        break;
    }
    SetModify(true);
    emit s->sigUpdate();
    //emit dataChanged(index, index);
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
    if(row < 0)
        return false;
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    SetModify(true);
    QSharedPointer<CSticky> s = m_Stickys.at(row);
    m_Stickys.removeOne(s);
    emit s->sigRemove(s);
    endRemoveRows();
    return true;
}

int CStickyModel::Clean()
{
    m_Stickys.clear();
    internalUpdate();
    return 0;
}

void CStickyModel::internalUpdate()
{
    emit dataChanged(index(0), index(m_Stickys.length() -1));
}

bool CStickyModel::IsModify()
{
    return m_bModify;
}

int CStickyModel::SetModify(bool bModify)
{
    m_bModify = bModify;
    return 0;
}

QSharedPointer<CSticky> CStickyModel::Add()
{
    QSharedPointer<CSticky> s(new CSticky());    
    if(!s)
        return QSharedPointer<CSticky>();
    m_Stickys.push_back(s);
    int row = m_Stickys.length() - 1;
    if(row < 0) row = 0;
    insertRow(row, QModelIndex());
    SetModify(true);
    emit dataChanged(index(0), index(row));
    bool check = connect(s.data(), SIGNAL(sigRemove(QSharedPointer<CSticky>)),
                    this, SLOT(slotDelete(QSharedPointer<CSticky>)));
    Q_ASSERT(check);
    check = connect(s.data(), SIGNAL(sigUpdate()),
                    this, SLOT(slotModify()));
    Q_ASSERT(check);
    return s;
}

QSharedPointer<CSticky> CStickyModel::Get(int index)
{
    if(index < 0 || index >= m_Stickys.length())
        return QSharedPointer<CSticky>();
    return m_Stickys.at(index);
}
        
void CStickyModel::slotDelete(QSharedPointer<CSticky> s)
{
    if(!s)
        return;
    int n = m_Stickys.indexOf(s);
    if(n < 0 || n >= m_Stickys.length())
        return;
    SetModify(true);
    m_Stickys.removeOne(s);
    emit dataChanged(index(n), index(n));
    return;
}

void CStickyModel::slotModify()
{
    SetModify(true);

    emit dataChanged(index(0),
                     index(m_Stickys.length() - 1));
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
        QSharedPointer<CSticky> s(new CSticky());
        d >> *s;
        m.m_Stickys.push_front(s);
        bool check = QObject::connect(s.data(), SIGNAL(sigRemove(QSharedPointer<CSticky>)),
                        &m, SLOT(slotDelete(QSharedPointer<CSticky>)));
        Q_ASSERT(check);
        check = QObject::connect(s.data(), SIGNAL(sigUpdate()),
                        &m, SLOT(slotModify()));
        Q_ASSERT(check);
    }
    return d;
}
#endif
