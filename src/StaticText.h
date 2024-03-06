#pragma once
#include<Windows.h>
#include"Point.h"

class StaticText {
private:
	char* sText;
public:
	StaticText (const char* text);
	~StaticText ();
	void Draw (HWND wndId, Point pos, long color);
};

