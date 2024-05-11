// 作者：康林 <kl222@126.com>

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

CFrmStickyNotes::CFrmStickyNotes(QWidget *parent) :
    #if defined(Q_OS_ANDROID)
    QWidget (parent),
    #else
    QWidget(parent, 
            Qt::Drawer
            | Qt::CustomizeWindowHint),
    #endif
    ui(new Ui::CFrmStickyNotes),
    m_ToolBarTop(this),
    m_ToolBarButton(this),
    m_TextEdit(this)
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->setupUi(this);
    //Use qss
    //setStyleSheet("background-color:rgb(255,255,128);color:rgb(0,255,0);");
    //setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:15px;}");

    m_ToolBarButton.addAction(QIcon::fromTheme("format-text-bold"), tr("Bold"), this, SLOT(slotBold()));
    m_ToolBarButton.addAction(QIcon::fromTheme("format-text-italic"), tr("Italic"), this, SLOT(slotItalic()));
    m_ToolBarButton.addAction(QIcon::fromTheme("format-text-underline"), tr("Underline"), this, SLOT(slotUnderline()));
    m_ToolBarButton.addAction(QIcon::fromTheme("format-text-strikethrough"), tr("Strikethrough"), this, SLOT(slotStrikethrough()));
    m_ToolBarButton.addSeparator();
    m_ToolBarButton.addAction(QIcon::fromTheme("edit-delete"), tr("Delete"), this, SLOT(slotDelet()));
    m_ToolBarButton.addAction(QIcon::fromTheme("add"), tr("New"), this, SLOT(slotNew()));
    m_ToolBarTop.addAction(QIcon::fromTheme("window-close"), tr("Close"), this, SLOT(close()));
    m_pComboBox = new QComboBox(this);
    m_pComboBox->addItem(tr("Normal"));
    m_pComboBox->addItem(tr("Priority"));
    m_pComboBox->addItem(tr("Delay"));
    m_ToolBarTop.addWidget(m_pComboBox);
#if !defined (Q_OS_ANDROID)
    m_ToolBarTop.hide();
    m_ToolBarButton.hide();
#endif
    bool check = connect(&m_TextEdit, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));
    Q_ASSERT(check);
    check = connect(m_pComboBox, SIGNAL(currentIndexChanged(int)),
                         this, SLOT(slotPolicy(int)));
    Q_ASSERT(check);
    layout()->addWidget(&m_ToolBarTop);
    layout()->addWidget(&m_TextEdit);
    layout()->addWidget(&m_ToolBarButton);
}

CFrmStickyNotes::~CFrmStickyNotes()
{
    qDebug() << "CFrmStickyNotes::~CFrmStickyNotes()";
    delete ui;
}
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void CFrmStickyNotes::enterEvent(QEnterEvent *event)
#else
void CFrmStickyNotes::enterEvent(QEvent *event)
#endif
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
    QSize size;
    QPoint pos;
    m_Sticky->GetWindows(pos, size);
    
    if(!pos.isNull() && this->pos() != pos)
        move(pos);
    if(size.isValid() && this->size() != size)
        resize(size);
    
    if(!m_Sticky->GetContent().isEmpty()
            && m_Sticky->GetContent() != m_TextEdit.toHtml())
        m_TextEdit.setHtml(m_Sticky->GetContent());
    if(m_pComboBox->currentIndex() != m_Sticky->GetPolicy())
        m_pComboBox->setCurrentIndex(m_Sticky->GetPolicy());
    if(m_Sticky->GetWindowHide() != isHidden())
        setHidden(m_Sticky->GetWindowHide());
    
    return 0;
}

bool CFrmStickyNotes::IsSticky(QSharedPointer<CSticky> sticky)
{
    return m_Sticky == sticky;
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
    if(m_Sticky)
    {
        emit m_Sticky->sigRemove(m_Sticky);
    }
}

void CFrmStickyNotes::slotNew()
{
    emit sigNew();
}

void CFrmStickyNotes::slotUpdate()
{
    if(!m_Sticky)
        return;
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
    m_Sticky->SetPolicy(static_cast<CSticky::POLICY>(policy));
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
    m_Sticky->SetText(m_TextEdit.toPlainText());
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
    m_Sticky->SetWindows(this->pos(), this->size());
}

void CFrmStickyNotes::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(!m_Sticky)
        return;
    m_Sticky->SetWindows(pos(), this->size());
}

void CFrmStickyNotes::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    if(!m_Sticky)
        return;
    m_Sticky->SetWindowHide();
}

void CFrmStickyNotes::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(!m_Sticky)
        return;
    m_Sticky->SetWindowHide(false);
}
