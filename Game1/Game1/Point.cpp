#include "Point.h"


//Structors
Point::Point() {
	xCoord = 0;
	yCoord = 0;
}
Point::Point(int x, int y) {
	xCoord = x;
	yCoord = y;
}

//Getters / Setters
int Point::x() {
	return xCoord;
}
int Point::y() {
	return yCoord;
}
void Point::setx(int x) {
	this->xCoord = x;
}
void Point::sety(int y) {
	this->yCoord = y;
}
void Point::setCoords(int x, int y) {
	this->xCoord = x;
	this->yCoord = y;
}

string Point::to_str() {
	return "(" + to_string(xCoord) + ", " + to_string(yCoord) + ")";
}

Point operator+(const Point &p1, const Point &p2) {
	return Point(p1.xCoord + p2.xCoord, p1.yCoord + p2.yCoord);
}
Point operator-(const Point &p1, const Point &p2) {
	return Point(p1.xCoord - p2.xCoord, p1.yCoord - p2.yCoord);
}