#ifndef CGLOBALDIR_H
#define CGLOBALDIR_H

#include <QString>
#include "tasks_export.h"

class TASKS_EXPORT CGlobalDir
{
public:
    CGlobalDir();
    
    static CGlobalDir* Instance();
     
    QString GetDirApplication();

    QString GetDirConfig();
    QString GetDirApplicationXml();
    QString GetDirDocument();
    int SetDirDocument(QString szPath);
    
    QString GetDirData();
    QString GetDirImage();
    
    QString GetDirTranslate();

    QString GetApplicationConfigureFile();
    
    QString GetUserConfigureFile();
   
private:
    QString m_szDocumentPath;
};

#endif // CGLOBALDIR_H
