#ifndef FRMSTICKYNOTES_H
#define FRMSTICKYNOTES_H

#include <QWidget>
#include <iostream>
#include <QToolBar>
#include <QTextEdit>
#include <QComboBox>
#include "Sticky.h"

namespace Ui {
class CFrmStickyNotes;
}

class CFrmStickyNotes : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmStickyNotes(QWidget *parent = nullptr,
                     QSharedPointer<CSticky> sticky =QSharedPointer<CSticky>());
    virtual ~CFrmStickyNotes() override;
    
    int SetSticky(QSharedPointer<CSticky> sticky);
    
Q_SIGNALS:
    void sigNew();
    
private Q_SLOTS:
    void slotBold();
    void slotItalic();
    void slotUnderline();
    void slotStrikethrough();
    void slotDelet();
    void slotDelet(QSharedPointer<CSticky>);
    void slotNew();
    void slotPolicy(int policy);
    void slotTextChanged();
    void slotUpdate();
    
protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
    
private:
    Ui::CFrmStickyNotes *ui;
    
    QComboBox *m_pComboBox;
    QToolBar m_ToolBarTop;
    QToolBar m_ToolBarButton;
    QTextEdit m_TextEdit;
    
    bool m_bMoveable;
    QPointF m_oldPos;
    QPoint m_oldTop;
    QRect m_rtDesktop;
    
    QSharedPointer<CSticky> m_Sticky;
};

#endif // FRMSTICKYNOTES_H
