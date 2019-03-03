#ifndef FRMSTICKYLIST_H
#define FRMSTICKYLIST_H

#include <QWidget>
#include "StickyModel.h"

namespace Ui {
class CFrmStickyList;
}

class CFrmStickyList : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmStickyList(QWidget *parent = nullptr);
    ~CFrmStickyList();
    
public Q_SLOTS:
    void slotLoad();
    void slotSave();
    
    void on_actionNew_triggered();
    void on_actionRemove_triggered();
    
private:
    int Load(const QString &szFile);
    int Save(const QString &szFile);
private:
    Ui::CFrmStickyList *ui;
    
    CStickyModel m_Model;
};

#endif // FRMSTICKYLIST_H
