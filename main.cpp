#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "FrmUpdater.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name());
    a.installTranslator(&t);
    CFrmUpdater u;
    u.show();
    u.StartDownload("https://github.com/qTox/qTox/blob/master/updater/update.cpp");
    //MainWindow w;
    //w.show();
    return a.exec();
}
