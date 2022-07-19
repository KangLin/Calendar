// 作者：康林 <kl222@126.com>

#include "FrmStickyList.h"
#include "ui_FrmStickyList.h"
#include "RabbitCommonDir.h"
#include "StickyItemDelegate.h"
#include <QFileDialog>
#include <QSettings>
#include <QDebug>

CFrmStickyList::CFrmStickyList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmStickyList),
    m_Model(this),
    m_lvTasks(this),
    m_ToolBar(this)
{
    ui->setupUi(this);
    this->layout()->addWidget(&m_ToolBar);
    this->layout()->addWidget(&m_lvTasks);
    QAction * pAction = m_ToolBar.addAction(QIcon::fromTheme("document-open"), tr("Open sticky"), this, SLOT(slotLoad()));
    pAction->setToolTip(tr("Open sticky"));
    pAction->setStatusTip(tr("Open sticky"));
    pAction = m_ToolBar.addAction(QIcon::fromTheme("document-save"), tr("Save sticky"), this, SLOT(slotSave()));
    pAction->setToolTip(tr("Save sticky"));
    pAction->setStatusTip(tr("Save sticky"));
    m_ToolBar.addSeparator();
    m_ToolBar.addAction(ui->actionNew);
    m_ToolBar.addAction(ui->actionRemove);
    m_lvTasks.setModel(&m_Model);
    m_lvTasks.setContextMenuPolicy(Qt::ActionsContextMenu);
    m_lvTasks.addAction(ui->actionNew);
    m_lvTasks.addAction(ui->actionRemove);
    //m_lvTasks.setSpacing(2);
    m_lvTasks.setItemDelegate(new CStickyItemDelegate(&m_lvTasks));
    bool check = connect(&m_lvTasks, SIGNAL(clicked(const QModelIndex)),
                     this, SLOT(on_listView_doubleClicked(const QModelIndex)));
    Q_ASSERT(check);
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    QString szFile = set.value("Sticky/File",
                               RabbitCommon::CDir::Instance()->GetDirUserData()
                               + QDir::separator() + "Sticky").toString();
    Load(szFile);
    QSharedPointer<CSticky> s;
    int i = 0;
    while(s = m_Model.Get(i++))
    {
        CFrmStickyNotes* sn = NewFrmSticky(s);
        sn->SetSticky(s);
        if(!s->GetWindowHide())
        {
#if defined (Q_OS_ANDROID)
            sn->showMaximized();
#else
            sn->show();
#endif
        }
    }
}

CFrmStickyList::~CFrmStickyList()
{
    if(m_Model.IsModify())
    {    
        QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                      QSettings::IniFormat);
        QString szFile = set.value("Sticky/File",
                                   RabbitCommon::CDir::Instance()->GetDirUserData()
                                   + QDir::separator() + "Sticky").toString();
        Save(szFile);
    }
    CleanStickyNotes();
    delete ui;
}

int CFrmStickyList::CleanStickyNotes()
{
    foreach(CFrmStickyNotes* p, m_StickyNotes)
    {
        p->close();
        p->deleteLater();
    }
    m_StickyNotes.clear();
    return 0;
}

void CFrmStickyList::slotLoad()
{
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    QString szFile = set.value("Sticky/File",
                               RabbitCommon::CDir::Instance()->GetDirUserData()
                               + QDir::separator() + "Sticky").toString();
    QFileInfo fi(szFile);
    szFile = RabbitCommon::CDir::GetOpenFileName(this, tr("Open sticky"), fi.path()); // QFileDialog::getOpenFileName();
    if(szFile.isEmpty())
        return;
    Load(szFile);
}

int CFrmStickyList::Load(const QString &szFile)
{
    QFile f(szFile);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "CFrmStickyList::Load file fail: " << szFile;
        return -1;
    }
    QDataStream d(&f);
    QString szVersion;
    QRect rect;
    QPoint pos;
    m_Model.Clean();
    CleanStickyNotes();
    d >> szVersion >> pos >> rect >> m_Model;
    f.close();
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    set.value("Sticky/File", szFile);
    setGeometry(rect);
    move(pos);
    return 0;
}

void CFrmStickyList::slotSave()
{
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    QString szFile = set.value("Sticky/File",
                               RabbitCommon::CDir::Instance()->GetDirUserData()
                               + QDir::separator() + "Sticky").toString();
    QFileInfo fi(szFile);
    szFile = RabbitCommon::CDir::GetSaveFileName(this, tr("Save sticky"), fi.path());
    if(szFile.isEmpty())
        return;
}

int CFrmStickyList::Save(const QString &szFile)
{
    QFile f(szFile);
    if(!f.open(QIODevice::WriteOnly))
    {
        qDebug() << "CFrmStickyList::Save file fail: " << szFile;
        return -1;
    }
    QDataStream d(&f);
    d << "1.0";
    d << this->pos();
    d << geometry();
    d << m_Model;
    f.close();
    return 0;
}

void CFrmStickyList::on_actionNew_triggered()
{
    QSharedPointer<CSticky> s = m_Model.Add();
    if(!s)
        return;
    s->SetContent(tr("Take notes ......"));
    CFrmStickyNotes* sn = NewFrmSticky(s);
    sn->SetSticky(s);
    if(sn)
    {
#if defined (Q_OS_ANDROID)
        sn->showMaximized();
#else
        sn->show();
#endif
    }
}

CFrmStickyNotes* CFrmStickyList::NewFrmSticky(QSharedPointer<CSticky> s)
{
    CFrmStickyNotes* pStickyNote = new CFrmStickyNotes(nullptr);
    if(!pStickyNote)
        return nullptr;
    bool check = connect(pStickyNote, SIGNAL(sigNew()),
                         this, SLOT(on_actionNew_triggered()));
    Q_ASSERT(check);
    check = connect(s.data(), SIGNAL(sigRemove(QSharedPointer<CSticky>)),
                    this, SLOT(slotDelete(QSharedPointer<CSticky>)));
    Q_ASSERT(check);
    m_StickyNotes.push_back(pStickyNote);
    return pStickyNote;
}

void CFrmStickyList::on_actionRemove_triggered()
{
    QModelIndex index = m_lvTasks.currentIndex();
    m_Model.removeRow(index.row());
}

void CFrmStickyList::on_listView_doubleClicked(const QModelIndex &index)
{
    ShowSticky(index.row());
}

void CFrmStickyList::ShowSticky(int i)
{
   if(i < 0 || i >= m_StickyNotes.length())
       return;
#if defined (Q_OS_ANDROID)
   m_StickyNotes.at(i)->showMaximized();
#else
   m_StickyNotes.at(i)->show();
   m_StickyNotes.at(i)->activateWindow();
#endif
}

void CFrmStickyList::slotDelete(QSharedPointer<CSticky> sticky)
{
    foreach(CFrmStickyNotes* s, m_StickyNotes)
    {
        if(s->IsSticky(sticky))
        {
            s->close();
            m_StickyNotes.removeOne(s);
            s->deleteLater();
            return;
        }
    }
}
