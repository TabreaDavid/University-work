#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include "agent.h"
#include "controller.h"
#include "mapwidget.h"

class AgentWindow : public QWidget {
    Q_OBJECT
private:
    Agent agent;
    Controller* controller;
    QList<Parcel> parcels;
    QLabel* titleLabel;
    QListWidget* parcelsList;
    MapWidget* mapWidget;
    QPushButton* deliverButton;
    
    int getOriginalParcelIndex(int localIndex);
public:
    AgentWindow(Agent agent, Controller* controller, QWidget* parent = nullptr);

private slots:
    void updateParcels();
    void deliverParcel();
    void parcelSelected(int index);

};