#pragma once
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "controller.h"
#include "repository.h"
#include "logisticswindow.h"
#include "agentwindow.h"
#include <QList>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Repository* repository;
    Controller* controller;
    QComboBox* agentsCombo;
    QPushButton* openAgentButton;
    QPushButton* openLogisticsButton;
    LogisticsWindow* logisticsWindow;
    QList<AgentWindow*> agentWindows;
public:
    MainWindow();
    ~MainWindow();
    
private slots:
    void openAgentWindow();
    void openLogisticsWindow();
    
};