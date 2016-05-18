#include "Pickup.h"

//STRUCTORS
Pickup::Pickup() {
	this->def = PickupDef();
	this->loc = Point(-1, -1);
	this->uses = -1;
}
Pickup::Pickup(PickupDef def, Point loc) {
	this->def = def;
	this->loc = loc;
	this->uses = def.getUses();
}

//GETTERS / SETTERS
PickupDef Pickup::getPickupDef() {
	return def;
}
Point Pickup::getLoc() {
	return loc;
}
void Pickup::setLoc(Point nLoc) {
	loc = nLoc;
}
void Pickup::degrade() {
	if (uses > 0)
		uses--;
}
int Pickup::getUsesLeft() {
	return uses;
}