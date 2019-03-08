#ifndef FRMSTICKYLIST_H
#define FRMSTICKYLIST_H

#include <QWidget>
#include <QListView>
#include <QToolBar>
#include "StickyModel.h"
#include "FrmStickyNotes.h"

namespace Ui {
class CFrmStickyList;
}

class CFrmStickyList : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFrmStickyList(QWidget *parent = nullptr);
    virtual ~CFrmStickyList();
    
public Q_SLOTS:
    void slotLoad();
    void slotSave();
    void on_actionNew_triggered();
    void on_actionRemove_triggered();
    void slotDelete(QSharedPointer<CSticky> sticky);
    
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);
    
private:
    int Load(const QString &szFile);
    int Save(const QString &szFile);
    void ShowSticky(int nIndex);
    CFrmStickyNotes *NewFrmSticky(QSharedPointer<CSticky> s);
    
private:
    Ui::CFrmStickyList *ui;
    
    CStickyModel m_Model;
    QList<CFrmStickyNotes*> m_StickyNotes;
    QListView m_lvTasks;
    QToolBar m_ToolBar;
};

#endif // FRMSTICKYLIST_H
