# Autonomous Chess Bot
An Autonomous chess playing bot that is capable of playing chess game with an user. The project uses ROS framework for the development of the control system. It is equipped with UIs developed with Qt4 that facilates user interaction with system. Stockfish chess engine is used as the intelligence unit of the bot. Python chess API has been used for easy communication with the engine and for increasing the robustness of the software. User physical move inputs are taken from an over head camera and are analysed with computer vision algorithms developed with OpenCV to track on board movements. The output of the system is mapped on the physical chess board via an XY slider that is controlled by an Arduino UNO. The communication between Arduino and the system is established by Serial communication protocol facilated by rosserial library.

Prerequisites:

1.Ubuntu 16.04
2.ROS Kinetic
3.OpenCV 3.2
4.Arduino IDE
5.QT4
6.Python 2.7
	libs:
	a>Python chess API
	b>Stockfish 8

Note:  The Project is still under Development.
