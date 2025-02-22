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
#include "RabbitCommonDir.h"
#include "RabbitCommonTools.h"
#include "FrmUpdater.h"
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

    QApplication app(argc, argv);
    app.setApplicationVersion(Calendar_VERSION);
    app.setApplicationName("Calendar");

    RabbitCommon::CTools::Instance()->Init();

    QStringList permissions("android.permission.VIBRATE");
    permissions << "android.permission.ACCESS_FINE_LOCATION"
                << "android.permission.BLUETOOTH";
    RabbitCommon::CTools::Instance()->AndroidRequestPermission(permissions);
    
    RabbitCommon::CTools::Instance()->InstallTranslator("CalendarApp");

    CTasksTools::Instance()->InitResource();

    app.setApplicationDisplayName(QObject::tr("Calendar"));
    
    qInfo(log) << QObject::tr("Calendar version: ") + Calendar_VERSION
#ifdef Calendar_REVISION
               + " (Revision: [" + Calendar_REVISION
                      + "](https://github.com/KangLin/"
                      + app.applicationName() +"/tree/"
                      + Calendar_REVISION + "))"
#endif
               + "; " + QObject::tr("LunarCalendar: ") + CLunarCalendar::Version()
               + "; " + QObject::tr("Rabbit Common: ") + RabbitCommon::CTools::Version();
        ;

    CFrmUpdater *pUpdate = new CFrmUpdater();
    if(pUpdate) {
        QIcon icon = QIcon::fromTheme("calendar");
        if(!icon.isNull()) {
            auto sizeList = icon.availableSizes();
            if(!sizeList.isEmpty()) {
                QPixmap p = icon.pixmap(*sizeList.begin());
                pUpdate->SetTitle(p.toImage());
            }
        }
        pUpdate->SetInstallAutoStartup();
        if(app.arguments().length() > 1) {
            try{
                pUpdate->GenerateUpdateJson();
                pUpdate->GenerateUpdateXml();
            } catch(...) {
                qCritical(log) << "Generate update fail";
            }

            qInfo(log) << app.applicationName() + " " + app.applicationVersion()
                              + " " + QObject::tr("Generate update json file End");
            return 0;
        }
    }

    CMainWindow win;
#if defined(Q_OS_ANDROID)
    win.showMaximized();
#else
    QSettings set(RabbitCommon::CDir::Instance()->GetFileUserConfigure(),
                  QSettings::IniFormat);
    bool bShow = set.value("Options/MainWindow/Show", false).toBool();
    if(bShow)
        win.show();
#endif

    int nRet = app.exec();

    RabbitCommon::CTools::Instance()->Clean();

    CTasksTools::Instance()->CleanResource();

    qInfo(log) << app.applicationName() + " " + app.applicationVersion() + " " + QObject::tr("End");

    return nRet;
}
