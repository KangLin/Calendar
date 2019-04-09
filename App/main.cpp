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
    a.setApplicationName("Tasks");

    QSettings set(CGlobalDir::Instance()->GetUserConfigureFile(),
                  QSettings::IniFormat);
    QString szPre;
   
#if defined(Q_OS_ANDROID) || _DEBUG
    szPre = ":/Translations";
#else
    szPre = CGlobalDir::Instance()->GetDirTranslations();
#endif
    
    QTranslator tApp, tTasks, tLunarCalendar;
    tApp.load(szPre + "/TasksApp_" + QLocale::system().name() + ".qm");
    a.installTranslator(&tApp);
    tTasks.load(szPre + "/Tasks_" + QLocale::system().name() + ".qm");
    a.installTranslator(&tTasks);
    tLunarCalendar.load(szPre + "/LunarCalendar_" + QLocale::system().name() + ".qm");
    a.installTranslator(&tLunarCalendar);
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
