#include <InputHandler.h>

InputHandler::InputHandler() {
	lClickDown = false;
}

InputHandler::~InputHandler() {
	//Nothing to delete
}

void InputHandler::onInit(const Leap::Controller& controller) {
	std::cout << "Init" << std::endl;
	screenHeight = mouse.getScreenHeight();
	screenWidth = mouse.getScreenWidth();
}

void InputHandler::onConnect(const Leap::Controller& controller) {
	std::cout << "Controller Connected" << std::endl;
	controller.enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Leap::Gesture::TYPE_CIRCLE);
	controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void InputHandler::onDisconnect(const Leap::Controller& controller) {
	std::cout << "Controller Disconnected" << std::endl;
}

void InputHandler::onFrame(const Leap::Controller& controller) {
	update(controller.frame());
}

void InputHandler::update(Leap::Frame frame) {
	//Do stuff per frame
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
			break;
			case Leap::Gesture::TYPE_CIRCLE:
			{
				Leap::CircleGesture circle = gesture;
				//If clockwise
				if (circle.pointable().direction().angleTo(circle.normal()) <= Leap::PI/4) {
					std::cout << "Circle Gesture clockwise" << std::endl;
					mouse.scrollUp();
				} else {
					std::cout << "Circle Gesture counter-clockwise" << std::endl;
					mouse.scrollDown();	
				}
			}
			break;
			case Leap::Gesture::TYPE_SWIPE:
			{
				std::cout << "Swipe Gesture" << std::endl;
			}
			break;
			default:
				std::cout << "Unsupported gesture type." << std::endl;
		}
	}
	//Testing for click
	Leap::PointableList pointables = frame.pointables();
	Leap::Pointable pointer = pointables.frontmost();
	Leap::FingerList handFingers = frame.hands()[0].fingers();
	if (handFingers.frontmost() == handFingers.leftmost()) {
		if (!lClickDown) {
			//Do press
			std::cout << "lClick down!" << std::endl;
			mouse.lPress();
			lClickDown = true;
		}
	} else {
		if (lClickDown) {
			//stop click
			std::cout << "lClick released." << std::endl;
			mouse.lRelease();
			lClickDown = false;
		}
	}
	//Handle pointing
	Leap::Vector stabilizedPosition = pointer.stabilizedTipPosition();
	Leap::InteractionBox box = frame.interactionBox();
	Leap::Vector normalizedPosition = box.normalizePoint(stabilizedPosition);
	int x = (int) (normalizedPosition.x * screenWidth);
	int y = (int) (screenHeight - normalizedPosition.y * screenHeight);
	mouse.set(x,y);
	mouse.move(0,0);
	
}