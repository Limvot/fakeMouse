
#include <iostream>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#ifndef FAKE_MOUSE
#define FAKE_MOUSE

class FakeMouse {
public:
	FakeMouse();
	~FakeMouse();
	void set(int x, int y);
	void move(int x, int y);
	void get(int &x, int &y);
	int getScreenHeight();
	int getScreenWidth();
	void lClick();
	void lPress();
	void lRelease();
	void rClick();
private:
	int screen, root, rootX, rootY;
	Display *display;

};

#endif
