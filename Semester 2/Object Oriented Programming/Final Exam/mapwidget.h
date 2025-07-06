#pragma once
#include <QWidget>
#include <QPaintEvent>
#include "parcel.h"
#include <QList>

class MapWidget : public QWidget {
    Q_OBJECT
private:
    QList<Parcel> parcels;
    int selectedIndex;
    void paintEvent(Parcel parcel, int index);

public:
    MapWidget(QWidget* parent = nullptr);
    void setParcels(QList<Parcel> parcels);
    int getSelectedParcelIndex();
    void clearSelection();

signals:
    void parcelSelected(int index);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

};