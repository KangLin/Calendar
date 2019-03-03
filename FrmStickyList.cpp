#include "FrmStickyList.h"
#include "ui_FrmStickyList.h"
#include <QFileDialog>
#include "FrmStickyNotes.h"

CFrmStickyList::CFrmStickyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmStickyList),
    m_Model(this)
{
    ui->setupUi(this);
    ui->listView->setModel(&m_Model);
    ui->listView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->listView->addAction(ui->actionNew);
    ui->listView->addAction(ui->actionRemove);
}

CFrmStickyList::~CFrmStickyList()
{
    if(m_Model.IsModify())
        slotSave();
    delete ui;
}

void CFrmStickyList::slotLoad()
{
    QString szFile = QFileDialog::getOpenFileName();
    if(szFile.isEmpty())
        return;
    Load(szFile);
}

int CFrmStickyList::Load(const QString &szFile)
{
    QFile f(szFile);
    if(!f.open(QIODevice::ReadOnly))
        return -1;
    QDataStream d(&f);
    d >> m_Model;
    f.close();
    return 0;
}

void CFrmStickyList::slotSave()
{
    QString szFile = QFileDialog::getSaveFileName();
    if(szFile.isEmpty())
        return;
    QFile f(szFile);
    if(!f.open(QIODevice::WriteOnly))
        return;
    QDataStream d(&f);
    d << m_Model;
    f.close();
    return;
}

void CFrmStickyList::on_actionNew_triggered()
{
    QSharedPointer<CSticky> s = m_Model.Add();
    if(!s)
        return;
    s->SetContent(tr("Take notes ......"));
    CFrmStickyNotes *pSticky = new CFrmStickyNotes(nullptr, s);
    if(!pSticky)
        return;
    bool check = connect(pSticky, SIGNAL(sigNew()),
                         this, SLOT(on_actionNew_triggered()));
    Q_ASSERT(check);    
    pSticky->show();
}

void CFrmStickyList::on_actionRemove_triggered()
{
    QModelIndex index = ui->listView->currentIndex();
    m_Model.removeRow(index.row());
}
