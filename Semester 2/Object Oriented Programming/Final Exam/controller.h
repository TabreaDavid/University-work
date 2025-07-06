#pragma once
#include "repository.h"
#include <QObject>
#include <QList>

class Controller : public QObject {
    Q_OBJECT
private:
    Repository* repository;
public:
    Controller(Repository* repository);
    
    QList<Agent> getAllAgents();
    QList<Parcel> getAllParcels();
    QList<Parcel> getUndeliveredParcels();
    QList<Parcel> getParcelsForAgent(Agent agent);
    bool deliverParcel(int parcelIndex);
    void addNewParcel(QString recipientName, QString street, QString number, 
                     double x, double y);

signals:
    void dataChanged();

};