#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "FrmStickyNotes.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name());
    a.installTranslator(&t);
    CFrmStickyNotes fs;
    fs.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
