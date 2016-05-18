#pragma once
#ifndef INVENTORYLOG_H
#define INVENTORYLOG_H
#include <vector>
#include <string>
#include <Windows.h>

#include "TileLibrary.h"
#include "Point.h"
#include "MessageLog.h"
#include "Pickup.h"
#include "Hero.h"
#include "Spell.h"

class InventoryLog
{
public:
	void init(TileLibrary* library, Hero* hero, MessageLog* log);
	bool addItem(Pickup item);
	void renderInventory();
	Pickup useItem(Point loc);

	int idxFromPoint(Point loc);
	bool isInventoryFull();

	int getItemType(Point loc);

	//Gear
	void renderGear();
	void degradeGear();

	Pickup unequipGear(Point loc);
	Pickup dropItem(Point loc);
	bool itemAlreadyEquipped(Point loc);
	Pickup getInvItemAtLoc(Point loc);
	int overInvOrGear(Point mouseLoc); //0 for inventory, 1 for gear, 2 for neither

	Pickup getItemAtLoc(Point loc);

	int getGold();
	void changeGold(int amount);

	Pickup sellItem(Point loc);

	//Leveling stuff
	void enemyKilled(int xp);
	void levelUp();

	//Spell stuff
	void renderSpells();
	Spell getSpell(Point mouseLoc);
private:
	TileLibrary* lib;
	MessageLog* log;
	vector<Pickup> inventory;
	vector<Pickup> gear;
	Hero* hero;
	int maxSize;
	int gearBoxSize;
	int numGear;
	int highlight_color;
	vector<int> gearSlotIcons;
	int goldAmount = 100;

	int xp = 1;
	int lvl = 1;
	int toNextLvl = 10;
	vector<Spell> spells;

	//Spell stuff
	Spell spell1 = Spell("Field of Fire", "Creates a field of fire around the hero", 0x340, 2, 1, 5);
	Spell spell2 = Spell("Death Rattle", "Forces monsters back, deals damage", 0x350, 3, 2, 10);
	Spell spell3 = Spell("Blessing of Katar", "Heals the hero", 0x367, 4, 3, 10);
	Spell spell4 = Spell("Ice Block", "Freezes nearby enemies", 0x37B, 5, 4, 15);
	Spell spell5 = Spell("Death Curse", "Curses enemies, damaging every turn", 0x39C, 6, 5, 15);
	Spell spell6 = Spell("Fist of Katar", "Places a trap at the hero's location", 0x34A, 7, 6, 20);
};

#endif