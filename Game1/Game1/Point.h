#pragma once

#include <string>

using namespace std;

/*
 * Name: Point
 * Description: Holds an x,y point (in tile orientation)
 *
 */
class Point {
public:
	//Structors
	Point();
	Point(int x, int y);

	//Getters / Setters
	int x();
	int y();
	void setx(int x);
	void sety(int y);
	void setCoords(int x, int y);

	string to_str();

	//ARITHMETIC OPERATORS
	Point& operator=(const Point &rhs) {
		if (this == &rhs)
			return *this;
		else {
			xCoord = rhs.xCoord;
			yCoord = rhs.yCoord;
			return *this;
		}
	}
	friend Point operator+(const Point &p1, const Point &p2);
	friend Point operator-(const Point &p1, const Point &p2);

	Point& operator/(int n) {
		xCoord = xCoord / n;
		yCoord = yCoord / n;
		return *this;
	}

	//CONDITIONAL OPERATORS
	bool operator<(const Point &other) const {
		if (this->xCoord <= other.xCoord && this->yCoord < other.yCoord)
			return true;
		else if (this->xCoord < other.xCoord && this->yCoord <= other.yCoord)
			return true;
		else
			return false;
	}
	bool operator>(const Point &other) const {
		return !(*this < other);
	}
	bool operator<=(const Point &other) const {
		if (this->xCoord <= other.xCoord && this->yCoord <= other.yCoord)
			return true;
		else
			return false;
	}
	bool operator>=(const Point &other) const {
		if (this->xCoord >= other.xCoord && this->yCoord >= other.yCoord)
			return true;
		else
			return false;
	}
	bool operator==(const Point &other) const {
		if (this->xCoord == other.xCoord && this->yCoord == other.yCoord)
			return true;
		else
			return false;
	}
	bool operator!=(const Point &other) const {
		return !(*this == other);
	}

private:
	int xCoord;
	int yCoord;
};
