/*  
 PrimaryScheduleDataModel is a simple Custom Data Model(container) like
 ListModel with all the Methods 
 on How use the Data Model
 */


#ifndef PRIMARY_SCHEDULE_DATA_MODEL_H
#define PRIMARY_SCHEDULE_DATA_MODEL_H

#include <QPointer>
#include <QAbstractListModel>
#include "PrimaryScheduleData.h"

class PrimaryScheduleDataModel : public QAbstractListModel
{

    Q_OBJECT

    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

   // Model Constructor & Initialisation!!
    PrimaryScheduleDataModel(QObject *parent = 0) : QAbstractListModel(parent), _selectedPrimaryScheduleId(-1)
    {
    	//SetRoleNames according to PrimaryScheduleData Class
        setRoleNames(PrimaryScheduleData::roleNames());
    }

public:

	//==========================================================================
    //  PrimaryScheduleDataModel Singleton construction
    //==========================================================================
    static PrimaryScheduleDataModel&   Instance();
    static QPointer<PrimaryScheduleDataModel>   getInstancePtr();

    //% How to Add PrimaryData into the Model
    void addPrimaryScheduleData ( const PrimaryScheduleData & pSData )
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        _PrimaryScheduleDataList << pSData;
        endInsertRows();
    }

    
    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        Q_UNUSED(parent);
        return _PrimaryScheduleDataList.count();
    }
    //% Number of PrimarySchdeuleData objects in Model
    //% Invokable from UI
    Q_INVOKABLE int primaryScheduleDataModelCount()
    {
        return _MachineDataList.count();
    }

    //% Grab Data of PrimaryScheduleData in a given Model using index and Role as Int?
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        QVariant returnValue = 0;
        if(index.row() >= 0 && index.row() < _PrimaryScheduleDataList.count())
        {
        	PrimaryScheduleData psData = _PrimaryScheduleDataList[index.row()];
            returnValue = psData.data(role);
        }

        return returnValue;
    }

    //% Whats the currentIndex in The Model?
    int currentIndex() const
    {
        int currentIndex = 0;
        for(int i = 0; i < _PrimaryScheduleDataList.size(); ++i)
        {
            if(_PrimaryScheduleDataList.at(i).getPrimaryScheduleId() == _selectedPrimaryScheduleId)
            {
                currentIndex = i;
                break;
            }
        }

        return currentIndex;
    }

    // Set an index as the current index in the Model
    void setCurrentIndex(int index)
    {
        int primaryScheduleId = _PrimaryScheduleDataList.at(index).getPrimaryScheduleId();

        if(_selectedPrimaryScheduleId != primaryScheduleId)
        {
            qDebug() << "PrimaryScheduleDataModel:setCurrentIndex="<<index;
            _selectedPrimaryScheduleId = primaryScheduleId;
            emit currentPrimaryScheduleIdChanged(_selectedPrimaryScheduleId);
            emit currentIndexChanged();
        }
    }

    //% Whats the Id of the a given Schedule Initialised
    int primaryScheduleId() const { return  _selectedPrimaryScheduleId; }

    //% Reset the Model
    void reset()
    {
        beginResetModel();

        _PrimaryScheduleDataList.clear();
        _selectedPrimaryScheduleId  = -1;

        endResetModel();
    }

    //% How to get a Particular Data value from the model from UI given the role name
    Q_INVOKABLE QVariant getDataValue(int index, const QString &role)
    {
        QVariant data  = 0;

        if(index >= 0 && index < _PrimaryScheduleDataList.count())
        {
        	PrimaryScheduleData psData = _PrimaryScheduleDataList[index];
            QHash<int, QByteArray> rolenames = roleNames();
            int roleId = (int) rolenames.key(role.toAscii());
            data = psData.data(roleId);
        }

        return data;
    }

    //% Set a particular PrimaryScheduleData as valid or not in the Model from UI
    Q_INVOKABLE QVariant setPrimaryScheduleDataIsValid(int pSscheduleId , bool psIsValid)
    {

        for(int i=0; i < _PrimaryScheduleDataList.count() ; i++)
        {
            if(pSscheduleId == _PrimaryScheduleDataList[i].getPrimaryScheduleId())
            {
            	_PrimaryScheduleDataList[i].setIsValidPrimarySchedule(psIsValid);
            	break;
            }
        }
    }




signals:

    void currentIndexChanged();
    void currentPrimaryScheduleIdChanged(int );




private:
	//Example of a List
    QList<PrimaryScheduleData> _PrimaryScheduleDataList;    //% The list of PrimaryShcedule items in the model.
    int  _selectedPrimaryScheduleId;        


};

#endif //PRIMARY_SCHEDULE_DATA_MODEL_H   