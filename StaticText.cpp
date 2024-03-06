#include "StaticText.h"

StaticText::StaticText (const char* text) {
	int len = strlen (text);
	sText = new char[len + 1];
	strcpy_s (sText, len + 1, text);
}

StaticText::~StaticText () {
	delete[] sText;
}

void StaticText::Draw (HWND wndId, Point pos, long color) {
	HDC drawDC = GetDC (wndId);
	SetBkMode (drawDC, TRANSPARENT);
	SetTextColor (drawDC, color);
	SetTextAlign (drawDC, TA_LEFT | TA_BASELINE);
	TextOut (drawDC, pos.GetX (), pos.GetY (), sText, strlen (sText));
}
