#include "agentwindow.h"
#include <QMessageBox>

AgentWindow::AgentWindow(Agent agent, Controller* controller, QWidget* parent)
    : QWidget(parent), agent(agent), controller(controller) {
    
    setWindowTitle(agent.getName());
    resize(600, 400);
    
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    titleLabel = new QLabel("Parcels for " + agent.getName());
    layout->addWidget(titleLabel);
    
    parcelsList = new QListWidget();
    layout->addWidget(parcelsList);
    
    mapWidget = new MapWidget();
    layout->addWidget(mapWidget);
    
    deliverButton = new QPushButton("Delivered");
    deliverButton->setEnabled(false);
    layout->addWidget(deliverButton);
    
    connect(controller, &Controller::dataChanged, this, &AgentWindow::updateParcels);
    connect(deliverButton, &QPushButton::clicked, this, &AgentWindow::deliverParcel);
    connect(mapWidget, &MapWidget::parcelSelected, this, &AgentWindow::parcelSelected);
    
    updateParcels();
}

void AgentWindow::updateParcels() {
    parcels = controller->getParcelsForAgent(agent);
    parcelsList->clear();
    
    for (Parcel parcel : parcels) {
        QString item = parcel.getRecipientName() + " - " + 
                       parcel.getStreet() + " " + parcel.getNumber();
        parcelsList->addItem(item);
    }
    
    mapWidget->setParcels(parcels);
    deliverButton->setEnabled(false);
}

void AgentWindow::deliverParcel() {
    int mapIndex = mapWidget->getSelectedParcelIndex();
    if (mapIndex >= 0) {
        int originalIndex = getOriginalParcelIndex(mapIndex);
        if (originalIndex >= 0) {
            controller->deliverParcel(originalIndex);
        }
    }
}

void AgentWindow::parcelSelected(int index) {
    deliverButton->setEnabled(index >= 0);
    parcelsList->setCurrentRow(index);
}

int AgentWindow::getOriginalParcelIndex(int localIndex) {
    if (localIndex < 0 || localIndex >= parcels.size())
        return -1;
        
    Parcel selectedParcel = parcels[localIndex];
    QList<Parcel> allParcels = controller->getAllParcels();
    
    for (int i = 0; i < allParcels.size(); i++) {
        Parcel parcel = allParcels[i];
        if (parcel.getRecipientName() == selectedParcel.getRecipientName() && 
            parcel.getStreet() == selectedParcel.getStreet() &&
            parcel.getNumber() == selectedParcel.getNumber() &&
            !parcel.isDelivered()) {
            return i;
        }
    }
    
    return -1;
}