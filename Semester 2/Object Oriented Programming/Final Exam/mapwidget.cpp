#include "mapwidget.h"
#include <QPainter>
#include <QMouseEvent>

MapWidget::MapWidget(QWidget* parent) : QWidget(parent), selectedIndex(-1) {
    setMinimumSize(400, 300);
}

void MapWidget::setParcels(QList<Parcel> parcels) {
    this->parcels = parcels;
    selectedIndex = -1;
    update();
}

int MapWidget::getSelectedParcelIndex() {
    return selectedIndex;
}

void MapWidget::clearSelection() {
    selectedIndex = -1;
    update();
}

void MapWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    
    for (int i = 0; i < parcels.size(); i++) {
        Parcel parcel = parcels[i];
        int x = 50 + (int)(parcel.getLocation().getX());
        int y = 50 + (int)(parcel.getLocation().getY());
        
        if (parcel.isDelivered()) {
            painter.setBrush(QBrush(Qt::green));
        } else {
            painter.setBrush(QBrush(Qt::red));
        }
        
        if (i == selectedIndex) {
            painter.setPen(QPen(Qt::blue, 1));
        } else {
            painter.setPen(QPen(Qt::black, 1));
        }
        
        painter.drawEllipse(x - 5, y - 5, 10, 10);
        painter.drawText(x + 10, y, parcel.getRecipientName());
    }
}

void MapWidget::mousePressEvent(QMouseEvent* event) {
    for (int i = 0; i < parcels.size(); i++) {
        Parcel parcel = parcels[i];
        int x = 50 + (int)(parcel.getLocation().getX() );
        int y = 50 + (int)(parcel.getLocation().getY());
        
        QRect parcelRect(x - 5, y - 5, 10, 10);
        if (parcelRect.contains(event->pos())) {
            selectedIndex = i;
            emit parcelSelected(i); 
            update();
            return;
        }
    }
    
    selectedIndex = -1;
    update();
}