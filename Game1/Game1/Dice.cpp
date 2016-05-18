#include "Dice.h"

Dice::Dice() {
	this->sides = -1;
	this->rolls = -1;
}
Dice::Dice(int sides, int rolls) {
	this->sides = sides;
	this->rolls = rolls;
}
int Dice::rollDice() {
	int sum = 0;
	for (int i = 1; i < rolls; i++)
		sum += rand() % sides + 1;
	return sum;
}
string Dice::to_str() {
	return to_string(rolls) + ", " + to_string(rolls * sides);
}

int Dice::getSides() {
	return sides;
}
int Dice::getRolls() {
	return rolls;
}
void Dice::setSides(int sides) {
	this->sides = sides;
}
void Dice::setRolls(int rolls) {
	this->rolls = rolls;
}