#include "TasksTools.h"
#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QLocale>
#if defined(Q_OS_WIN)
    #include <Windows.h>
#endif

#include "LunarCalendar.h"

const QString gCurrentUserRun = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const QString gCurrentUserRunOnce = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
const QString gCurrentUserRunServices = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
const QString gCurrentUserRunServicesOnce = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce";

const QString gRun = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const QString gRunOnce = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
const QString gRunServices = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
const QString gRunServicesOnce = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce";

CTasksTools::CTasksTools()
{}

CTasksTools::~CTasksTools()
{}

CTasksTools* CTasksTools::Instance()
{
    static CTasksTools* pTools = nullptr;
    if(nullptr == pTools)
        pTools = new CTasksTools();
    return pTools;
}

void CTasksTools::InitTranslator()
{
    QString szPre;    
#if defined(Q_OS_ANDROID) || _DEBUG
    szPre = ":/Translations";
#else
    szPre = qApp->applicationDirPath() + QDir::separator() + ".." + QDir::separator() + "translations";
#endif
    m_Translator.load(szPre + "/Tasks_" + QLocale::system().name() + ".qm");
    qApp->installTranslator(&m_Translator);
    
    CLunarCalendar::InitTranslator();
}

void CTasksTools::CLeanTranslator()
{
    qApp->removeTranslator(&m_Translator);
}

int CTasksTools::InstallStartRunCurrentUser()
{
    return InstallStartRun(gCurrentUserRun);
}

int CTasksTools::RemoveStartRunCurrentUser()
{
    return RemoveStartRun(gCurrentUserRun);
}

bool CTasksTools::IsStartRunCurrentUser()
{
    return IsStartRun(gCurrentUserRun);
}

int CTasksTools::InstallStartRunOnceCurrentUser()
{
    return InstallStartRun(gCurrentUserRunOnce);
}

int CTasksTools::RemoveStartRunOnceCurrentUser()
{
    return RemoveStartRun(gCurrentUserRunOnce);
}

bool CTasksTools::IsStartRunOnceCurrentUser()
{
    return IsStartRun(gCurrentUserRunOnce);
}

int CTasksTools::InstallStartRunServicesCurrentUser()
{
    return InstallStartRun(gCurrentUserRunServices);
}

int CTasksTools::RemoveStartRunServicesCurrentUser()
{
    return RemoveStartRun(gCurrentUserRunServices);
}

bool CTasksTools::IsStartRunServicesCurrentUser()
{
    return IsStartRun(gCurrentUserRunServices);
}

int CTasksTools::InstallStartRunServicesOnceCurrentUser()
{
    return InstallStartRun(gCurrentUserRunServicesOnce);
}

int CTasksTools::RemoveStartRunServicesOnceCurrentUser()
{
    return RemoveStartRun(gCurrentUserRunServicesOnce);
}

bool CTasksTools::IsStartRunServicesOnceCurrentUser()
{
    return IsStartRun(gCurrentUserRunServicesOnce);
}

int CTasksTools::InstallStartRun()
{
    return InstallStartRun(gRun);
}

int CTasksTools::RemoveStartRun()
{
    return RemoveStartRun(gRun);
}

bool CTasksTools::IsStartRun()
{
    return IsStartRun(gRun);
}

int CTasksTools::InstallStartRunOnce()
{
    return InstallStartRun(gRunOnce);
}

int CTasksTools::RemoveStartRunOnce()
{
    return RemoveStartRun(gRunOnce);
}

bool CTasksTools::IsStartRunOnce()
{
    return IsStartRun(gRunOnce);
}

int CTasksTools::InstallStartRunServices()
{
    return InstallStartRun(gRunServices);
}

int CTasksTools::RemoveStartRunServices()
{
    return RemoveStartRun(gRunServices);
}

bool CTasksTools::IsStartRunServices()
{
    return IsStartRun(gRunServices);
}

int CTasksTools::InstallStartRunServicesOnce()
{
    return InstallStartRun(gRunServicesOnce);
}

int CTasksTools::RemoveStartRunServicesOnce()
{
    return RemoveStartRun(gRunServicesOnce);
}

bool CTasksTools::IsStartRunServicesOnce()
{
    return IsStartRun(gRunServicesOnce);
}

int CTasksTools::InstallStartRun(const QString &szReg, const QString &szName, const QString &szPath)
{
    QString appName = QApplication::applicationName();
    QString appPath = QApplication::applicationFilePath();
    if(!szName.isEmpty())
        appName = szName;
    if(!szPath.isEmpty())
        appPath = szPath;
    return SetRegister(szReg, appName, appPath);
}

int CTasksTools::RemoveStartRun(const QString &szReg, const QString &szName)
{
    QString appName = QApplication::applicationName();
    if(!szName.isEmpty())
        appName = szName;
    return RemoveRegister(szReg, appName);
}

bool CTasksTools::IsStartRun(const QString &szReg, const QString &szName)
{
    QString appName = QApplication::applicationName();
    if(!szName.isEmpty())
        appName = szName;
    return IsRegister(szReg, appName);
}

int CTasksTools::SetRegister(const QString &reg, const QString &name, const QString &path)
{
    QSettings r(reg, QSettings::NativeFormat);
    QString val = r.value(name).toString();
    if(val != path)
        r.setValue(name, path);
    return 0;
}

int CTasksTools::RemoveRegister(const QString &reg, const QString &name)
{
    QSettings r(reg, QSettings::NativeFormat);
    QString val = r.value(name).toString();
    if(!val.isEmpty())
        r.remove(name);
    return 0;
}

bool CTasksTools::IsRegister(const QString &reg, const QString &name)
{
    QSettings r(reg, QSettings::NativeFormat);
    QString val = r.value(name).toString();
    return !val.isEmpty();
}

int CTasksTools::ScreenPower(bool bOff)
{
#if defined(Q_OS_WIN)
    if(bOff)
        SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    else 
        SendMessage(FindWindow(0, 0), WM_SYSCOMMAND, SC_MONITORPOWER, -1);
#endif
    return 0;
}

int CTasksTools::ScreenSaver(bool bSaver)
{
#if defined(Q_OS_WIN)
    ::SystemParametersInfo( SPI_SETSCREENSAVEACTIVE, bSaver, 0, 0 );
#endif
    return 0;
}

/*
取消电源管理，避免睡眠、待机：  

::SetThreadExecutionState( ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED );

 恢复电源管理：  

::SetThreadExecutionState( ES_CONTINUOUS );

*/ 
