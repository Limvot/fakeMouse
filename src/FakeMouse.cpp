
#include <FakeMouse.h>

FakeMouse::FakeMouse() {
	display = XOpenDisplay(NULL);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
}

FakeMouse::~FakeMouse() {
	XCloseDisplay(display);
}

void FakeMouse::set(int x, int y) {
	XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
}

void FakeMouse::move(int x, int y) {
	int currX, currY;
	get(currX, currY);
	// std::cout << "x: " << currX << " y: " << currY << std::endl;
	currX += x;
	currY += y;
	XWarpPointer(display, None, root, 0, 0, 0, 0, currX, currY);
}

void FakeMouse::get(int &x, int &y) {
	//int winX, winY;
	unsigned int mask;
	Window junk, child;

	XQueryPointer(display,
					root,
					&junk,
					&child,
					&rootX,
					&rootY,
					&x,
					&y,
					&mask);
}

int FakeMouse::getScreenHeight() {
	return XDisplayHeight(display, 0);
}

int FakeMouse::getScreenWidth() {
	return XDisplayWidth(display, 0);
}

void FakeMouse::lClick() {
	XTestFakeButtonEvent(display, 1, True, CurrentTime);
	XTestFakeButtonEvent(display, 1, False, CurrentTime);
}

void FakeMouse::lPress() {
	XTestFakeButtonEvent(display, 1, True, CurrentTime);
}

void FakeMouse::lRelease() {
	XTestFakeButtonEvent(display, 1, False, CurrentTime);
}

void FakeMouse::rClick() {
	XTestFakeButtonEvent(display, 3, True, CurrentTime);
	XTestFakeButtonEvent(display, 3, False, CurrentTime);
}

void FakeMouse::scrollUp() {
	XTestFakeButtonEvent(display, 4, True, CurrentTime);
	XTestFakeButtonEvent(display, 4, False, CurrentTime);
}

void FakeMouse::scrollDown() {
	XTestFakeButtonEvent(display, 5, True, CurrentTime);
	XTestFakeButtonEvent(display, 5, False, CurrentTime);
}

