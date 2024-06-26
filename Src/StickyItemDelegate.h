// 作者：康林 <kl222@126.com>

#ifndef STIKYITEMDELEGATE_H
#define STIKYITEMDELEGATE_H

#include <QStyledItemDelegate>

class CStickyItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CStickyItemDelegate(QObject *parent = nullptr);

    virtual QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // STIKYITEMDELEGATE_H
