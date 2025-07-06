#include "agent.h"
#include <QtMath>

Agent::Agent(QString name, Location center, double radius)
    : name(name), serviceAreaCenter(center), serviceAreaRadius(radius) {}

QString Agent::getName()  {
    return name;
}

void Agent::setName(QString name) {
    this->name = name;
}

void Agent::addStreet(QString street) {
    streets.append(street);
}

QList<QString> Agent::getStreets()  {
    return streets;
}

Location Agent::getServiceAreaCenter()  {
    return serviceAreaCenter;
}

double Agent::getServiceAreaRadius()  {
    return serviceAreaRadius;
}

bool Agent::isInServiceArea(Location location)  {
    double dx = location.getX() - serviceAreaCenter.getX();
    double dy = location.getY() - serviceAreaCenter.getY();
    return qSqrt(dx * dx + dy * dy) <= serviceAreaRadius;
}