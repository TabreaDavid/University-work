#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow() {
    repository = new Repository();
    controller = new Controller(repository);
    
    setWindowTitle("ParcelFlow");
    resize(300, 150);
    
    QWidget* centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    
    QLabel* titleLabel = new QLabel("Parcelflow");
    layout->addWidget(titleLabel);
    
    agentsCombo = new QComboBox();
    layout->addWidget(agentsCombo);
    
    QList<Agent> agents = controller->getAllAgents();
    for (Agent agent : agents) {
        agentsCombo->addItem(agent.getName());
    }
    
    openAgentButton = new QPushButton("Open agent window");
    layout->addWidget(openAgentButton);
    
    openLogisticsButton = new QPushButton("Open dashboard ");
    layout->addWidget(openLogisticsButton);
    
    connect(openAgentButton, &QPushButton::clicked, this, &MainWindow::openAgentWindow);
    connect(openLogisticsButton, &QPushButton::clicked, this, &MainWindow::openLogisticsWindow);
    
    logisticsWindow = nullptr;
}

MainWindow::~MainWindow() {
    for (AgentWindow* window : agentWindows) {
        if (window) {
            window->close();
            delete window;
        }
    }
    
    if (logisticsWindow) {
        logisticsWindow->close();
        delete logisticsWindow;
    }
    
    delete controller;
    delete repository;
}

void MainWindow::openAgentWindow() {
    int index = agentsCombo->currentIndex();
    if (index >= 0) {
        QList<Agent> agents = controller->getAllAgents();
        if (index < agents.size()) {
            Agent agent = agents[index];
            AgentWindow* agentWindow = new AgentWindow(agent, controller);
            agentWindows.append(agentWindow);
            agentWindow->show();
        }
    }
}

void MainWindow::openLogisticsWindow() {
    if (!logisticsWindow) {
        logisticsWindow = new LogisticsWindow(controller);
    }
    logisticsWindow->show();
    logisticsWindow->raise();
}