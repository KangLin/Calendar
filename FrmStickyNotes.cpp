#include "FrmStickyNotes.h"
#include "ui_FrmStickyNotes.h"
#include <QDebug>
#include <string>

#include <QHBoxLayout>

CFrmStickyNotes::CFrmStickyNotes(QWidget *parent) :
    QWidget(parent, 
            Qt::Drawer
            | Qt::CustomizeWindowHint),
    ui(new Ui::CFrmStickyNotes),
    m_ToolBar(this)
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    //TODO:Use qss
    setStyleSheet("background-color:rgb(255,255,128);color:rgb(0,255,0);");
    //setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:15px;}"); 
    
    m_ToolBar.addAction(tr("Bold"), this, SLOT(slotBold()));
    m_ToolBar.addAction(tr("Italic"), this, SLOT(slotItalic()));
    m_ToolBar.addAction(tr("Underline"), this, SLOT(slotUnderline()));
    m_ToolBar.addAction(tr("Strikethrough"), this, SLOT(slotStrikethrough()));
    m_ToolBar.addAction(QIcon(":/icon/Delete"), tr("Delete"), this, SLOT(slotDelet()));
    m_ToolBar.show();
    this->layout()->addWidget(&m_ToolBar);
}

CFrmStickyNotes::~CFrmStickyNotes()
{
    qDebug() << "CFrmStickyNotes::~CFrmStickyNotes()";
    delete ui;
}

int CFrmStickyNotes::Load(std::istream in)
{
    int nRet = 0;
    std::string szText;
    in >> szText;
    ui->teContent->setHtml(szText.c_str());
    return nRet;
}

int CFrmStickyNotes::Save(std::ostream out)
{
    int nRet = 0;
    std::string szText = ui->teContent->toHtml().toStdString();
    out << szText;
    return nRet;
}

void CFrmStickyNotes::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setWindowFlags(Qt::Drawer
                   | Qt::WindowTitleHint
                   | Qt::WindowCloseButtonHint
                   | Qt::CustomizeWindowHint);
    show();               
    qDebug() << "CFrmStickyNotes::enterEvent";
}

void CFrmStickyNotes::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "CFrmStickyNotes::leaveEvent";
    setWindowFlags(Qt::Drawer
                   | Qt::CustomizeWindowHint);
    show();
}

void CFrmStickyNotes::slotBold()
{
    
}

void CFrmStickyNotes::slotItalic()
{
    
}

void CFrmStickyNotes::slotUnderline()
{
    
}

void CFrmStickyNotes::slotStrikethrough()
{
    
}

void CFrmStickyNotes::slotDelet()
{
    
}
