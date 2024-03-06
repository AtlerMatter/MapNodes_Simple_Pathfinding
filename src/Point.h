#pragma once

class Point {
private:
	int x, y;
public:
	Point ();
	Point (int x0, int y0);
	void SetX (int new_x);
	int GetX ();
	void SetY (int new_y);
	int GetY ();
	double GetDistance (Point p2);
};
