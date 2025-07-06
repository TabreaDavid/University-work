#include "controller.h"

Controller::Controller(Repository* repository) : repository(repository) {
    connect(repository, &Repository::dataChanged, this, &Controller::dataChanged);
}

QList<Agent> Controller::getAllAgents() {
    return repository->getAgents();
}

QList<Parcel> Controller::getAllParcels() {
    return repository->getParcels();
}

QList<Parcel> Controller::getUndeliveredParcels() {
    QList<Parcel> undelivered;
    for (Parcel parcel : repository->getParcels()) {
        if (!parcel.isDelivered()) {
            undelivered.append(parcel);
        }
    }
    return undelivered;
}

QList<Parcel> Controller::getParcelsForAgent(Agent agent) {
    QList<Parcel> agentParcels;
    for (Parcel parcel : repository->getParcels()) {
        if (!parcel.isDelivered()) {
            if (agent.getStreets().contains(parcel.getStreet()) || 
                agent.isInServiceArea(parcel.getLocation())) {
                agentParcels.append(parcel);
            }
        }
    }
    return agentParcels;
}

bool Controller::deliverParcel(int parcelIndex) {
    QList<Parcel> parcels = repository->getParcels();
    if (parcelIndex >= 0 && parcelIndex < parcels.size()) {
        Parcel parcel = parcels[parcelIndex];
        parcel.setDelivered(true);
        repository->updateParcel(parcelIndex, parcel);
        return true;
    }
    return false;
}

void Controller::addNewParcel(QString recipientName, QString street, 
                            QString number, double x, double y) {
    Parcel parcel(recipientName, street, number, Location(x, y), false);
    repository->addParcel(parcel);
}