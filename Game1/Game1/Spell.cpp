#include "Spell.h"

Spell::Spell() {
	this->title = "";
	this->desc = "";
	this->icon = 0;
	this->reqLvl = -1;
	this->spellType = 0;
	this->cost = -1;
}
Spell::Spell(string title, string desc, int icon, int reqLvl, int spellType, int cost) {
	this->title = title;
	this->desc = desc;
	this->icon = icon;
	this->reqLvl = reqLvl;
	this->spellType = spellType;
	this->cost = cost;
}

void Spell::incSpellLvl() {
	spellLvl++;
}

string Spell::getTitle() {
	return title;
}
string Spell::getDesc() {
	return desc;
}
int Spell::getIcon() {
	return icon;
}
int Spell::getReqLvl() {
	return reqLvl;
}
int Spell::getCost() {
	return cost;
}
int Spell::getSpellType() {
	return spellType;
}
bool Spell::isUnlocked() {
	return unlocked;
}
void Spell::unlock() {
	unlocked = true;
}

int Spell::getTurnActivated() {
	return turnActivated;
}
void Spell::setTurnActivated(int turn) {
	turnActivated = turn;
}
int Spell::getNumTurns() {
	return numTurns;
}