#ifndef FRMTOP_H
#define FRMTOP_H

#pragma once

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class CFrmTop;
}

class CFrmTop : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmTop(QWidget *parent = nullptr);
    ~CFrmTop();
    
    void SetText(const QString szText);
    int SetBackgroupImage(const QString szImage);
    
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);

private:
    Ui::CFrmTop *ui;
    
    bool m_bMoveable;
    QPointF m_oldPos;
    QPoint m_oldTop;
    QRect m_rtDesktop;
    
    QImage m_bpBackgroup;
};

#endif // FRMTOP_H
