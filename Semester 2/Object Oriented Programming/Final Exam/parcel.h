#pragma once
#include <QString>
#include "location.h"

class Parcel {
private:
    QString recipientName;
    QString street;
    QString number;
    Location location;
    bool delivered;
public:
    Parcel(QString recipientName = "", QString street = "", QString number = "", 
           Location location = Location(), bool delivered = false);
    QString getRecipientName();
    QString getStreet();
    QString getNumber();
    Location getLocation();
    bool isDelivered();
    void setDelivered(bool delivered);
    

};