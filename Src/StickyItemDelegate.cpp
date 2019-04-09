#include "StickyItemDelegate.h"
#include <QTextEdit>
#include <QApplication>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QPalette>

CStickyItemDelegate::CStickyItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    
}

//QWidget *CStickyItemDelegate::createEditor(QWidget *parent,
//                                          const QStyleOptionViewItem &option,
//                                          const QModelIndex &index) const
//{
//    return new QTextEdit(parent);
//}

//void CStickyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    if(!editor)
//        return;
//    QTextEdit *pEdit = static_cast<QTextEdit*>(editor);
//    pEdit->setHtml(index.model()->data(index, Qt::EditRole).toString());
//}

//void CStickyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
//    if(!editor || !model)
//        return;
//    QTextEdit* pEdit = static_cast<QTextEdit*>(editor);
//    model->setData(index, pEdit->toHtml(), Qt::EditRole);
//}

void CStickyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTextEdit e;
    e.setHtml(index.data(Qt::EditRole).toString());
    painter->save();
    painter->setBrush(option.backgroundBrush);
    painter->translate(option.rect.topLeft());
    e.resize(option.rect.size());
    e.render(painter);
    painter->restore();
}

//QSize CStickyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QTextEdit e;
//    e.setHtml(index.data(Qt::EditRole).toString());
//    return e.size();
//}
