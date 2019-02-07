#include "FrmStickyNotes.h"
#include "ui_FrmStickyNotes.h"
#include <QDebug>
#include <string>

CFrmStickyNotes::CFrmStickyNotes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CFrmStickyNotes)
{
    ui->setupUi(this);
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
    ui->teContent->setText(szText.c_str());
    return nRet;
}

int CFrmStickyNotes::Save(std::ostream out)
{
    int nRet = 0;
    std::string szText = ui->teContent->toPlainText().toStdString();
    out << szText;
    return nRet;
}
