#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "FrmEyeNurse.h"
#include "ObjectFactory.h"
#include <QDebug>

extern int gTypeIdCTask;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
    qDebug() << "Language: " << QLocale::system().name();
    QTranslator t;
    t.load(":/Translations/app_" + QLocale::system().name());
    a.installTranslator(&t);
  
    /*CFrmUpdater u;
    u.show();
    u.StartDownload("https://github.com/qTox/qTox/blob/master/updater/update.cpp");//*/
    /*MainWindow w;
    w.show();*/
    
    CFrmEyeNurse en;

    qDebug() << "TypeIdCTask: " << gTypeIdCTask;
    
    CTask* p = (CTask*) CObjectFactory::createObject("CTask");
    if(p)
        qDebug() << "p is not null";
    else
        qDebug() << "p is null";
    return a.exec();
}
