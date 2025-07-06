#pragma once
#include <QString>
#include <QList>
#include "agent.h"
#include "parcel.h"
#include <QObject>

class Repository : public QObject {
    Q_OBJECT
private:
    void loadAgents();
    void loadParcels();
    
    QList<Agent> agents;
    QList<Parcel> parcels;
    QString agentsFile;
    QString parcelsFile;
public:
    Repository();
    ~Repository();
    
    QList<Agent> getAgents();
    QList<Parcel> getParcels();
    void addParcel(Parcel parcel);
    void updateParcel(int index, Parcel parcel);
    void saveData();

signals:
    void dataChanged();

};