#include "FrmStickyNotes.h"
#include "ui_FrmStickyNotes.h"
#include <QDebug>
#include <string>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QApplication>
#include <QScreen>
#include <QSpacerItem>
#include <QBuffer>

CFrmStickyNotes::CFrmStickyNotes(QWidget *parent,
                                 QSharedPointer<CSticky> sticky) :
    QWidget(parent, 
            Qt::Drawer
            | Qt::CustomizeWindowHint),
    ui(new Ui::CFrmStickyNotes),
    m_ToolBarTop(this),
    m_ToolBarButton(this),
    m_TextEdit(this)
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    //TODO:Use qss
    //setStyleSheet("background-color:rgb(255,255,128);color:rgb(0,255,0);");
    //setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:15px;}"); 

    m_ToolBarButton.addAction(QIcon(":/icon/Bold"), tr("Bold"), this, SLOT(slotBold()));
    m_ToolBarButton.addAction(QIcon(":/icon/Italic"), tr("Italic"), this, SLOT(slotItalic()));
    m_ToolBarButton.addAction(QIcon(":/icon/Underline"), tr("Underline"), this, SLOT(slotUnderline()));
    m_ToolBarButton.addAction(QIcon(":/icon/Stricke"), tr("Strikethrough"), this, SLOT(slotStrikethrough()));
    m_ToolBarButton.addSeparator();
    m_ToolBarButton.addAction(QIcon(":/icon/Delete"), tr("Delete"), this, SLOT(slotDelet()));
    m_ToolBarButton.addAction(QIcon(":/icon/Add"), tr("New"), this, SLOT(slotNew()));
    m_ToolBarTop.addAction(QIcon(":/icon/Close"), tr("Close"), this, SLOT(close()));
    m_pComboBox = new QComboBox(this);
    m_pComboBox->addItem(tr("Normal"));
    m_pComboBox->addItem(tr("Priority"));
    m_pComboBox->addItem(tr("Delay"));
    m_ToolBarTop.addWidget(m_pComboBox);
    m_ToolBarTop.hide();
    m_ToolBarButton.hide();
    
    bool check = connect(&m_TextEdit, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));
    Q_ASSERT(check);
    check = connect(m_pComboBox, SIGNAL(currentIndexChanged(int)),
                         this, SLOT(slotPolicy(int)));
    Q_ASSERT(check);
    layout()->addWidget(&m_ToolBarTop);
    layout()->addWidget(&m_TextEdit);
    layout()->addWidget(&m_ToolBarButton);
    
    this->SetSticky(sticky);    
}

CFrmStickyNotes::~CFrmStickyNotes()
{
    qDebug() << "CFrmStickyNotes::~CFrmStickyNotes()";
    delete ui;
}

void CFrmStickyNotes::enterEvent(QEvent *event)
{
    qDebug() << "CFrmStickyNotes::enterEvent";
    Q_UNUSED(event);

    if(this->isHidden())
        return;
   
    m_ToolBarTop.show();
    m_ToolBarButton.show();    
}

void CFrmStickyNotes::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CFrmStickyNotes::leaveEvent";

    QRect rect = this->geometry();
    if(rect.contains(cursor().pos()))
        return;
    m_ToolBarTop.hide();
    m_ToolBarButton.hide();
}

int CFrmStickyNotes::SetSticky(QSharedPointer<CSticky> sticky)
{
    if(!sticky)
        return -1;
    m_Sticky = sticky;
    bool check = connect(m_Sticky.data(), SIGNAL(sigUpdate()),
                         this, SLOT(slotUpdate()));
    Q_ASSERT(check);
    check = connect(m_Sticky.data(), SIGNAL(sigRemove(QSharedPointer<CSticky>)),
                    this, SLOT(slotDelet(QSharedPointer<CSticky>)));
    Q_ASSERT(check);
    if(!m_Sticky->GetContent().isEmpty())
        m_TextEdit.setHtml(m_Sticky->GetContent());
    if(!m_Sticky->GetWindowRect().isNull())
        this->setGeometry(m_Sticky->GetWindowRect());
    m_pComboBox->setCurrentIndex(m_Sticky->GetPolicy());
    if(m_Sticky->GetWindowHide() != isHidden())
        setHidden(m_Sticky->GetWindowHide());

    return 0;
}

void CFrmStickyNotes::slotBold()
{
    QTextCharFormat fmt = m_TextEdit.textCursor().charFormat();
    QFont f = fmt.font();
    f.setBold(!f.bold());
    fmt.setFont(f);
    if(!m_TextEdit.textCursor().hasSelection())
        m_TextEdit.textCursor().select(QTextCursor::WordUnderCursor);
    m_TextEdit.textCursor().mergeCharFormat(fmt);
}

void CFrmStickyNotes::slotItalic()
{
    QTextCharFormat fmt = m_TextEdit.textCursor().charFormat();
    QFont f = fmt.font();
    f.setItalic(!f.italic());
    fmt.setFont(f);
    fmt.setFont(f);
    m_TextEdit.textCursor().mergeCharFormat(fmt);
}

void CFrmStickyNotes::slotUnderline()
{
    QTextCharFormat fmt = m_TextEdit.textCursor().charFormat();
    QFont f = fmt.font();
    f.setUnderline(!f.underline());
    fmt.setFont(f);
    fmt.setFont(f);
    m_TextEdit.textCursor().mergeCharFormat(fmt);
}

void CFrmStickyNotes::slotStrikethrough()
{
    QTextCharFormat fmt = m_TextEdit.textCursor().charFormat();
    QFont f = fmt.font();
    f.setStrikeOut(!f.strikeOut());
    fmt.setFont(f);
    fmt.setFont(f);
    m_TextEdit.textCursor().mergeCharFormat(fmt);
}

void CFrmStickyNotes::slotDelet()
{
    close();
    if(m_Sticky)
        emit m_Sticky->sigRemove(m_Sticky);
}

void CFrmStickyNotes::slotDelet(QSharedPointer<CSticky>)
{
    close();
}

void CFrmStickyNotes::slotNew()
{
    emit sigNew();
}

void CFrmStickyNotes::slotUpdate()
{
    if(!m_Sticky)
        return;
    //loop signal
    if(m_TextEdit.toHtml() != m_Sticky->GetContent())
        m_TextEdit.setHtml(m_Sticky->GetContent());
    if(m_Sticky->GetPolicy() != m_pComboBox->currentIndex())
        slotPolicy(m_Sticky->GetPolicy());
    if(m_Sticky->GetWindowHide() != isHidden())
    {
        if(m_Sticky->GetWindowHide())
            hide();
        else
            show();
    }
}

void CFrmStickyNotes::slotPolicy(int policy)
{
    if(!m_Sticky)
        return;
    m_Sticky->SetPolicy((CSticky::POLICY)policy);
    switch (policy) {
    case CSticky::normal:
        m_TextEdit.setStyleSheet("");
        break;
    case CSticky::priority:
        m_TextEdit.setStyleSheet("QTextEdit { background: red }");
        break;
    case CSticky::delay:  
        m_TextEdit.setStyleSheet("QTextEdit { background: blue }");
        break;
    }
}

void CFrmStickyNotes::slotTextChanged()
{
    if(!m_Sticky)
        return;
    m_Sticky->SetContent(m_TextEdit.toHtml());
}

void CFrmStickyNotes::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bMoveable)
    {
        m_oldTop.setX(m_oldTop.x() + (e->screenPos().x() - m_oldPos.x()));
        m_oldTop.setY(m_oldTop.y() + (e->screenPos().y() - m_oldPos.y()));
        if(m_oldTop.x() < 0)
            m_oldTop.setX(0);
        if(m_oldTop.y() < 0)
            m_oldTop.setY(0);
        if(m_oldTop.x() + frameGeometry().width()
                > QApplication::primaryScreen()->geometry().width())
            m_oldTop.setX(QApplication::primaryScreen()->geometry().width()
                          - frameGeometry().width());
        if(m_oldTop.y() + frameGeometry().height()
                > QApplication::primaryScreen()->geometry().height())
            m_oldTop.setY(QApplication::primaryScreen()->geometry().height()
                          - frameGeometry().height());
        m_oldPos = e->screenPos();
        move(m_oldTop);
    }
}

void CFrmStickyNotes::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_oldTop = this->pos();
        m_oldPos = e->screenPos();
        m_bMoveable = true;
    }
}

void CFrmStickyNotes::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        m_bMoveable = false;
}


void CFrmStickyNotes::focusInEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CFrmStickyNotes::focusInEvent";
}

void CFrmStickyNotes::focusOutEvent(QFocusEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CFrmStickyNotes::focusOutEvent";
}


void CFrmStickyNotes::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
    if(!m_Sticky)
        return;
    m_Sticky->SetWindowRect(frameGeometry());
}

void CFrmStickyNotes::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(!m_Sticky)
        return;
    m_Sticky->SetWindowRect(frameGeometry());
}

void CFrmStickyNotes::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    m_Sticky->SetWindowHide();
}


void CFrmStickyNotes::showEvent(QShowEvent *event)
{
    m_Sticky->SetWindowHide(false);
}
