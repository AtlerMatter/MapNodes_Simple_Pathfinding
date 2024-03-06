#include "Circle.h"
#include <math.h>
#include <stdio.h>

Circle::Circle () {
	this->center = Point(0, 0);
	this->radius = 1;
}

Circle::Circle (Point centro, int raio) {
	this->center = centro;
	this->radius = raio;
}

Circle::~Circle () { }

void Circle::Draw (HWND wndId, long color) {
	if (wndId != NULL) {
        HDC DrawHDC = GetDC (wndId);
        // penstyle, width, color 
        HPEN   hNPen = CreatePen (PS_SOLID, 2, color);
        HPEN   hOPen = (HPEN)SelectObject (DrawHDC, hNPen);
        HBRUSH hOldBrush;
        HBRUSH hNewBrush;
        hNewBrush = CreateSolidBrush (color);
        hOldBrush = (HBRUSH)SelectObject (DrawHDC, hNewBrush);
        Ellipse (DrawHDC, center.GetX () - radius, center.GetY () + radius,
            center.GetX () + radius, center.GetY () - radius);
        DeleteObject (SelectObject (DrawHDC, hOPen));
        DeleteObject (SelectObject (DrawHDC, hOldBrush));
        ReleaseDC (wndId, DrawHDC);
	}
}

void Circle::Draw (HWND wndId, long color, char* text, long text_color) {
    if (wndId != NULL) {
        HDC DrawHDC = GetDC (wndId);
        // penstyle, width, color 
        HPEN hNPen = CreatePen (PS_SOLID, 2, color);
        HPEN hOPen = (HPEN)SelectObject (DrawHDC, hNPen);
        HBRUSH hOldBrush;
        HBRUSH hNewBrush;
        hNewBrush = CreateSolidBrush (color);
        hOldBrush = (HBRUSH)SelectObject (DrawHDC, hNewBrush);
        Ellipse (DrawHDC, center.GetX () - radius, center.GetY () + radius,
            center.GetX () + radius, center.GetY () - radius);
        SetBkMode (DrawHDC, TRANSPARENT);
        SetTextColor (DrawHDC, text_color);
        SetTextAlign (DrawHDC, TA_CENTER | TA_BASELINE);
        TextOut (DrawHDC, center.GetX (), center.GetY () + 3, text, strlen (text));
        DeleteObject (SelectObject (DrawHDC, hOPen));
        DeleteObject (SelectObject (DrawHDC, hOldBrush));
        ReleaseDC (wndId, DrawHDC);
    }
}

bool Circle::Contains (Point p) {
	return pow ((double)p.GetX () - (double)center.GetX (), 2) + pow ((double)p.GetY () - (double)center.GetY (), 2) <= pow ((double)radius, 2);
}
