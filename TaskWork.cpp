#include "TaskWork.h"
#include <QDebug>

CTaskWork::CTaskWork(int nInterval, QObject *parent) 
    : CTask(nInterval, parent)
{
}

int CTaskWork::onRun()
{
    int nRet = 0;
    qDebug()<<"CTaskWork::onRun()" << QTime::currentTime();
    return nRet;
}
