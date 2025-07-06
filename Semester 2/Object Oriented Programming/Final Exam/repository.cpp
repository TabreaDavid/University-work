#include "repository.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

Repository::Repository() {
    agentsFile = "../data/agents.txt";
    parcelsFile = "../data/parcels.txt";
    loadAgents();
    loadParcels();
}

Repository::~Repository() {
    saveData();
}

QList<Agent> Repository::getAgents() {
    return agents;
}

QList<Parcel> Repository::getParcels() {
    return parcels;
}

void Repository::addParcel(Parcel parcel) {
    parcels.append(parcel);
    emit dataChanged();
}

void Repository::updateParcel(int index, Parcel parcel) {
    if (index >= 0 && index < parcels.size()) {
        parcels[index] = parcel;
        emit dataChanged();
    }
}

void Repository::loadAgents() {
    QFile file(agentsFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        
        if (parts.size() >= 4) {
            QString name = parts[0];
            double centerX = parts[1].toDouble();
            double centerY = parts[2].toDouble();
            double radius = parts[3].toDouble();
            
            Agent agent(name, Location(centerX, centerY), radius);
            
            for (int i = 4; i < parts.size(); i++) {
                agent.addStreet(parts[i]);
            }
            
            agents.append(agent);
        }
    }
    
    file.close();
}

void Repository::loadParcels() {
    QFile file(parcelsFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        
        if (parts.size() >= 6) {
            QString recipientName = parts[0];
            QString street = parts[1];
            QString number = parts[2];
            double locationX = parts[3].toDouble();
            double locationY = parts[4].toDouble();
            bool delivered = parts[5] == "true";
            
            parcels.append(Parcel(recipientName, street, number, 
                                  Location(locationX, locationY), delivered));
        }
    }
    
    file.close();
}

void Repository::saveData() {
    QFile file(parcelsFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (Parcel parcel : parcels) {
        out << parcel.getRecipientName() << "|" << parcel.getStreet() << "|" 
            << parcel.getNumber() << "|"
            << parcel.getLocation().getX() << "|" << parcel.getLocation().getY() << "|" << (parcel.isDelivered() ? "true" : "false") << "\n";
    }
    
    file.close();
}