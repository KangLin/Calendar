#ifndef STIKYITEMDELEGATE_H
#define STIKYITEMDELEGATE_H

#include <QStyledItemDelegate>

class CStickyItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CStickyItemDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;   
};

#endif // STIKYITEMDELEGATE_H
