#include "parcel.h"

Parcel::Parcel(QString recipientName, QString street, QString number, 
               Location location, bool delivered)
    : recipientName(recipientName), street(street), number(number), 
      location(location), delivered(delivered) {}

QString Parcel::getRecipientName() {
    return recipientName;
}

QString Parcel::getStreet() {
    return street;
}

QString Parcel::getNumber() {
    return number;
}

Location Parcel::getLocation() {
    return location;
}

bool Parcel::isDelivered() {
    return delivered;
}

void Parcel::setDelivered(bool delivered) {
    this->delivered = delivered;
}