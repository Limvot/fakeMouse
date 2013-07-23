#//include <FakeMouse.h>
#include <InputHandler.h>
#include <iostream>
#include <string>

#include "Leap.h"

#include <time.h>

int main() {
	InputHandler inputHandler;
	Leap::Controller controller;
	controller.addListener(inputHandler);

	std::cout << "Press Enter to quit" << std::endl;
	std::cin.get();

	controller.removeListener(inputHandler);

	return 0;
}

