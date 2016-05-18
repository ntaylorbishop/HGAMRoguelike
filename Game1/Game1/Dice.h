#pragma once

#include <cstdlib>
#include <string>

using namespace std;

class Dice
{
public:
	Dice();
	Dice(int sides, int rolls);
	int rollDice();
	string to_str();

	int getSides();
	int getRolls();
	void setSides(int sides);
	void setRolls(int rolls);

	bool operator==(const Dice &other) const {
		if (this->sides == other.sides && this->rolls == other.rolls)
			return true;
		else
			return false;
	}
	bool operator!=(const Dice &other) const {
		return !(*this == other);
	}
private:
	int sides;
	int rolls;
};

