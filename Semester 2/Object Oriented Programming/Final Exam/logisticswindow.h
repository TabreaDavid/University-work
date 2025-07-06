#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include "controller.h"
#include "mapwidget.h"

class LogisticsWindow : public QWidget {
    Q_OBJECT
public:
    LogisticsWindow(Controller* controller, QWidget* parent = nullptr);

private slots:
    void updateParcels();
    void addNewParcel();
    void deliverParcel();

private:
    Controller* controller;
    QTableWidget* parcelsTable;
    MapWidget* mapWidget;
    QPushButton* deliverButton;
    QLineEdit* recipientNameEdit;
    QLineEdit* streetEdit;
    QLineEdit* numberEdit;
    QDoubleSpinBox* xCoordSpin;
    QDoubleSpinBox* yCoordSpin;
    QPushButton* addButton;
};