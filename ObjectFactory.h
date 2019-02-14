#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>

class CObjectFactory
{
public:
    CObjectFactory();
    
    template<typename T>
    static int registerClass()
    {
        return qRegisterMetaType<T>();
    }
    
    static QObject* createObject(const QByteArray& className, QObject* parent = NULL)
    {
        int type = QMetaType::type(className);
        if(QMetaType::UnknownType == type)
            return NULL;
        const QMetaObject *metaObj = QMetaType::metaObjectForType(type);
        if(NULL == metaObj)
            return NULL;
        QObject *obj = metaObj->newInstance(Q_ARG(QObject*, parent));
        return obj;
    }
};

#endif // OBJECTFACTORY_H
