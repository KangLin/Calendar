#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QSettings>
#include "MainWindow.h"
#include "FrmEyeNurse.h"
#include "Global/GlobalDir.h"

int main(int argc, char *argv[])
{
    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    
    QApplication a(argc, argv);

    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name());
    a.installTranslator(&t);
    set.setValue("Language", QLocale::system().name());

    CMainWindow m;
    bool bShow = set.value("MainWindow/Show", false).toBool();
    if(bShow)
        m.show();

    /*CFrmUpdater u;
    u.show();
    u.StartDownload("https://github.com/qTox/qTox/blob/master/updater/update.cpp");//*/
    /*MainWindow w;
    w.show();//*/

    //CFrmEyeNurse en;

    return a.exec();
}
