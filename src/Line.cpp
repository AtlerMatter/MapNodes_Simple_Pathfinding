#include "Line.h"
#include<math.h>

Line::Line () {
	this->pf = Point();
	this->pi = Point();
}

Line::Line (Point p1, Point p2) {
	this->pi = p1;
	this->pf = p2;
}

void Line::Draw (HWND wndId, long color) {
	if (wndId != NULL) {
		if (wndId != NULL) {
			HPEN hOPen;
			// penstyle, width, color 
			HPEN hNPen = CreatePen (PS_SOLID, 2, color);
			HDC DrawHDC = GetDC (wndId);
			hOPen = (HPEN)SelectObject (DrawHDC, hNPen);
			// starting point of line 
			MoveToEx (DrawHDC, pi.GetX (), pi.GetY (), NULL);
			// ending point of line 
			LineTo (DrawHDC, pf.GetX (), pf.GetY ());
			DeleteObject (SelectObject (DrawHDC, hOPen));
			ReleaseDC (wndId, DrawHDC);
		}
	}
}

double Line::GetLength () {
	return sqrt( pow( (double)this->pi.GetX() - (double)this->pf.GetX(), 2) + pow((double)this->pi.GetY() - (double)this->pf.GetY(), 2) );
}
