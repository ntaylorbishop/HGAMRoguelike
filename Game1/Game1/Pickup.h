#pragma once

#include "Point.h"
#include "PickupDef.h"

class Pickup {
public:
	//STRUCTORS
	Pickup();
	Pickup(PickupDef def, Point loc);

	//GETTERS / SETTERS
	PickupDef getPickupDef();
	Point getLoc();
	void setLoc(Point nLoc);
	void degrade();
	int getUsesLeft();

	bool operator==(const Pickup &other) const {
		if (this->def == other.def)
			return true;
		else
			return false;
	}
	bool operator!=(const Pickup &other) const {
		return !(*this == other);
	}
private:
	PickupDef def;
	Point loc;
	int uses;
};

