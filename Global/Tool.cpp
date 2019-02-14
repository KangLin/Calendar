#include "Tool.h"
#include <QSettings>
#include <QApplication>

const QString gCurrentUserRun = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const QString gCurrentUserRunOnce = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
const QString gCurrentUserRunServices = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
const QString gCurrentUserRunServicesOnce = "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce";

const QString gRun = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const QString gRunOnce = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
const QString gRunServices = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServices";
const QString gRunServicesOnce = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce";

CTool::CTool()
{    
}

int CTool::InstallStartRunCurrentUser()
{
    return InstallStartRun(gCurrentUserRun);
}

int CTool::RemoveStartRunCurrentUser()
{
    return RemoveStartRun(gCurrentUserRun);
}

bool CTool::IsStartRunCurrentUser()
{
    return IsStartRun(gCurrentUserRun);
}

int CTool::InstallStartRunOnceCurrentUser()
{
    return InstallStartRun(gCurrentUserRunOnce);
}

int CTool::RemoveStartRunOnceCurrentUser()
{
    return RemoveStartRun(gCurrentUserRunOnce);
}

bool CTool::IsStartRunOnceCurrentUser()
{
    return IsStartRun(gCurrentUserRunOnce);
}

int CTool::InstallStartRunServicesCurrentUser()
{
    return InstallStartRun(gCurrentUserRunServices);
}

int CTool::RemoveStartRunServicesCurrentUser()
{
    return RemoveStartRun(gCurrentUserRunServices);
}

bool CTool::IsStartRunServicesCurrentUser()
{
    return IsStartRun(gCurrentUserRunServices);
}

int CTool::InstallStartRunServicesOnceCurrentUser()
{
    return InstallStartRun(gCurrentUserRunServicesOnce);
}

int CTool::RemoveStartRunServicesOnceCurrentUser()
{
    return RemoveStartRun(gCurrentUserRunServicesOnce);
}

bool CTool::IsStartRunServicesOnceCurrentUser()
{
    return IsStartRun(gCurrentUserRunServicesOnce);
}

int CTool::InstallStartRun()
{
    return InstallStartRun(gRun);
}

int CTool::RemoveStartRun()
{
    return RemoveStartRun(gRun);
}

bool CTool::IsStartRun()
{
    return IsStartRun(gRun);
}

int CTool::InstallStartRunOnce()
{
    return InstallStartRun(gRunOnce);
}

int CTool::RemoveStartRunOnce()
{
    return RemoveStartRun(gRunOnce);
}

bool CTool::IsStartRunOnce()
{
    return IsStartRun(gRunOnce);
}

int CTool::InstallStartRunServices()
{
    return InstallStartRun(gRunServices);
}

int CTool::RemoveStartRunServices()
{
    return RemoveStartRun(gRunServices);
}

bool CTool::IsStartRunServices()
{
    return IsStartRun(gRunServices);
}

int CTool::InstallStartRunServicesOnce()
{
    return InstallStartRun(gRunServicesOnce);
}

int CTool::RemoveStartRunServicesOnce()
{
    return RemoveStartRun(gRunServicesOnce);
}

bool CTool::IsStartRunServicesOnce()
{
    return IsStartRun(gRunServicesOnce);
}

int CTool::InstallStartRun(const QString &reg)
{
    QString appName = QApplication::applicationName();
    QString appPath = QApplication::applicationFilePath();
    return SetRegister(reg, appName, appPath);
}

int CTool::RemoveStartRun(const QString &reg)
{
    QString appName = QApplication::applicationName();
    return RemoveRegister(reg, appName);
}

bool CTool::IsStartRun(const QString &reg)
{
    QString appName = QApplication::applicationName();
    return IsRegister(reg, appName);
}

int CTool::SetRegister(const QString &reg, const QString &name, const QString &path)
{
    QSettings r(reg, QSettings::NativeFormat);
    QString val = r.value(name).toString();
    if(val != path)
        r.setValue(name, path);
    return 0;
}

int CTool::RemoveRegister(const QString &reg, const QString &name)
{
    QSettings r(reg, QSettings::NativeFormat);
    QString val = r.value(name).toString();
    if(!val.isEmpty())
        r.remove(name);
    return 0;
}

bool CTool::IsRegister(const QString &reg, const QString &name)
{
    QSettings r(reg, QSettings::NativeFormat);
    QString val = r.value(name).toString();
    return !val.isEmpty();
}
