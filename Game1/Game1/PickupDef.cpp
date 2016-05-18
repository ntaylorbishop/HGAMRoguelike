#include "PickupDef.h"

//STRUCTORS
PickupDef::PickupDef() {
	this->tile = 0;
	this->name = name;
	this->desc = "NULL";
	this->type = type;
	this->useEffect = [](){};
	this->removeEffect = [](){};
	this->weight = 0;
}
PickupDef::PickupDef(int tile, string name, string desc, int weight, int price, function<void()> useEffect) {
	this->tile = tile;
	this->name = name;
	this->desc = desc;
	this->type = 0;
	this->useEffect = useEffect;
	this->removeEffect = [](){};
	this->weight = weight;
	this->price = price;
}
PickupDef::PickupDef(int tile, string name, string desc, int type, int uses, int weight, int price, function<void()> useEffect, function<void()> removeEffect) {
	this->tile = tile;
	this->name = name;
	this->desc = desc;
	this->type = type;
	this->uses = uses;
	this->useEffect = useEffect;
	this->removeEffect = removeEffect;
	this->weight = weight;
	this->price = price;
}
PickupDef::PickupDef(int tile, string name, string desc, int type, int uses, int weight, int price) {
	this->tile = tile;
	this->name = name;
	this->desc = desc;
	this->type = type;
	this->uses = uses;
	this->weight = weight;
	this->price = price;
}

//GETTERS / SETTERS
int PickupDef::getTile() {
	return tile;
}
string PickupDef::getName() {
	return name;
}
string PickupDef::getDESC() {
	return desc;
}
int PickupDef::getType() {
	return type;
}
string PickupDef::getTypeName() {
	switch (type) {
		case 1:
			return "head piece";
			break;
		case 2:
			return "necklace";
			break; 
		case 3:
			return "chest piece";
			break; 
		case 4:
			return "glove";
			break; 
		case 5:
			return "boot";
			break; 
		case 6:
			return "tomb";
			break; 
		case 7:
			return "weapon";
			break; 
		case 8:
			return "shield";
			break; 
	}
}
int PickupDef::getUses() {
	return uses;
}
int PickupDef::getWeight() {
	return weight;
}
void PickupDef::setWeight(int weight) {
	this->weight = weight;
}
int PickupDef::getPrice() {
	return price;
}

void PickupDef::addEffects(function <void()> useEffect, function <void()> removeEffect) {
	this->useEffect = useEffect;
	this->removeEffect = removeEffect;
}