
#ifndef OCAPSULEDATA_MODEL_H
#define OCAPSULEDATA_MODEL_H

#include <QPointer>
#include <QAbstractListModel>
#include "OcapsuleData.h"

//
//% 
//    
//%% OcapsuleDataModel class is a container class (QList) holding
//%% each OcapsuleData class. We make it a singleton holding
//%% Objects of OcapsuleData such that each OcapsuleData Object
//%% Stays alive always through the static nature of this class.
//%% This Class provides all the methods for a QList custom Object.
//



class OcapsuleDataModel : public QAbstractListModel
{

    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

    OcapsuleDataModel(QObject *parent = 0) : QAbstractListModel(parent), _selectedOcapsuleId(-1)
    {
        setRoleNames(OcapsuleData::roleNames());
    }

public:

    //
    //%  Create Singleton as it last throughout App life
    //
    static OcapsuleDataModel&   Instance();
    static QPointer<OcapsuleDataModel>   getInstancePtr();

    void addOcapsuleData(const OcapsuleData &ocapsuleData)
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        _OcapsuleDataList << ocapsuleData;
        endInsertRows();
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return _OcapsuleDataList.count();
    }

    Q_INVOKABLE int washerCount()
    {
        return _OcapsuleDataList.count();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        QVariant returnValue;
        if(index.row() >= 0 && index.row() < _OcapsuleDataList.count())
        {
        	OcapsuleData model = _OcapsuleDataList[index.row()];
            returnValue = model.data(role);
        }

        return returnValue;
    }

    int currentIndex() const
    {
        int currentIndex = 0;
        for(int i = 0; i < _OcapsuleDataList.size(); ++i)
        {
            if(_OcapsuleDataList.at(i).getOcapsuleId() == _selectedOcapsuleId)
            {
                currentIndex = i;
                break;
            }
        }

        return currentIndex;
    }

    void setCurrentIndex(int index)
    {
        int ocapsuleId = _OcapsuleDataList.at(index).getOcapsuleId();

        if(_selectedOcapsuleId != ocapsuleId)
        {
            qDebug() << "OcapsuleDataModel:setCurrentIndex="<<index;
            _selectedOcapsuleId = ocapsuleId;
            emit currentDatabaseIdChanged(_selectedOcapsuleId);
            emit currentIndexChanged();
        }
    }

    int ocapsuleId() const { return _selectedOcapsuleId; }

    void setDatabaseId(int ocapsuleId)
    {
        if(_selectedOcapsuleId != ocapsuleId)
        {
            _selectedOcapsuleId = ocapsuleId;

            emit currentDatabaseIdChanged(_selectedOcapsuleId);
            emit currentIndexChanged();
        }
    }

    void reset()
    {
        beginResetModel();

        _OcapsuleDataList.clear();
        _selectedOcapsuleId= -1;

        endResetModel();
    }

    Q_INVOKABLE QVariant getDataValue(int index, const QString &role)
    {
        QVariant data;

        if(index >= 0 && index < _OcapsuleDataList.count())
        {
        	OcapsuleData ocapsuleData = _OcapsuleDataList[index];
            QHash<int, QByteArray> rolenames = roleNames();
            int roleId = (int) rolenames.key(role.toAscii());
            data = ocapsuleData.data(roleId);
        }

        return data;
    }
    //% Do Ocapsules have formula?( product no?) will find out!!
    Q_INVOKABLE QVariant setActiveFormula(int ocapsuleId, int formulaNo)
    {
        QVariant data;

        for(int i=0; i< _OcapsuleDataList.count() ; i++)
        {
            if(ocapsuleId== _OcapsuleDataList[i].getOcapsuleId())
            {
            	 _OcapsuleDataList[i].setActiveFormulaNo(formulaNo);
            	break;
            }
        }
    	return data;
    }

signals:
            void currentIndexChanged();
            void currentDatabaseIdChanged(int );

private:
    QList<OcapsuleData> _OcapsuleDataList;     //% List Of Ocapsules.
    int _selectedOcapsuleId;        //% ID of the given Ocapsule(O1,O2).

};

#endif // #ifndef OCAPSULEDATAMODEL_H
