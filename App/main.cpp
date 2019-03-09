#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QSettings>
#include "MainWindow.h"
#include "Global/GlobalDir.h"
#include "FrmUpdater.h"
#include "FrmStickyNotes.h"
#include "FrmStickyList.h"

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
#if defined(Q_OS_ANDROID)
    m.showMaximized();
#else
    bool bShow = set.value("Options/MainWindow/Show", false).toBool();
    if(bShow)
        m.show();
#endif

    return a.exec();
}
