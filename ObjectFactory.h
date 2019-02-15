#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QDebug>

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
        {
            qCritical() << className << " is QMetaType::UnknownType";
            return nullptr;
        }
        QObject *obj = (QObject*)QMetaType::create(type);
        if(nullptr == obj)
        {
            qCritical() << "QMetaType::create fail: " << type;
            return nullptr;
        }
        //const QMetaObject* metaObj = QMetaType::metaObjectForType(type);
        //QObject *obj = metaObj->newInstance(Q_ARG(QObject*, parent));
        return obj;
    }
};

#endif // OBJECTFACTORY_H
