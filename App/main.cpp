#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QSettings>
#include "MainWindow.h"
#include "FrmStickyNotes.h"
#include "FrmStickyList.h"
#include "Global/TasksTools.h"
#ifdef RABBITCOMMON
    #include "RabbitCommonDir.h"
    #include "RabbitCommonTools.h"
    #include "FrmUpdater/FrmUpdater.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationVersion(BUILD_VERSION);
    a.setApplicationName("Tasks");
    
//#if defined(Q_OS_ANDROID) && QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
//    QtAndroid::hideSplashScreen();
//#endif
    
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);

    QTranslator tApp, tTasks, tLunarCalendar;
    tApp.load(RabbitCommon::CDir::Instance()->GetDirTranslations()
              + "/TasksApp_" + QLocale::system().name() + ".qm");
    a.installTranslator(&tApp);
    qInfo() << "Language:" << QLocale::system().name();

    CTasksTools::Instance()->InitResource();
#ifdef RABBITCOMMON
    RabbitCommon::CTools::Instance()->Init();
#endif
    
    a.setApplicationDisplayName(QObject::tr("Tasks"));
    
#ifdef RABBITCOMMON 
    CFrmUpdater *pUpdate = new CFrmUpdater();
    pUpdate->SetTitle(QImage(":/icon/App"));
    if(!pUpdate->GenerateUpdateXml()) 
        return 0; 
#endif
    
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
