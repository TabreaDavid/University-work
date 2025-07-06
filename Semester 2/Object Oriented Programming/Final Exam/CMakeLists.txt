cmake_minimum_required(VERSION 3.30)

project(sol)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "/Users/m3/Qt/6.9.0/macos")

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(sol
  main.cpp
  agent.cpp
  agentwindow.cpp
  location.cpp
  controller.cpp
  mainwindow.cpp
  parcel.cpp
  repository.cpp
  logisticswindow.cpp
  mapwidget.cpp
  
)

set_property(TARGET sol PROPERTY CMAKE_AUTOUIC OFF)


target_link_libraries(sol
  Qt::Core
  Qt::Gui
  Qt::Widgets
)