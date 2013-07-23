#include <FakeMouse.h>

#include <iostream>
//#include <istream>
#include <string>

#include "Leap.h"

#include <time.h>


class InputHandler : public Leap::Listener {
	public:
		InputHandler();
		~InputHandler();
		void onInit(const Leap::Controller& controller);
		void onConnect(const Leap::Controller& controller);
		void onDisconnect(const Leap::Controller& controller);
		void onFrame(const Leap::Controller& controller);
		void update(Leap::Frame frame);
	private:
		FakeMouse mouse;
		int screenWidth, screenHeight;
};
