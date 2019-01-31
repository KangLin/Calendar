#include "TaskPrompt.h"

CTaskPrompt::CTaskPrompt(QObject *parent = nullptr) : CTask(parent)
{
}

int CTaskPrompt::slotStart()
{
    CTask::slotStart();
    //TODO: prompt
    
}

int CTaskPrompt::onRun()
{
    
}
