#ifndef TASKS_TOOL_H
#define TASKS_TOOL_H

#include <QTranslator>
#include <QString>
#include "tasks_export.h"

class TASKS_EXPORT CTasksTools
{
private:
    CTasksTools();
    ~CTasksTools();
    
public:
    static CTasksTools* Instance();
    
    void InitResource();
    void CleanResource();
    
    //https://zhidao.baidu.com/question/67815593.html
    static int InstallStartRunCurrentUser();
    static int RemoveStartRunCurrentUser();
    static bool IsStartRunCurrentUser();
    
    static int InstallStartRunOnceCurrentUser();
    static int RemoveStartRunOnceCurrentUser();
    static bool IsStartRunOnceCurrentUser();
    
    static int InstallStartRunServicesCurrentUser();
    static int RemoveStartRunServicesCurrentUser();
    static bool IsStartRunServicesCurrentUser();
    
    static int InstallStartRunServicesOnceCurrentUser();
    static int RemoveStartRunServicesOnceCurrentUser();
    static bool IsStartRunServicesOnceCurrentUser();
    
    static int InstallStartRun();
    static int RemoveStartRun();
    static bool IsStartRun();
    
    static int InstallStartRunOnce();
    static int RemoveStartRunOnce();
    static bool IsStartRunOnce();
    
    static int InstallStartRunServices();
    static int RemoveStartRunServices();
    static bool IsStartRunServices();
    
    static int InstallStartRunServicesOnce();
    static int RemoveStartRunServicesOnce();
    static bool IsStartRunServicesOnce();
    
    static int InstallStartRun(const QString &szReg,
                               const QString &szName = QString(),
                               const QString &szPath = QString());
    static int RemoveStartRun(const QString &szReg,
                              const QString &szName = QString());
    static bool IsStartRun(const QString &szReg,
                           const QString &szName = QString());

    static int ScreenPower(bool bOff);
    static int ScreenSaver(bool bSaver);
    
private:
    QTranslator m_Translator;
    
    static int SetRegister(const QString &reg, const QString &name, const QString &path);
    static int RemoveRegister(const QString &reg, const QString &name);
    static bool IsRegister(const QString &reg, const QString &name);
    
    void InitTranslator();
    void CLeanTranslator();
};

#endif // TASKS_TOOL_H
