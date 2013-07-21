#include <FakeMouse.h>

#include <iostream>
//#include <istream>
#include <string>

int main() {
	FakeMouse mouse;
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
	return 0;
}