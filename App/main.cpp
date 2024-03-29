#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLoggingCategory>
#include <QSettings>
#include <QDir>
#if defined(Q_OS_ANDROID) \
    && QT_VERSION >= QT_VERSION_CHECK(5, 7, 0) \
    && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #include <QtAndroidExtras/QtAndroid>
#endif

#include "MainWindow.h"
#include "FrmStickyNotes.h"
#include "FrmStickyList.h"
#include "Global/TasksTools.h"
#ifdef RABBITCOMMON
    #include "RabbitCommonDir.h"
    #include "RabbitCommonTools.h"
    #include "FrmUpdater.h"
#endif
#include "LunarCalendar.h"

static Q_LOGGING_CATEGORY(log, "Rabbit.LunarCalendar")

int main(int argc, char *argv[])
{
#if (QT_VERSION > QT_VERSION_CHECK(5,6,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#if defined(Q_OS_ANDROID) \
    && QT_VERSION >= QT_VERSION_CHECK(5, 7, 0) \
    && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QtAndroid::hideSplashScreen();
#endif

    QApplication a(argc, argv);
    a.setApplicationVersion(Calendar_VERSION);
    a.setApplicationName("Calendar");

    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);

    QTranslator tApp;
    bool bRet = tApp.load(RabbitCommon::CDir::Instance()->GetDirTranslations()
              + QDir::separator() + a.applicationName() + "App_"
              + QLocale::system().name() + ".qm");
    if(bRet)
        a.installTranslator(&tApp);
    qInfo(log) << "Language:" << QLocale::system().name();

    CTasksTools::Instance()->InitResource();
#ifdef RABBITCOMMON
    RabbitCommon::CTools::Instance()->Init();
    QStringList permissions("android.permission.VIBRATE");
    permissions << "android.permission.ACCESS_FINE_LOCATION"
                << "android.permission.BLUETOOTH";
    RabbitCommon::CTools::Instance()->AndroidRequestPermission(permissions);
#endif

    a.setApplicationDisplayName(QObject::tr("Calendar"));
    
    qInfo(log) << QObject::tr("Calendar version: ") + Calendar_VERSION
#ifdef Calendar_REVISION
               + " (Revision: [" + Calendar_REVISION
                      + "](https://github.com/KangLin/"
                      + a.applicationName() +"/tree/"
                      + Calendar_REVISION + "))"
#endif
               + "; " + QObject::tr("LunarCalendar: ") + CLunarCalendar::Version()
               + "; " + QObject::tr("Rabbit Common: ") + RabbitCommon::CTools::Version();
        ;

#ifdef RABBITCOMMON
    CFrmUpdater *pUpdate = new CFrmUpdater();
    QIcon icon = QIcon::fromTheme("calendar");
    if(!icon.isNull()) {
        auto sizeList = icon.availableSizes();
        if(!sizeList.isEmpty()) {
            QPixmap p = icon.pixmap(*sizeList.begin());
            pUpdate->SetTitle(p.toImage());
        }
    }
    pUpdate->SetInstallAutoStartup();
    if(a.arguments().length() > 1) {
        pUpdate->GenerateUpdateJson();
        pUpdate->GenerateUpdateXml();
        return 0;
    }
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

    if(bRet)
        a.removeTranslator(&tApp);
    CTasksTools::Instance()->CleanResource();
    return nRet;
}
