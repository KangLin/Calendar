// 作者：康林 <kl222@126.com>

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QObject>
#include <QByteArray>
#include <QMetaObject>
#include <QHash>
#include <QDebug>
#include <QDomElement>
#include <QMetaProperty>
#include <QIcon>
#include <QPixmap>
#include <QBuffer>

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
        Q_UNUSED(parent);
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
        if(!pThis)
            return -1;
        const QMetaObject* pObj = pThis->metaObject();
        if("class" != e.tagName())
        {
            qCritical() << pObj->className() << "::LoadSettings failed: tagName:"
                        << e.tagName() << " name:" << e.attribute("name");
            return -1;
        }
        
        QDomElement de = e.firstChildElement();
        while(!de.isNull())
        {
            QString szName = de.nodeName();
            QVariant value = de.attribute("value");
            if("icon" == szName && value.isValid())
            {
                QPixmap p;
                QByteArray ba = QByteArray::fromBase64(value.toByteArray());
                bool b = p.loadFromData(ba);
                if(b)
                    value = QIcon(p);
            }
            if("backgroundImage" == szName && value.isValid())
            {
                QImage img;
                QByteArray ba = QByteArray::fromBase64(value.toByteArray());
                bool b = img.loadFromData(ba);
                if(b)
                    value = img;
            }
            if(value.isValid())
                pThis->setProperty(szName.toStdString().c_str(), value);
            /*int nIndex = pObj->indexOfProperty(szName.toStdString().c_str());
            QMetaProperty property = pObj->property(nIndex);
            QVariant v(szValue);
            if(!property.write(pThis, szValue))
                qCritical() << "Write property fail: " << pObj->className() << szName;
            */
            de = de.nextSiblingElement();
        }
        return nRet;
    }
    
    static int SaveSettings(QDomElement &e, QObject* pThis)
    {
        int nRet = 0;
        const QMetaObject* pObj = pThis->metaObject();
        QDomDocument doc;

        if(e.isNull())
        {
            qCritical() << "CObjectFactory::SaveSettings e is null";
            return -1;  
        }
        
        int nAttr = pObj->propertyCount();
        for(int i = 0; i < nAttr; i++)
        {
            QMetaProperty p = pObj->property(i);
            if(!(p.isReadable() && p.isWritable()))
                continue;
            QString szName = p.name();
            QVariant value = p.read(pThis);
            if("icon" == szName && !value.isNull())
            {
                QIcon icon = value.value<QIcon>();
                if(0 == icon.availableSizes().length())
                    continue;
                QPixmap p = icon.pixmap(icon.availableSizes().at(0));
                QByteArray ba;
                QBuffer buf(&ba);
                if(buf.open(QIODevice::WriteOnly))
                    p.save(&buf, "PNG");
                if(!ba.isEmpty())
                    value = ba.toBase64();
            }
            if("backgroundImage" == szName && !value.isNull())
            {
                QImage img = value.value<QImage>();
                QByteArray ba;
                QBuffer buf(&ba);
                if(buf.open(QIODevice::WriteOnly))
                    img.save(&buf, "PNG");
                if(!ba.isEmpty())
                    value = ba.toBase64();
            }
            //qDebug() << "property name: " << szName << " value: " << value.toString();
            if(value.isValid())
            {
                
                QDomElement domProperty = doc.createElement(szName);
                if(p.isEnumType())
                {
                    QMetaEnum e = p.enumerator();
                    qDebug() << " name:" << e.name() << " key:" << e.key(value.toInt()) << " index:" << value.toInt();
                    domProperty.setAttribute("value", e.key(value.toInt()));
                } else
                    domProperty.setAttribute("value", value.toString());
                e.appendChild(domProperty);
            }
        } 
        return nRet;
    }
    
};

#endif // OBJECTFACTORY_H
