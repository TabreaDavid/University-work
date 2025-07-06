#pragma once
#include <QString>
#include <QList>
#include "location.h"

class Agent {
private:
    QString name;
    QList<QString> streets;
    Location serviceAreaCenter;
    double serviceAreaRadius;
public:
    Agent(QString name = "", Location center = Location(), double radius = 0);
    QString getName();
    void setName(QString name);
    void addStreet(QString street);
    QList<QString> getStreets();
    Location getServiceAreaCenter();
    double getServiceAreaRadius();
    bool isInServiceArea(Location location);


};