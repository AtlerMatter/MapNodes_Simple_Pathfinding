#pragma once
#include<Windows.h>
#include "Point.h"

class Circle {
private:
	int radius;
	Point center;
public:
	Circle ();
	Circle (Point c, int r);
	~Circle ();
	bool Contains (Point p);
	void Draw (HWND wndId, long color);
	void Draw (HWND wndId, long color, char* text, long text_color);
};

