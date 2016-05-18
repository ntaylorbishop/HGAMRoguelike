#pragma once
#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>

#include "MessageLog.h"
#include "InventoryLog.h"
#include "TileLibrary.h"
#include "Cell.h"
#include "Point.h"
#include "ActorDef.h"
#include "Actor.h"
#include "PickupDef.h"
#include "Pickup.h"
#include "Dice.h"
#include "Hero.h"
#include "Shop.h"

using namespace std;

class GameEngine {
public:
	//Structors
	GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize);
	~GameEngine();

	void run();
	bool quitGame();

	template <class T> T pickfromtable(vector<T> table) {
		//Set difficulty frequencies
		for (unsigned int i = 0; i < table.size(); i++) {
			float freqFloat = ((float)currLevel / (float)table[i].getWeight()) * 100.0;
			int freq = (int)freqFloat;
			table[i].setWeight(freq);
		}

		int totalSum = 0;
		for (unsigned int i = 0; i < table.size(); i++)
			totalSum += table[i].getWeight();

		int index = rand() % totalSum;

		int sum = 0;
		int i = 0;
		while (sum < index) {
			sum = sum + table[i++].getWeight();
		}
		if (i == 0)
			i++;
		int which = rand() % i;
		return table[which];
	}
private:
	//Game Menu
	bool gameStart = false;
	int heroAnimMenu = 0;
	int animSpeed = 0;
	bool justDied = true;

	int worldSize;

	vector<vector<Cell>> map;
	vector<Point> playableMap;
	vector<Actor*> monsters;
	vector<ActorDef> actordefs;
	vector<Pickup*> pickups;
	vector<PickupDef> pickupdefs;

	Point screenOrientation;
	TileLibrary lib;
	MessageLog log;
	InventoryLog invLog;
	Hero* hero;
	bool deadHero = false;
	int turns = 0;
	Shop shop;

	//Level stuff
	int currLevel;
	Point stairLoc;
	int wallTile;
	int floorTile;

	//Math stuff
	vector<long> rads;
	double pi = 3.14159265358979323846;

	ActorDef main = ActorDef(Dice(3, 4), 1, 100, 0x0AC, "The hero", 1);

	//Monster table
	ActorDef rat       = ActorDef(Dice(3, 3), 0, 20, 0x0D9, "Mutated rat",          1);
	ActorDef spider    = ActorDef(Dice(3, 3), 0, 20, 0x0DF, "Big spider",           1);
	ActorDef ant       = ActorDef(Dice(3, 3), 0, 20, 0x080, "Angry ant",            1);
	ActorDef bee       = ActorDef(Dice(3, 3), 0, 20, 0x081, "Giant bee",            1);
	ActorDef beetle    = ActorDef(Dice(4, 2), 0, 20, 0x084, "Dung beetle",          1);
	ActorDef snake     = ActorDef(Dice(3, 3), 0, 20, 0x086, "Rattlesnake",          1);
	ActorDef dingo     = ActorDef(Dice(2, 2), 1, 30, 0x08C, "Rabid dingo",          1);
	ActorDef fox       = ActorDef(Dice(4, 3), 2, 30, 0x08D, "Mama fox",             1);
	ActorDef plant     = ActorDef(Dice(4, 3), 1, 30, 0x09C, "Mutated plant",        1);
	ActorDef puppy     = ActorDef(Dice(4, 3), 1, 30, 0x090, "Young wolf",           1);

	ActorDef giant_rat = ActorDef(Dice(4, 5), 2, 40, 0x0DA, "Giant mutated rat",    2);
	ActorDef tarantula = ActorDef(Dice(4, 5), 2, 40, 0x0E0, "Mutated tarantula",    2);
	ActorDef fire_ant  = ActorDef(Dice(4, 5), 2, 40, 0x080, "Mutated fire aunt",    2);
	ActorDef hornet    = ActorDef(Dice(4, 5), 2, 40, 0x085, "Giant Mutated hornet", 2);
	ActorDef snow_wolf = ActorDef(Dice(4, 6), 2, 40, 0x094, "Snow wolf",            2);
	ActorDef werewolf  = ActorDef(Dice(4, 6), 2, 50, 0x096, "Werewolf",             2);
	ActorDef hyena     = ActorDef(Dice(5, 6), 3, 50, 0x08D, "Hyena",                3);
	ActorDef eye_djinn = ActorDef(Dice(5, 6), 3, 50, 0x09D, "Eye of D'jinn",        3);
	ActorDef cerberus  = ActorDef(Dice(5, 6), 3, 50, 0x09A, "Cerberus wolf",        3);
	ActorDef tent_mon  = ActorDef(Dice(5, 6), 3, 50, 0x0A1, "Tentacle monster",     3);

	ActorDef priest     =  ActorDef(Dice(9, 10), 5, 60, 0x0B1, "Amalori Priest",     5);
	ActorDef hpriest    =  ActorDef(Dice(8, 10), 5, 60, 0x0B2, "Amalori High Priest",5);
	ActorDef sad_bag    =  ActorDef(Dice(7, 8), 5, 70, 0x0B6, "Sad Paper Bag",       5);
	ActorDef ass_goblin =  ActorDef(Dice(7, 9), 5, 70, 0x07E, "Goblin Assassin",     5);

	//Bosses
	ActorDef boss1 = ActorDef(Dice(5, 9), 1, 20, 0x08B, "Katar's Phoenix (BOSS)", 50);
	ActorDef boss2 = ActorDef(Dice(7, 9), 2, 20, 0x0EA, "Grim's Reaper (BOSS)", 50);
	ActorDef boss3 = ActorDef(Dice(7, 9), 3, 20, 0x0E8, "King of Katar (BOSS)", 50);
	ActorDef boss4 = ActorDef(Dice(10, 11), 4, 20, 0x0E7, "Amalori Drake (BOSS)", 50);
	ActorDef boss5 = ActorDef(Dice(9, 8), 5, 20, 0x0E9, "Katar's Right Hand (BOSS)", 50);
	ActorDef boss6 = ActorDef(Dice(8, 9), 6, 20, 0x0C6, "Amalori Witch Queen (BOSS)", 50);

	//Boss stuff
	Actor* boss;
	vector<ActorDef> bossdefs;
	vector<PickupDef> legendarydefs;
	Point bossLoc;
	Point bossInRoomLoc;
	Point stairAscend;
	vector<vector<Cell>> bossMap;
	vector<vector<Cell>> mapHold;
	vector<Pickup*> pickupsHold;
	vector<Pickup*> bossRoomPickups;
	int worldSizeHold;
	int bossMapSize = 11;
	bool inBossRoom = false;
	bool bossIsDead = false;

	void enterBossRoom();
	void leaveBossRoom();

	void generateLevel();
	Point addToRandomLoc(Cell t);
	Point getRandomLoc();

	//Rendering funcs
	void drawMap();
	void fillBox(Point pStart, Point pEnd);
	int floodFill(Point loc, int zone, int size);
	void renderFogOfWar();
	void drawBressenhamLine(int octant, Point delta);
	Point switchOctant(int octant, Point p);

	void doBattle(Actor* atkr, Actor* atkd); //Returns 0 if nobody died, 1 if atkr died, 2 if atkd died

	bool moveableCell(Point p);
	void onPlayerTurn(bool b, Point p);
	bool moveAI(Actor* monster);
	Point pickAIPoint(Actor* monster, Point dir, bool random);
	Point pickRandomPoint();

	void killMonster(Point loc);
	void killHero();
	void addPickup(Point loc);

	//Mouse funcs
	Pickup registerInventoryClick();
	void onMouseOver();

	//Spell stuff
	void useSpell(Point mouseLoc);

	void renderGameMenu();
	void restart();
};

#endif