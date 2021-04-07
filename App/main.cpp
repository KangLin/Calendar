#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QSettings>
#if defined(Q_OS_ANDROID)
    #include <QtAndroidExtras/QtAndroid>
#endif

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
#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#if defined(Q_OS_ANDROID) && QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
    QtAndroid::hideSplashScreen();
#endif
    
    QApplication a(argc, argv);
    a.setApplicationVersion(BUILD_VERSION);
    a.setApplicationName("Calendar");
    
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);

    QTranslator tApp, tTasks, tLunarCalendar;
    tApp.load(RabbitCommon::CDir::Instance()->GetDirTranslations()
              + QDir::separator() + a.applicationName() + "App_"
              + QLocale::system().name() + ".qm");
    a.installTranslator(&tApp);
    qInfo() << "Language:" << QLocale::system().name();

    CTasksTools::Instance()->InitResource();
#ifdef RABBITCOMMON
    RabbitCommon::CTools::Instance()->Init();
#endif
    
    a.setApplicationDisplayName(QObject::tr("Calendar"));
    
#ifdef RABBITCOMMON
    CFrmUpdater *pUpdate = new CFrmUpdater();
    pUpdate->SetTitle(QImage(":/icon/App"));
    pUpdate->SetInstallAutoStartup();
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

    int nRet = a.exec();
    
#ifdef RABBITCOMMON
    RabbitCommon::CTools::Instance()->Clean();
#endif
    
    a.removeTranslator(&tApp);
    CTasksTools::Instance()->CleanResource();
    return nRet;
}
