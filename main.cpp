#include <FakeMouse.h>

#include <iostream>
//#include <istream>
#include <string>

#include "Leap.h"

#include <time.h>

int main() {
	FakeMouse mouse;

	Leap::Controller controller;

	int screenHeight = mouse.getScreenHeight();
	int screenWidth = mouse.getScreenWidth();

	while (true) {
		bool newConnection = true;
		while (controller.isConnected()) {
			if (newConnection) {
				std::cout << "Controller is connected!" << std::endl;
				controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
				newConnection = false;
			}
			Leap::Frame frame = controller.frame();
			std::cout 	<< "Frame id: " << frame.id()
						<< ", timestamp: " << frame.timestamp()
						<< ", hands: " << frame.hands().count()
						<< ", fingers: " << frame.fingers().count()
						<< ", tools: " << frame.tools().count() << std::endl;

			Leap::GestureList gestures = frame.gestures();
			for (int i = 0; i < gestures.count(); i++) {
				Leap::Gesture gesture = gestures[i];
				switch (gesture.type()) {
					case Leap::Gesture::TYPE_SCREEN_TAP:
					{
						Leap::ScreenTapGesture screentap = gesture;
						std::cout	<< "Screen Tap id: " << gesture.id()
									<< ", state: " << gesture.state()
									<< ", position: " << screentap.position()
									<< ", direction: " << screentap.direction() << std::endl;
						mouse.lClick();
					}
					break;

					case Leap::Gesture::TYPE_KEY_TAP:
					{
						Leap::KeyTapGesture keytap = gesture;
						std::cout	<< "Key Tap id: " << gesture.id()
									<< ", state: " << gesture.state()
									<< ", position: " << keytap.position()
									<< ", direction: " << keytap.direction() << std::endl;
						mouse.rClick();
					}
					default:
						std::cout << "Unsupported gesture type." << std::endl;
				}
			}


			//Leap::HandList hands = frame.hands();
			Leap::PointableList pointables = frame.pointables();
			//Leap::FingerList fingers = frame.fingers();
			//Leap::ToolList tools = frame.tools();

			Leap::Pointable pointer = pointables.frontmost();
			Leap::Vector stabilizedPosition = pointer.stabilizedTipPosition();

			Leap::InteractionBox box = frame.interactionBox();
			Leap::Vector normalizedPosition = box.normalizePoint(stabilizedPosition);

			int x = (int) (normalizedPosition.x * screenWidth);
			int y = (int) (screenHeight - normalizedPosition.y * screenHeight);
			mouse.set(x,y);
		}
		timespec sleepTime;
		sleepTime.tv_sec = 1;
		sleepTime.tv_nsec = 0;
		nanosleep(&sleepTime, &sleepTime);
		std::cout << "Controller is not connected." << std::endl;
	}

/*
	std::string input = "";
	while (input != "quit") {
		std::cin >> input;

		if (input == "up") {
			mouse.move(0, -100);
			//Make sure event goes through
			mouse.move(0,0);
		}
		else if (input == "down") {
			mouse.move(0, 100);
			//Make sure event godowes through
			mouse.move(0,0);
		}
		else if (input == "left") {
			mouse.move(-100, 0);
			//Make sure event goes through
			mouse.move(0,0);
		}
		else if (input == "right") {
			mouse.move(100, 0);
			//Make sure event goes through
			mouse.move(0,0);
		}
		else if (input == "lclick") {
			mouse.lClick();
			//Make sure event goes through
			mouse.move(0,0);
		}
		else if (input == "rclick"){
			mouse.rClick();
			//Make sure event goes through
			mouse.move(0,0);
		}
		else if (input == "show"){
			for (int i = 0; i < 100000; i++) {
				int x,y;
				mouse.get(x,y);
				std::cout << "x: " << x << " y: " << y << std::endl;
			}
		}
		else
			std::cout << "No input" << std::endl;
	}
	*/
	return 0;
}

