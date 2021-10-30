# Roborex_chess
Official repository for Project Autonomous Chess Bot under Cyborg, NITR

## What is it

An Autonomous chess playing bot capable of playing chess with users.

## How it is supported

The project uses：

* ROS as framework to the development of the control system

* Qt4 to facilitate user-system interacion

* Stockfish chess engine as the intelligence unit of the bot

* Python chess API for easier communication with the engine and for increasing software robustness 

* OpenCV to facilitate computer vision algorithms to track board movements while user's physical move inputs are taken from an overhead camera

* Arduino UNO to control an X-Y slider mapping the system output and the physical chess board

* Serial communication protocol (sopported by Pyserial library) for communicating between Arduino and the system

## Prerequisites

* Ubuntu 16.04
* ROS Kinetic
* OpenCV 3.2
* Arduino IDE
* QT4
* Python 2.7 libs (Python chess API & Stockfish 8)
* CMake 2.8.3

# Note
The Project is completed and the code has been archived.
