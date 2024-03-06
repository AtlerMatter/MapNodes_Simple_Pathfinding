#include "Point.h"
#include<math.h>

Point::Point () {
	this->x = 0;
	this->y = 0;
}

Point::Point (int x0, int y0) {
	this->x = x0;
	this->y = y0;
}

void Point::SetX (int new_x) {
	this->x = new_x;
}

int Point::GetX () {
	return this->x;
}

void Point::SetY (int new_y) {
	this->y = new_y;
}

int Point::GetY () {
	return this->y;
}

double Point::GetDistance (Point p2) {
	return sqrt(pow((double)p2.GetX() - (double)this->GetX(), 2) + pow ((double)p2.GetY () - (double)this->GetY (), 2));
}
