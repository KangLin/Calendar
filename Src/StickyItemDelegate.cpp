// 作者：康林 <kl222@126.com>

#include "StickyItemDelegate.h"
#include <QTextEdit>
#include <QApplication>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QPalette>
#include <QDebug>

CStickyItemDelegate::CStickyItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{    
}

QWidget *CStickyItemDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{
    if(index.isValid()) {
        QTextEdit *textedit = new QTextEdit(parent);
        textedit->setReadOnly(true);
        return textedit;
    } else {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }
}

void CStickyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.isValid() && editor) {
        QTextEdit *pEdit = static_cast<QTextEdit*>(editor);
        pEdit->setHtml(index.model()->data(index, Qt::EditRole).toString());
    } else {
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void CStickyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.isValid() && editor && model) {
        QTextEdit* pEdit = static_cast<QTextEdit*>(editor);
        model->setData(index, pEdit->toHtml(), Qt::EditRole);
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void CStickyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    
    QTextEdit e;
    //e.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    e.setHtml(index.data(Qt::EditRole).toString());
    //QVariant background = index.model()->data(index, Qt::BackgroundRole);
    //QVariant front = index.model()->data(index, Qt::ForegroundRole);
    painter->setBrush(option.backgroundBrush);
    painter->translate(option.rect.topLeft());
    e.resize(option.rect.size());
    e.render(painter);
    
    painter->restore();
}

QSize CStickyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTextEdit e;
    e.setHtml(index.data(Qt::EditRole).toString());
    QMargins cm = e.contentsMargins();
    int marginW = e.style()->pixelMetric(
                                QStyle::PM_FocusFrameHMargin) << 1;
    int marginH = e.style()->pixelMetric(
                                QStyle::PM_FocusFrameVMargin) << 1;
    QSize s = option.rect.size();
    s.setHeight(option.fontMetrics.boundingRect(e.toPlainText()).height()
                + cm.top() + cm.bottom() + marginH);
    return s;
}

//void CStickyItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    if(index.isValid() && editor) {

//    } else {
//        QStyledItemDelegate::updateEditorGeometry(editor, option, index);
//    }
//}
