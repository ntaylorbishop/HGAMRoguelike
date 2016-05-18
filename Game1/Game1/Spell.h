#ifndef SPELL_H
#define SPELL_H

#include <string>

using namespace std;

class Spell {
public:
	Spell();
	Spell(string title, string desc, int icon, int reqLvl, int spellType, int cost);

	void incSpellLvl();

	string getTitle();
	string getDesc();
	int getIcon();
	int getReqLvl();
	int getCost();
	int getSpellType();
	bool isUnlocked();
	void unlock();

	void setTurnActivated(int turn);
	int getTurnActivated();
	int getNumTurns();
private:
	string title;
	string desc;
	
	int icon;
	int spellLvl;
	int reqLvl;
	bool unlocked = false;
	int spellType;
	int cost;
	int turnActivated = 1;
	int numTurns = 5;
};

#endif /* SPELL_H */
