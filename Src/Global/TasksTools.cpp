#include "TasksTools.h"
#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QDebug>
#if defined(Q_OS_WIN)
    #include <Windows.h>
#endif

#include "LunarCalendar.h"
#include "RabbitCommonDir.h"

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
    m_Translator.load(RabbitCommon::CDir::Instance()->GetDirTranslations()
                      + "/Tasks_" + QLocale::system().name() + ".qm");
    qApp->installTranslator(&m_Translator);
}

void CTasksTools::CLeanTranslator()
{
    qApp->removeTranslator(&m_Translator);
}

void CTasksTools::InitResource()
{
    InitTranslator();
    Q_INIT_RESOURCE(ResourceTasks);
#if _DEBUG
    Q_INIT_RESOURCE(translations_Tasks);
#endif
}

void CTasksTools::CleanResource()
{
    Q_CLEANUP_RESOURCE(ResourceTasks);
#if _DEBUG
    Q_CLEANUP_RESOURCE(translations_Tasks);
#endif
    CLeanTranslator();
}

int CTasksTools::ScreenPower(bool bOff)
{
    Q_UNUSED(bOff);
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
    Q_UNUSED(bSaver);
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
