#include "logisticswindow.h"
#include <QHeaderView>
#include <QMessageBox>

LogisticsWindow::LogisticsWindow(Controller* controller, QWidget* parent)
    : QWidget(parent), controller(controller) {
    
    setWindowTitle("Logistics dashboard");
    resize(800, 600);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("All parcels");
    mainLayout->addWidget(titleLabel);
    
    parcelsTable = new QTableWidget();
    parcelsTable->setColumnCount(5);
    parcelsTable->setHorizontalHeaderLabels({"Recipient", "Street", "Number", "Status", "Coordinates"});
    parcelsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(parcelsTable);
    
    mapWidget = new MapWidget();
    mainLayout->addWidget(mapWidget);
    
    deliverButton = new QPushButton("Deliver");
    deliverButton->setEnabled(false);
    mainLayout->addWidget(deliverButton);
    
    QHBoxLayout* addLayout = new QHBoxLayout();
    mainLayout->addLayout(addLayout);
    
    recipientNameEdit = new QLineEdit();
    recipientNameEdit->setPlaceholderText("Recipient name");
    addLayout->addWidget(recipientNameEdit);
    
    streetEdit = new QLineEdit();
    streetEdit->setPlaceholderText("Street");
    addLayout->addWidget(streetEdit);
    
    numberEdit = new QLineEdit();
    numberEdit->setPlaceholderText("Number");
    addLayout->addWidget(numberEdit);

    xCoordSpin = new QDoubleSpinBox();
    xCoordSpin->setMinimum(-1000.0);
    xCoordSpin->setMaximum(1000.0);
    xCoordSpin->setDecimals(2);
    addLayout->addWidget(xCoordSpin);

    yCoordSpin = new QDoubleSpinBox();
    yCoordSpin->setMinimum(-1000.0);
    yCoordSpin->setMaximum(1000.0);
    yCoordSpin->setDecimals(2);
    addLayout->addWidget(yCoordSpin);
    
    addButton = new QPushButton("Add parcel");
    addLayout->addWidget(addButton);
    
    connect(controller, &Controller::dataChanged, this, &LogisticsWindow::updateParcels);
    connect(addButton, &QPushButton::clicked, this, &LogisticsWindow::addNewParcel);
    connect(deliverButton, &QPushButton::clicked, this, &LogisticsWindow::deliverParcel);
    connect(mapWidget, &MapWidget::parcelSelected, [this](int index) {
        deliverButton->setEnabled(index >= 0);
    });
    
    updateParcels();
}

void LogisticsWindow::updateParcels() {
    QList<Parcel> parcels = controller->getAllParcels();
    
    parcelsTable->setRowCount(parcels.size());
    
    for (int i = 0; i < parcels.size(); i++) {
        Parcel parcel = parcels[i];
        parcelsTable->setItem(i, 0, new QTableWidgetItem(parcel.getRecipientName()));
        parcelsTable->setItem(i, 1, new QTableWidgetItem(parcel.getStreet()));
        parcelsTable->setItem(i, 2, new QTableWidgetItem(parcel.getNumber()));
        parcelsTable->setItem(i, 3, new QTableWidgetItem(parcel.isDelivered() ? "Delivered" : "Not delivered"));
        parcelsTable->setItem(i, 4, new QTableWidgetItem(
        QString("(%1, %2)").arg(parcel.getLocation().getX()).arg(parcel.getLocation().getY())));
        
        if (parcel.isDelivered()) {
            for (int j = 0; j < parcelsTable->columnCount(); j++) {
                if (parcelsTable->item(i, j)) {
                    parcelsTable->item(i, j)->setBackground(QBrush(Qt::green));
                }
            }
        }
    }
    
    mapWidget->setParcels(parcels);
    deliverButton->setEnabled(false);
}

void LogisticsWindow::addNewParcel() {
    QString recipientName = recipientNameEdit->text();
    QString street = streetEdit->text();
    QString number = numberEdit->text();
    double x = xCoordSpin->value();
    double y = yCoordSpin->value();

    if (recipientName.isEmpty() || street.isEmpty() || number.isEmpty()) {
        QMessageBox::warning(this, "Invalid input", " Fill all fields");
        return;
    }

    controller->addNewParcel(recipientName, street, number, x, y);

    recipientNameEdit->clear();
    streetEdit->clear();
    numberEdit->clear();
    xCoordSpin->setValue(0.0);
    yCoordSpin->setValue(0.0);
}

void LogisticsWindow::deliverParcel() {
    int index = mapWidget->getSelectedParcelIndex();
    if (index >= 0) {
        controller->deliverParcel(index);
    }
}