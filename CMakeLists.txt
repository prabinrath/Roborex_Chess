cmake_minimum_required(VERSION 2.8.3)
project(chess_bot)
add_definitions(-std=c++11)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
#qt_build 
roscpp
rospy
std_msgs
genmsg
sensor_msgs
cv_bridge
image_transport
)

find_package(OpenCV REQUIRED)

## Declare ROS messages and services
add_message_files(FILES botdata.msg ui_data.msg feature.msg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs sensor_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime)

## System dependencies are found with CMake's conventions
find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

################################################
## Find files 
################################################
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
set(QT_MOC include/Ui_Moc/MainUI.h include/Ui_Moc/InteractUI.h include/Ui_Moc/Menu.h include/Ui_Moc/NewGame.h include/Ui_Moc/LoadDelete.h include/Ui_Moc/About.h include/Ui_Moc/GameTile.h)
SET(QT_SOURCES src/Ui_Source/MainUI.cpp src/Ui_Source/InteractUI.cpp src/Ui_Source/Menu.cpp src/Ui_Source/NewGame.cpp src/Ui_Source/LoadDelete.cpp src/Ui_Source/About.cpp src/Ui_Source/GameTile.cpp)

#set(QT_MOC include/Ui_Moc/GameTabs.h)
#SET(QT_SOURCES src/Ui_Source/GameTabs.cpp)

#TODO:Try to get BoardUI here
################################################
## Setup QT
################################################
QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

###########
## Build ##
###########
include_directories(include)
include_directories(${catkin_INCLUDE_DIRS} ${QT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_library(chess_bot_ui ${QT_SOURCES} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(chess_bot_ui ${QT_LIBRARIES} ${catkin_LIBRARIES})

add_executable(chess_ui src/Ui_Source/main.cpp)
target_link_libraries(chess_ui chess_bot_ui)

add_executable(frame_pub src/Image_processing/frame_pub.cpp)
target_link_libraries(frame_pub ${catkin_LIBRARIES} ${OpenCV_LIBS})
add_dependencies(frame_pub chess_bot_generate_messages_cpp)

add_executable(frame_handler src/Image_processing/frame_handler.cpp)
target_link_libraries(frame_handler ${catkin_LIBRARIES} ${OpenCV_LIBS})
add_dependencies(frame_handler chess_bot_generate_messages_cpp)
