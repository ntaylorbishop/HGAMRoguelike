#pragma once
#include <vector>

#include "PickupDef.h"
#include "Pickup.h"
#include "Point.h"
#include "TileLibrary.h"
#include "MessageLog.h"
#include "Hero.h"
#include "InventoryLog.h"


class Shop {
public:
	Shop();
	Shop(Point loc, int difficulty, vector<PickupDef> potItems, TileLibrary* lib, Hero* hero, MessageLog* log, InventoryLog* invLog);

	void renderShop();

	void buy(Point loc);
	void sell(Pickup p);

	void activateShop();
	bool isShopping();

	//Getters / setters
	Point getLoc();
	void setLoc(Point nLoc);
	int getTile();

	//Utility
	int idxFromPoint(Point loc);
private:
	vector<PickupDef> shopItems;
	vector<PickupDef> potItems;
	Point loc;
	int shopGold = 10000;
	int difficulty;
	int tile = 0x0C0;
	bool shopOpen = false;

	Point start, end;

	Hero* hero;
	TileLibrary* lib;
	MessageLog* log;
	InventoryLog* invLog;
	vector<Pickup> storeItems;
	int storeSize = 35;
};

