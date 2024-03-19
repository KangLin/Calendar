#ifndef TASKS_TOOL_H
#define TASKS_TOOL_H

#include <QTranslator>
#include <QString>
#include <QTranslator>
#include <QSharedPointer>
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
    
    static int ScreenPower(bool bOff);
    static int ScreenSaver(bool bSaver);
    
private:
    QSharedPointer<QTranslator> m_Translator;
        
    void InitTranslator();
    void CLeanTranslator();
};

#endif // TASKS_TOOL_H
