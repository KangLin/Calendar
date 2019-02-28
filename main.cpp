#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QSettings>
#include "MainWindow.h"
#include "Global/GlobalDir.h"
#include "FrmUpdater.h"
#include <QThread>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(BUILD_VERSION);

    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    
    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name() + ".qm");
    a.installTranslator(&t);
    set.setValue("Language", QLocale::system().name());

    CFrmUpdater u;
    if(!u.GenerateUpdateXml())
        return 0;
    
    CMainWindow m;
    bool bShow = set.value("MainWindow/Show", false).toBool();
    if(bShow)
        m.show();

    return a.exec();
}
