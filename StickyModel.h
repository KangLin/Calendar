#ifndef CSTRICKYMODEL_H
#define CSTRICKYMODEL_H

#include <QSharedPointer>
#include <QAbstractListModel>
#include "Sticky.h"

class CStickyModel : public QAbstractListModel
{
    Q_OBJECT
    
public:
    explicit CStickyModel(QObject *parent = nullptr);
    
    bool IsModify();
    int Add(QSharedPointer<CSticky> s);
    int Delete(QSharedPointer<CSticky> s);
    
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    
#ifndef QT_NO_DATASTREAM
    friend QDataStream& operator<<(QDataStream &d, const CStickyModel &s);
    friend QDataStream& operator>>(QDataStream &d, CStickyModel &s);
#endif

private:
    QList<QSharedPointer<CSticky> > m_Stickys;
    bool m_Modify;    
    
};

#endif // CSTRICKYMODEL_H
