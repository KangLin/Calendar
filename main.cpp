#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QSettings>
#include "MainWindow.h"
#include "Global/GlobalDir.h"
#include "FrmUpdater.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    
    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name() + ".qm");
    a.installTranslator(&t);
    set.setValue("Language", QLocale::system().name());

    CMainWindow m;
    bool bShow = set.value("MainWindow/Show", false).toBool();
    if(bShow)
        m.show();
    
    CFrmUpdater u;
    //u.show();
    u.DownloadFile(QUrl("https://raw.githubusercontent.com/KangLin/Tasks/master/Update.xml"));//*/
    //u.DownloadFile(QUrl::fromLocalFile("d:\\Source\\Tasks\\update.xml"));

    return a.exec();
}
