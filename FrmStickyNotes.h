#ifndef FRMSTICKYNOTES_H
#define FRMSTICKYNOTES_H

#include <QWidget>
#include <iostream>
#include <QToolBar>

namespace Ui {
class CFrmStickyNotes;
}

class CFrmStickyNotes : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmStickyNotes(QWidget *parent = nullptr);
    ~CFrmStickyNotes();
    
    int Load(std::istream in);
    int Save(std::ostream out);
    
private Q_SLOTS:
    void slotBold();
    void slotItalic();
    void slotUnderline();
    void slotStrikethrough();
    void slotDelet();
    
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    
private:
    Ui::CFrmStickyNotes *ui;
    
    QToolBar m_ToolBar;
};

#endif // FRMSTICKYNOTES_H
