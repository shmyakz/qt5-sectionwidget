cmake_minimum_required(VERSION 3.28)
project(SectionWidget)

set(TARGET ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${TARGET} main.cpp
	src/application.cpp
	src/application.h
	src/gui/mainwindow.cpp
	src/gui/mainwindow.h
	src/gui/sectionwidget.cpp
	src/gui/sectionwidget.h)

target_link_libraries(${TARGET}
	Qt::Core
	Qt::Gui
	Qt::Widgets
)
