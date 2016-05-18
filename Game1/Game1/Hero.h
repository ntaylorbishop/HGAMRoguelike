#pragma once
#ifndef HERO_H
#define HERO_H
#include <vector>

#include "Actor.h"
#include "Dice.h"

class Hero: public Actor {
public:
	Hero(ActorDef def, Point loc, bool isHero) : Actor(def, loc, isHero, false) { base_atk = def.actorATK(); };
	void changeATK(Dice d);
	void revertATK();
	void changeDEF(int num);
	void changeHP(int num);
	void changeMaxHP(int num);

	void changeMana(int num);
	void changeMaxMana(int num);

	int getMana();
	int getMaxMana();
private:
	Dice base_atk;
	int mana = 100;
	int maxMana = 100;
};

#endif
