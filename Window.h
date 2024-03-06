#pragma once
#include<Windows.h>
#include"Point.h"


class Window {
private:
    HWND windowId;
    Point cur_coord;
    bool bClick;
	bool bEnter;
    
	static Window * object;
	static Window * GetObject();
public:
	Window();
	~Window() { };
	bool Create(const char* sTitle);
	bool Create (char* sTitle, char* sImageName);
	static LRESULT CALLBACK WindowProc(HWND wndId, unsigned int msg, WPARAM wp, LPARAM lp);

	void Clean ();
	HWND GetWindowId() { return windowId; }
	bool HasClicked() { return bClick; }
	Point GetPoint() { return cur_coord; }
	Point GetBottomRight ();
	void ResetEnterKey () { GetObject ()->bEnter = false; }
	bool HasPressEnter () { return bEnter; }
};
