// 作者：康林 <kl222@126.com>

#include "TaskDay.h"

CTaskDay::CTaskDay(QObject *parent) : CTaskPromptDelay(parent)
{
    
}

int CTaskDay::Init()
{
    setObjectName("TaskDay");
    return 0;
}

int CTaskDay::onStart()
{
    return 0;
}

int CTaskDay::onRun()
{
    return 0;
}

int CTaskDay::Start()
{
    return 0;
}
