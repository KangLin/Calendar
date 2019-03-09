#include "StickyItemDelegate.h"
#include <QTextEdit>
#include <QApplication>
#include <QPainter>
#include <QStyleOptionViewItem>

CStickyItemDelegate::CStickyItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    
}

QWidget *CStickyItemDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    return new QTextEdit(parent);
}

void CStickyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(!editor)
        return;
    QTextEdit *pEdit = static_cast<QTextEdit*>(editor);
    pEdit->setHtml(index.model()->data(index, Qt::EditRole).toString());
}

void CStickyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(!editor || !model)
        return;
    QTextEdit* pEdit = static_cast<QTextEdit*>(editor);
    model->setData(index, pEdit->toHtml(), Qt::EditRole);
}
