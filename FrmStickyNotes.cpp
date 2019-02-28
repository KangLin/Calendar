#include "FrmStickyNotes.h"
#include "ui_FrmStickyNotes.h"
#include <QDebug>
#include <string>

CFrmStickyNotes::CFrmStickyNotes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmStickyNotes)
{
    setWindowFlags(Qt::ToolTip|windowFlags());
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->setupUi(this);
    //TODO:Use qss
    setStyleSheet("background-color:rgb(255,255,128);color:rgb(0,255,0);");
    //setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:15px;}"); 
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
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

void CFrmStickyNotes::focusInEvent(QFocusEvent *event)
{
    setWindowFlags(~(Qt::WindowFlags)Qt::ToolTip & windowFlags());
}

void CFrmStickyNotes::focusOutEvent(QFocusEvent *event)
{
    setWindowFlags(Qt::ToolTip|windowFlags());
}
