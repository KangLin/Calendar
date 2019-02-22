#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include "MainWindow.h"
#include "FrmEyeNurse.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name());
    a.installTranslator(&t);

    CMainWindow m;
#if defined (_DEBUG) || defined (DEBUG)
    m.show();
#endif
    /*CFrmUpdater u;
    u.show();
    u.StartDownload("https://github.com/qTox/qTox/blob/master/updater/update.cpp");//*/
    /*MainWindow w;
    w.show();//*/

    //CFrmEyeNurse en;

    return a.exec();
}
