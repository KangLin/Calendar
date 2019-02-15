#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QDebug>
#include <QDomElement>
#include <QMetaProperty>

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

    static int LoadSettings(const QDomElement &e, QObject* pThis)
    {
        int nRet = 0;
        if(e.isNull())
        {
            qCritical() << "CTask::LoadSettings e is null";
            return -1;
        }
        if(!e.hasAttributes())
        {
            qCritical() << "CTask::LoadSettings has not attributes";
            return -2;
        }
        const QMetaObject* pObj = pThis->metaObject();
        
        int nAttr = e.attributes().length();
        for(int i = 0; i < nAttr; i++)
        {
            QString szName = e.attributes().item(i).nodeName();
            QString szValue = e.attributes().item(i).nodeValue();
            int nIndex = pObj->indexOfProperty(szName.toStdString().c_str());
            QMetaProperty property = pObj->property(nIndex);
            if(!property.write(pThis, szValue))
                qCritical() << "Write propery fail: " << pObj->className() << szName;
        }
        return nRet;
    }
    
    static int SaveSettings(const QDomElement &e, QObject* pThis)
    {
        int nRet = 0;
        
        return nRet;
    }
    
};

#endif // OBJECTFACTORY_H
