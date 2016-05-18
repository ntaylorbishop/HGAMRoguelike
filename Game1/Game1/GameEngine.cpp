#include "GameEngine.h"

//Structors
GameEngine::GameEngine(char* title, int xScreenRes, int yScreenRes, char* tiles, int tileSize, int tileRes, int worldSize) {
	lib.init(title, xScreenRes, yScreenRes, tiles, tileSize, tileRes);
	this->worldSize = worldSize;
	currLevel = 1;

	screenOrientation = lib.res() / 2;

	//Add monster table
	actordefs = { rat, spider, ant, bee, beetle, snake, dingo, fox, plant, puppy,
		          giant_rat, tarantula, fire_ant, hornet, snow_wolf, werewolf, hyena, 
				  eye_djinn, cerberus, tent_mon, priest, hpriest, sad_bag, ass_goblin 
	};

	//Add boss table
	bossdefs = { boss1, boss2, boss3, boss4, boss5, boss6 };

	hero = new Hero(main, Point(0, 0), true);

	//Add pickup table stuff for sloppy
	pickupdefs = {
		//health pots
		PickupDef(0x227, "Small Health Potion", "Restores 10 HP", 1, 100, [&]() { hero->changeHP(10); }),
		PickupDef(0x237, "Big Health Potion", "Restores 20 HP", 2, 200, [&]() { hero->changeHP(20); }),
		PickupDef(0x220, "Large Health Potion", "Restores 30 HP", 3, 300, [&]() { hero->changeHP(30); }),

		//mana pots
		PickupDef(0x22A, "Small Mana Potion", "Restores 5 mana", 1, 100, [&]() { hero->changeMana(5); }),
		PickupDef(0x23A, "Mana Potion", "Restores 10 mana", 2, 100, [&]() { hero->changeMana(10); }),
		PickupDef(0x223, "Large Mana Potion", "Restores 20 mana", 3, 300, [&]() { hero->changeMana(20); }),

		//helms
		PickupDef(0x2DC, "Crude Helmet", "Increases defense by 1", 1, 5, 1, 100, [&]() { hero->changeDEF(1); }, [&]() { hero->changeDEF(-1); }),
		PickupDef(0x2DD, "Steel Helmet", "Increases defense by 2", 1, 5, 2, 200, [&]() { hero->changeDEF(2); }, [&]() { hero->changeDEF(-2); }),
		PickupDef(0x2D9, "Magician's Hat", "Increases max health by 10", 1, 5, 4, 400, [&]() { hero->changeMaxHP(10); }, [&]() { hero->changeMaxHP(-10); }),

		//necks
		PickupDef(0x337, "Worn Necklace", "Increases max health by 5", 2, 10, 1, 100, [&]() { hero->changeMaxHP(5); }, [&]() { hero->changeMaxHP(-5); }),
		PickupDef(0x338, "Fine Necklace", "Increases defense by 2", 2, 5, 2, 200, [&]() { hero->changeDEF(2); }, [&]() { hero->changeDEF(-2); }),
		PickupDef(0x33B, "Cross of Al'tair", "Increases defense by 4", 2, 5, 4, 400, [&]() { hero->changeDEF(4); }, [&]() { hero->changeDEF(-4); }),

		//shirts
		PickupDef(0x2D0, "Tattered Shirt", "Increases max health by 5", 3, 5, 1, 100, [&]() { hero->changeMaxHP(5); }, [&]() { hero->changeMaxHP(-5); }),
		PickupDef(0x2D1, "Gold Chainmail", "Increases max health by 10", 3, 5, 2, 200, [&]() { hero->changeMaxHP(10); }, [&]() { hero->changeMaxHP(-10); }),
		PickupDef(0x2D2, "Vest of the Thief's Guild", "Increases defense by 3", 3, 5, 4, 400, [&]() { hero->changeDEF(3); }, [&]() { hero->changeDEF(-3); }),

		//gloves
		PickupDef(0x2E7, "Worn Leather Glove", "Increases defense by 1", 4, 4, 1, 100, [&]() { hero->changeDEF(1); }, [&]() { hero->changeDEF(-1); }),
		PickupDef(0x2E9, "Chainmail Glove", "Increases defense by 2", 4, 4, 2, 200, [&]() { hero->changeDEF(2); }, [&]() { hero->changeDEF(-2); }),
		PickupDef(0x2EA, "Glove of the Magi", "Increases max health by 10", 4, 4, 4, 400, [&]() { hero->changeMaxHP(10); }, [&]() { hero->changeMaxHP(-10); }),

		//shoes
		PickupDef(0x2E1, "Smelly Old Shoe", "Increases defense by 1", 5, 5, 1, 100, [&]() { hero->changeDEF(1); }, [&]() { hero->changeDEF(-1); }),
		PickupDef(0x2E2, "Fine Leather Shoe", "Increases defense by 2", 5, 5, 2, 200, [&]() { hero->changeDEF(2); }, [&]() { hero->changeDEF(-2); }),
		PickupDef(0x2E3, "Knight's Boot", "Increases defense by 3", 5, 5, 4, 400, [&]() { hero->changeDEF(3); }, [&]() { hero->changeDEF(-3); }),

		//journals
		PickupDef(0x3D1, "Standard Spell Journal", "Increases max health by 5", 6, 10, 1, 100, [&]() { hero->changeMaxHP(5); }, [&]() { hero->changeMaxHP(-5); }),
		PickupDef(0x3D3, "Mage's Necronomicon", "Increases max health by 7", 6, 10, 2, 200, [&]() { hero->changeMaxHP(7); }, [&]() { hero->changeMaxHP(-7); }),
		PickupDef(0x3D4, "Death Note", "Increases max health by 9", 6, 10, 4, 400, [&]() { hero->changeMaxHP(9); }, [&]() { hero->changeMaxHP(-9); }),

		//swords
		PickupDef(0x260, "Crude Dagger", "Attack: (2, 14)", 7, 5, 1, 100, [&]() { hero->changeATK(Dice(7, 2)); }, [&]() { hero->revertATK(); }),
		PickupDef(0x253, "Fine Longsword", "Attack: (3, 15)", 7, 5, 2, 200, [&]() { hero->changeATK(Dice(5, 3)); }, [&]() { hero->revertATK(); }),
		PickupDef(0x2A2, "Ogre's Battleaxe", "Attack: (4, 16)", 7, 5, 3, 300, [&]() { hero->changeATK(Dice(4, 4)); }, [&]() { hero->revertATK(); }),

		//shields
		PickupDef(0x2C0, "Broken Shield", "Increases defense by 1", 8, 2, 1, 100, [&]() { hero->changeDEF(1); }, [&]() { hero->changeDEF(-1); }),
		PickupDef(0x2C2, "Fine Wooden Shield", "Increases defense by 4", 8, 2, 2, 200, [&]() { hero->changeDEF(4); }, [&]() { hero->changeDEF(-4); }),
		PickupDef(0x2C3, "Tower Shield", "Increases defense by 5", 8, 2, 4, 400, [&]() { hero->changeDEF(5); }, [&]() { hero->changeDEF(-5); })
	};

	//Legendary items
	legendarydefs = {
		PickupDef(0x2D7, "Hakar's Skull", "Increases defense by 7", 1, 15, 4, 4000, [&]() { hero->changeDEF(7); }, [&]() { hero->changeDEF(-7); }),
		PickupDef(0x336, "Akator's Blessing", "Increases defense by 6", 2, 15, 4, 4000, [&]() { hero->changeDEF(6); }, [&]() { hero->changeDEF(-6); }),
		PickupDef(0x2D6, "Hakar's Skin", "Increases defense by 7", 3, 15, 4, 4000, [&]() { hero->changeDEF(7); }, [&]() { hero->changeDEF(-7); }),
		PickupDef(0x2ED, "Shadowborn Glove", "Increases max health by 40", 4, 15, 4, 4000, [&]() { hero->changeMaxHP(40); }, [&]() { hero->changeMaxHP(-40); }),
		PickupDef(0x2E5, "Shadowborn Shoe", "Increases defense by 5", 5, 15, 4, 4000, [&]() { hero->changeDEF(5); }, [&]() { hero->changeDEF(-5); }),
		PickupDef(0x3D6, "Hakar's Bible", "Increases max health by 50", 6, 15, 4, 4000, [&]() { hero->changeMaxHP(50); }, [&]() { hero->changeMaxHP(-50); }),
		PickupDef(0x390, "Akator's Right Hand", "Attack: (10, 20)", 7, 15, 4, 4000, [&]() { hero->changeATK(Dice(10, 2)); }, [&]() { hero->revertATK(); }),
		PickupDef(0x2C4, "Hakar's Left Hand", "Increases defense by 6", 8, 15, 4, 4000, [&]() { hero->changeDEF(6); }, [&]() { hero->changeDEF(-6); }),
	};

	//Set up MessageLog / Inventory
	log.init(&lib);
	invLog.init(&lib, hero, &log);

	generateLevel();
}
GameEngine::~GameEngine() {
	for (vector<Actor*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
		delete *it;
	for (vector<Pickup*>::iterator it = pickups.begin(); it != pickups.end(); ++it)
		delete *it;
	delete hero;
	lib.shutdown();
}

void GameEngine::renderGameMenu() {
	justDied = false;

	lib.loop_portion(Point(0, 0), lib.res(), [&](Point p) {
		lib.rendertile(0x125, p);
	});

	tl_scale(2);
	string title = "Welcome to the Kingdoms of Amalor!";
	Point center = Point(lib.res().x() / 2 - title.length() / 2, lib.res().y() / 2 - 15);
	lib.renderText(center, title);

	tl_scale(3);
	string title2 = "Press enter to start the game";
	Point t2Loc = Point(lib.res().x() / 2 - title2.length() / 2, lib.res().y() / 2);
	lib.renderText(t2Loc, title2);
	string title3 = "Press escape to exit the game";
	Point t3Loc = Point(lib.res().x() / 2 - title3.length() / 2, lib.res().y() / 2 + 2);
	lib.renderText(t3Loc, title3);

	tl_scale(1);

	//Take input
	if (lib.keywentdown("return") || lib.keywentdown("enter")) {
		gameStart = true;
		justDied = true;
		if (deadHero) {
			restart();
		}
	}

	//Player animation
	if (heroAnimMenu > lib.res().x() + 1)
		heroAnimMenu = 0;

	Point p(heroAnimMenu, lib.res().y() - 5);
	lib.rendertile(0x0AC, p);

	animSpeed++;
	if (animSpeed % 20 == 0)
		heroAnimMenu++;
}

void GameEngine::restart() {
	//Reinitialize the inventory and message log
	log = MessageLog();
	invLog = InventoryLog();
	log.init(&lib);
	invLog.init(&lib, hero, &log);

	//Re initialize the hero
	deadHero = false;
	delete hero;

	hero = new Hero(main, Point(0, 0), true);

	currLevel = 1;
	inBossRoom = false;
	generateLevel();
}

//main
void GameEngine::run() {
	lib.framestart();
	
	if (!gameStart)
		renderGameMenu();
	else {
		//Move the char left, right, up, and down
		if (!deadHero && !shop.isShopping()) {
			onPlayerTurn((lib.keywentdown("left") || lib.keywentdown("a")), Point(-1, 0));
			onPlayerTurn((lib.keywentdown("up") || lib.keywentdown("w")), Point(0, -1));
			onPlayerTurn((lib.keywentdown("right") || lib.keywentdown("d")), Point(1, 0));
			onPlayerTurn((lib.keywentdown("down") || lib.keywentdown("s")), Point(0, 1));

			//Enter stairs
			if (lib.keywentdown("return") || lib.keywentdown("enter")) {
				if (hero->getLoc() == stairLoc) {
					currLevel++;
					generateLevel();
				}
				if (hero->getLoc() == shop.getLoc())
					shop.activateShop();
				if (hero->getLoc() == bossLoc)
					enterBossRoom();
				if (hero->getLoc() == stairAscend)
					leaveBossRoom();
			}

			if (tl_buttonwentdown(1)) {
				Pickup p = registerInventoryClick();
				if (p.getLoc() != Point(-1, -1)) {
					if (p.getPickupDef().getType() == 0)
						log.registerEvent(("Used a " + p.getPickupDef().getName() + "!").c_str());
					else
						log.registerEvent(("Equipped a " + p.getPickupDef().getName() + "!").c_str());
				}

				if (lib.mouseLoc() >= Point(lib.res().x() / 2 - 3, lib.res().y() - 4) && lib.mouseLoc() <= Point(lib.res().x() / 2 + 3, lib.res().y() - 4))
					useSpell(lib.mouseLoc());
			}
			if (tl_buttonwentdown(3)) {
				Pickup p;

				if (invLog.overInvOrGear(lib.mouseLoc()) == 0) {
					p = invLog.dropItem(lib.mouseLoc());
					if (p.getLoc() != Point(-1, -1))
						log.registerEvent(("Dropped the " + p.getPickupDef().getName() + "!").c_str());
				}
				else if (invLog.overInvOrGear(lib.mouseLoc()) == 1) {
					OutputDebugString("herpderp");
					p = invLog.unequipGear(lib.mouseLoc());
					if (p.getLoc() != Point(-1, -1))
						log.registerEvent(("Unequipped the " + p.getPickupDef().getName() + "!").c_str());
				}
			}
		}

		drawMap();

		onMouseOver();
		if(deadHero) {
			if (lib.keywentdown("escape"))
				gameStart = false;
		}
	}
}

void GameEngine::generateLevel() {

	//Clear out the last level
	for (vector<Actor*>::iterator it = monsters.begin(); it != monsters.end(); ++it)
		delete (*it);
	monsters.clear();
	for (vector<Pickup*>::iterator it = pickups.begin(); it != pickups.end(); ++it)
		delete (*it);
	pickups.clear();
	map.clear();
	playableMap.clear();

	//Set tile graphics for curr floor
	if (currLevel == 1) {
		wallTile = 0x103;
		floorTile = 0x100;
	}
	else if (currLevel > 1) {
		wallTile = 0x14D;
		floorTile = 0x13E;

		delete boss;
	}

	//Initialize the outer map vector
	for (int i = 0; i < worldSize; i++) {
		vector<Cell> v;
		map.push_back(v);
	}

	//Generate the map boundaries
	lib.loop_portion(Point(0, 0), Point(worldSize, worldSize), [&](Point p) {
		Cell c(p, 2, wallTile, 0);
		map[p.x()].push_back(c);
	});

	//Generate the random rooms
	for (int i = 0; i < rand() % 130 + 100; i++) {
		Point pStart((rand() % 55 + 1), (rand() % 55 + 1));
		Point pEnd(pStart.x() + (rand() % 6 + 3), pStart.y() + (rand() % 6 + 3));

		fillBox(pStart, pEnd);
	}

	//Flood fill to connect the world
	int currZone = 0;
	vector<int> zoneSize;
	lib.loop_portion(Point(0, 0), Point(worldSize, worldSize), [&](Point p) {
		if (map[p.x()][p.y()].getCellType() != 2 && map[p.x()][p.y()].getZone() == 0) {
			currZone++;
			int size = floodFill(map[p.x()][p.y()].getLoc(), currZone, 0);
			zoneSize.push_back(size);
		}
	});

	//Get biggest zone in array
	int max = zoneSize[0];
	int largestZone = 0;
	for (unsigned int i = 1; i < zoneSize.size(); i++) {
		if (zoneSize[i] > max) {
			largestZone = i;
			max = zoneSize[i];
		}
	}
	largestZone++; //Offset for vector index

	//Get rid of everything but largest zone
	int end = worldSize - 1;
	lib.loop_portion(Point(0, 0), Point(worldSize, worldSize), [&](Point p) {
		Cell& c = map[p.x()][p.y()];

		if (c.getZone() != largestZone) {
			if ((p.x() + 1 < end && map[p.x() + 1][p.y()].getZone() == largestZone) ||
				(p.x() - 1 > 0 && map[p.x() - 1][p.y()].getZone() == largestZone) ||
				(p.y() + 1 < end && map[p.x()][p.y() + 1].getZone() == largestZone) ||
				(p.y() - 1 > 0 && map[p.x()][p.y() - 1].getZone() == largestZone) ||
				(p.x() - 1 > 0 && p.y() - 1 > 0 && map[p.x() - 1][p.y() - 1].getZone() == largestZone) ||
				(p.x() - 1 > 0 && p.y() + 1 < end   && map[p.x() - 1][p.y() + 1].getZone() == largestZone) ||
				(p.x() + 1 < end && p.y() - 1 > 0 && map[p.x() + 1][p.y() - 1].getZone() == largestZone) ||
				(p.x() + 1 < end && p.y() + 1 < end && map[p.x() + 1][p.y() + 1].getZone() == largestZone)) {
				c.setTile(wallTile);
				c.setTileType(2);
			}
			else {
				c.setTile(0);
				c.setTileType(2);
			}
		}
		else if (c.getLoc().x() == end)
			c.setTile(0);
	});

	//Set player starting position
	lib.loop_portion(Point(0, 0), Point(worldSize - 1, worldSize - 1), [&](Point p) {
		if (map[p.x()][p.y()].getZone() != 0 && map[p.x()][p.y()].getCellType() != 2)
			playableMap.push_back(map[p.x()][p.y()].getLoc());
	});

	//Add monsters
	for (unsigned int i = 0; i < playableMap.size(); i++) {
		int chance = rand() % 30;
		if (chance == 15) {
			//Make the monster
			ActorDef def = pickfromtable<ActorDef>(actordefs);
			monsters.push_back(new Actor(def, playableMap[i], false, false));
			map[playableMap[i].x()][playableMap[i].y()].setActor(monsters.back());

			//Give chance to spawn with item
			chance = rand() % 5 + 1; //Give 10% chance to spawn
			if (chance == 3) {
				PickupDef def = pickfromtable<PickupDef>(pickupdefs);
				pickups.push_back(new Pickup(def, playableMap[i]));
				map[playableMap[i].x()][playableMap[i].y()].setPickup(pickups.back());
			}
		}
	}

	//Set starting pos
	Point heroLoc = getRandomLoc();
	screenOrientation = heroLoc;
	hero->setLoc(screenOrientation);

	//Add stairs, shop, boss
	stairLoc = addToRandomLoc(Cell(Point(), 5, 0x1A0, -1));
	shop = Shop(addToRandomLoc(Cell(Point(), 6, 0x0C0, -1)), currLevel, pickupdefs, &lib, hero, &log, &invLog);
	bossLoc = addToRandomLoc(Cell(Point(), 7, 0x1AB, -1));
	bossInRoomLoc = Point(5, 2);


	//Instantiate the boss map
	for (int i = 0; i < bossMapSize; i++) {
		vector<Cell> row;
		for (int j = 0; j < bossMapSize; j++) {
			if (i == 0 || i == bossMapSize - 1 || j == 0 || j == bossMapSize - 1)
				row.push_back(Cell(Point(i, j), 2, 0x14B, 1));
			else
				row.push_back(Cell(Point(i, j), 1, 0x122, 1));
		}
		bossMap.push_back(row);
	}

	//Add the boss to its location in the boss map
	int which = rand() % bossdefs.size();
	boss = new Actor(bossdefs[which], bossInRoomLoc, false, true);
	bossMap[bossInRoomLoc.x()][bossInRoomLoc.y()].setActor(boss);
}
Point GameEngine::addToRandomLoc(Cell t) {
	int x = rand() % map.size();
	int y = rand() % map[x].size();

	if (map[x][y].getCellType() != 2 && map[x][y].getCellType() != 5 && map[x][y].getCellType() != 6 && map[x][y].getCellType() != 7) {
		map[x][y].setTileType(t.getCellType()); //Set to next level stairs
		map[x][y].setTile(t.getTile());
		return Point(x, y);
	}
	else
		return addToRandomLoc(t);
}
Point GameEngine::getRandomLoc() {
	int x = rand() % map.size();
	int y = rand() % map[x].size();

	if (map[x][y].getCellType() != 2 && map[x][y].getCellType() != 5 && map[x][y].getCellType() != 6)
		return Point(x, y);
	else
		return getRandomLoc();
}

bool GameEngine::quitGame() {
	if (lib.keywentdown("escape") && !gameStart && !justDied)
		return true;
	else
		return false;
}
void GameEngine::drawMap() {
	renderFogOfWar();

	Point world = screenOrientation - (lib.res() / 2);
	int yWorldOrig = world.y();

	for (int xScreen = 0; xScreen < lib.res().x(); xScreen++) {
		world.sety(yWorldOrig);
		for (int yScreen = 0; yScreen < lib.res().y(); yScreen++) {
			Point d(xScreen, yScreen);

			if (world.x() < 0 || world.y() < 0 || world.x() > worldSize - 1 || world.y() > worldSize - 1) {
				Cell t(d, 0, 0, 0);
				lib.rendertile(t.getTile(), d);
			}
			else {
				Cell t = map[world.x()][world.y()];

				//For of war stuff
				//Set stuff on screen back to not visible
				map[world.x()][world.y()].setVisibility(false);

				//Explore it if the bressenham lines
				if (t.isVisible() == false) {
					if (t.isExplored() && !t.isVisible())
						tl_color(0xFFFFFF70);
					else if (t.isExplored() && t.isVisible())
						tl_color(0xFFFFFFFF);
					else if (!t.isExplored() && !t.isVisible())
						tl_color(0xFFFFFF20);
				}

				if (t.getTile() != floorTile && t.getCellType() != 6)
					lib.rendertile(0, d);
				else if (t.getCellType() == 6)
					lib.rendertile(floorTile, d);

				lib.rendertile(t.getTile(), d);
				tl_color(0xFFFFFFFF);

				if (t.getPickup() != NULL && t.isVisible())
					lib.rendertile(t.getPickup()->getPickupDef().getTile(), d);

				//Set spell stuff
				if (t.getSpell().getSpellType() == 1) {
					if (turns > t.getSpell().getTurnActivated() + t.getSpell().getNumTurns())
						map[world.x()][world.y()].setSpell(Spell());
					else
						lib.rendertile(0x341, d);
				}
				if (t.getSpell().getSpellType() == 4) {
					if (turns > t.getSpell().getTurnActivated() + t.getSpell().getNumTurns()) {
						map[world.x()][world.y()].setSpell(Spell());
					}
					else
						lib.rendertile(0x377, d);
				}

				if (t.getActor() != NULL && t.isVisible()) {
					lib.rendertile(t.getActor()->getActorDef().getTile(), d);
					if (t.getActor()->getSpell().getSpellType() == 5) {
						if (turns > t.getActor()->getSpell().getTurnActivated() + t.getActor()->getSpell().getNumTurns()) {
							t.getActor()->setSpell(Spell());
						}
						else
							lib.rendertile(0x39D, d);
					}
				}

				if (t.getSpell().getSpellType() == 6)
					lib.rendertile(0x34A, d);
			}
			world = world + Point(0, 1);
		}
		world = world + Point(1, 0);
	}

	//Render MessageLog, InventoryLog, Shop
	log.renderMsgs();
	invLog.renderInventory();

	//Draw char
	if (!deadHero)
		lib.rendertile(hero->getActorDef().getTile(), lib.res() / 2);

	shop.renderShop();
}

void GameEngine::fillBox(Point pStart, Point pEnd) {
	lib.loop_portion(pStart, pEnd, [&](Point p) {
		map[p.x()][p.y()].setTile(floorTile);
		map[p.x()][p.y()].setTileType(1);
	});
}

int GameEngine::floodFill(Point loc, int zone, int size) {
	if (!(loc.x() < 0 || loc.x() > worldSize - 1 || loc.y() < 0 || loc.y() > worldSize - 1)) {
		if (map[loc.x()][loc.y()].getZone() != 0 || map[loc.x()][loc.y()].getCellType() == 2)
			return 1;
		else {
			map[loc.x()][loc.y()].setZone(zone);
			return size + floodFill(loc - Point(0, 1), zone, size) + floodFill(loc - Point(1, 0), zone, size)
				        + floodFill(loc + Point(1, 0), zone, size) + floodFill(loc + Point(0, 1), zone, size);
		}
	}
	else
		return size;
}
void GameEngine::renderFogOfWar() {
	Point heroLoc = lib.res() / 2;
	int radius = 8;
	vector<Point> circPoints;

	//Find the circumference of the circle around the hero
	Point prevPoint(0, 0);
	for (double rad = 0; rad < pi / 4; rad += 0.02) {
		double xTrig = (double)radius * cos(rad);
		double yTrig = (double)radius * sin(rad);
		int x = heroLoc.x() + xTrig;
		int y = heroLoc.y() + yTrig;
		Point p(x, y);
		if (p != prevPoint) {
			circPoints.push_back(p);
			prevPoint = p;
		}
	}

	for (int octant = 0; octant < 8; octant++) {
		for (unsigned int i = 0; i < circPoints.size(); i++) {
			drawBressenhamLine(octant, circPoints[i]);
		}
	}
}
void GameEngine::drawBressenhamLine(int octant, Point delta) {
	Point relLoc = screenOrientation - (lib.res() / 2);
	Point start = lib.res() / 2;
	Point end = delta;
	delta = end - start;

	int D = 2 * delta.y() - delta.x();
	int y = start.y();

	Point heroLoc = hero->getLoc();
	
	map[heroLoc.x()][heroLoc.y()].explore();
	map[heroLoc.x()][heroLoc.y()].setVisibility(true);

	for (int x = start.x() + 1; x < end.x(); x++) {
		Point rel;
		if (D > 0) {
			y += 1;
			rel = relLoc + switchOctant(octant, Point(x, y));

			if (map[rel.x()][rel.y()].getCellType() == 2)
				return;
			else {
				map[rel.x()][rel.y()].explore();
				map[rel.x()][rel.y()].setVisibility(true);
			}

			D += (2 * delta.y()) - (2 * delta.x());
		}
		else {
			rel = relLoc + switchOctant(octant, Point(x, y));

			if (map[rel.x()][rel.y()].getCellType() == 2)
				return;
			else {
				map[rel.x()][rel.y()].explore();
				map[rel.x()][rel.y()].setVisibility(true);
			}

			D += (2 * delta.y());
		}
	}
}
Point GameEngine::switchOctant(int octant, Point p) {	
	Point heroLoc = lib.res() / 2;

	switch (octant) {
		case 0: {
			return Point(p.x(), p.y());
		}
		case 1: {
			p = p - heroLoc;
			Point ret = Point(p.y(), p.x());
			ret = ret + heroLoc;
			return ret;
		}
		case 2: {
			p = p - heroLoc;
			Point ret(p.y(), p.x());
			ret = ret + heroLoc;
			ret.sety( ret.y() - 2*(ret.y() - heroLoc.y()) );
			return ret;
		}
		case 3: {
			Point ret = p;
			ret.setx(ret.x() - 2 * (ret.x() - heroLoc.x()));
			return ret;
		}
		case 4: {
			Point ret = p;
			ret.setx(ret.x() - 2 * (ret.x() - heroLoc.x()));
			ret.sety(ret.y() - 2 * (ret.y() - heroLoc.y()));
			return ret;
		}
		case 5: {
			p = p - heroLoc;
			Point ret(p.y(), p.x());
			ret = ret + heroLoc;
			ret.setx(ret.x() - 2 * (ret.x() - heroLoc.x()));
			ret.sety(ret.y() - 2 * (ret.y() - heroLoc.y()));
			return ret;
		}
		case 6: {
			p = p - heroLoc;
			Point ret(p.y(), p.x());
			ret = ret + heroLoc;
			ret.setx(ret.x() - 2 * (ret.x() - heroLoc.x()));
			return ret;
		}
		case 7: {
			Point ret = p;
			ret.sety(ret.y() - 2 * (ret.y() - heroLoc.y()));
			return ret;
		}
	}
}
void GameEngine::doBattle(Actor* atkr, Actor* atkd) {
	string heroHP = "HP: " + to_string(hero->getHP()) + "\n";
	lib.play("OnHit");

	int atkrDMG = atkr->getATK() - atkd->getActorDef().getDEF();
	int atkdDMG = atkd->getATK() - atkr->getActorDef().getDEF();

	atkr->doDMG(atkdDMG);
	string atkrEvent;
	if(atkrDMG > 0)
		atkrEvent = atkr->getActorDef().getDESC() + " attacked " + atkd->getActorDef().getDESC() + " for " + to_string(atkrDMG) + "!";
	else
		atkrEvent = atkr->getActorDef().getDESC() + " missed!";
	log.registerEvent(atkrEvent);

	atkd->doDMG(atkrDMG);
	string atkdEvent;
	if (atkrDMG > 0) {
		if (atkdDMG > 0)
			atkdEvent = atkd->getActorDef().getDESC() + " defended for " + to_string(atkdDMG) + "!";
		else
			atkdEvent = atkd->getActorDef().getDESC() + " couldn't defend!";
	}
	else
		atkdEvent = atkd->getActorDef().getDESC() + " missed!";
	log.registerEvent(atkdEvent);
	
	if (atkr->onDeath()) {
		if (atkr->isHero()) {
			lib.play("HeroOnDeath");
			killHero();
		}
		else
			killMonster(atkr->getLoc());
	}
	else if (atkd->onDeath()) {
		if (atkd->isHero()) {
			lib.play("HeroOnDeath");
			killHero();
		}
		else 
			killMonster(atkd->getLoc());
	}

	//Degrade armor / weapon
	invLog.degradeGear();
}

bool GameEngine::moveableCell(Point p) {
	Cell c = map[p.x()][p.y()];
	if (c.getCellType() != 2 && c.getActor() == NULL)
		return true;
	else
		return false;
}
void GameEngine::onPlayerTurn(bool b, Point p) {
	if (b) {
		//Increment turn
		log.incTurn();

		//Restore some mana
		if (turns % 3 == 0)
			hero->changeMana(1);

		//Move Player
		Point d = p;
		p = p + screenOrientation;
		if (moveableCell(p)) {
			screenOrientation = p;
			hero->setLoc(hero->getLoc() + d);

			int mapCellType = map[p.x()][p.y()].getCellType();
			if (mapCellType == 5)
				log.registerEvent("Press enter to descend stairs");
			else if (mapCellType == 6)
				log.registerEvent("Press enter to use Shop");
			else if (mapCellType == 7)
				log.registerEvent("A mysterious cave...press enter to descend");
			else if (mapCellType == 8)
				log.registerEvent("Press enter to ascend up the stairs");

			if (map[p.x()][p.y()].getPickup() != NULL)
				addPickup(p);
		}
		else if (map[p.x()][p.y()].getActor() != NULL)
			doBattle(hero, map[p.x()][p.y()].getActor());

		//Move AI
		if (!inBossRoom) {
			for (unsigned int i = 0; i < monsters.size(); i++) {
				Point mLoc = monsters[i]->getLoc();
				Actor* m = map[mLoc.x()][mLoc.y()].getActor();
				if (moveAI(m))
					doBattle(m, hero);
			}
		}
		turns++;
	}
}
bool GameEngine::moveAI(Actor* monster) {
	//Death Curse damage
	if (monster->getSpell().getSpellType() == 5) {
		monster->doDMG(3);
		if (monster->getHP() <= 0)
			killMonster(monster->getLoc());
	}

	Point heroLoc = hero->getLoc();
	Point loc = monster->getLoc();
	int xDist = heroLoc.x() - loc.x();
	int yDist = heroLoc.y() - loc.y();
	int which = 0;

	Point dir(0, 0);

	//Choose direction
	if (xDist == 0 && yDist == 0)
		dir = Point(0, 0);
	else if (xDist == 0 && yDist != 0)
		dir = Point(0, yDist / abs(yDist));
	else if (xDist != 0 && yDist == 0)
		dir = Point(xDist / abs(xDist), 0);
	else if (xDist != 0 && yDist != 0)
		dir = Point(xDist / abs(xDist), yDist / abs(yDist));


	//Move monster based on whether it's close enough to the hero or not
	if (abs(xDist) + abs(yDist) < 5) {
		loc = loc + pickAIPoint(monster, dir, false);
		monster->gettingTired();
	}
	else
		loc = loc + pickAIPoint(monster, dir, true);

	//Don't move the monster if it's next to the hero, make it attack
	if (Point(abs(xDist), abs(yDist)) == Point(0, 1) || Point(abs(xDist), abs(yDist)) == Point(1, 0))
		return true; //Is going to attack hero
	else {
		//Update loc in map grid
		try {
			if (loc > Point(0, 0) && loc < Point(63, 63)) {
				if (moveableCell(map[loc.x()][loc.y()].getLoc())) {
					if (!monster->isTired()) {
						if (map[monster->getLoc().x()][monster->getLoc().y()].getSpell().getSpellType() != 4) { //If monster is in ice block, don't move
							//Move the monster
							map[monster->getLoc().x()][monster->getLoc().y()].setActor(NULL);
							monster->setLoc(loc);
							map[loc.x()][loc.y()].setActor(monster);
						}

						if (map[loc.x()][loc.y()].getSpell().getSpellType() == 1) { //Field of fire, damage monster if they're in the spell
							monster->doDMG(2);
							if (monster->getHP() <= 0)
								killMonster(monster->getLoc());
						}
						else if (map[loc.x()][loc.y()].getSpell().getSpellType() == 6) {
							monster->doDMG(10);
							log.registerEvent(monster->getActorDef().getDESC() + " triggered Fist of Katar!");
							if (monster->getHP() <= 0)
								killMonster(monster->getLoc());
							map[loc.x()][loc.y()].setSpell(Spell());
						}
					}
				}
			}
		}
		catch (int e) {
			OutputDebugString(to_string(e).c_str());
		}
		return false;
	}
}
Point GameEngine::pickAIPoint(Actor* monster, Point dir, bool random) {
	int which = 0;
	if (!random) {
		which = rand() % 2;

		if (dir.x() != 0 && dir.y() != 0) {
			switch (which) {
				case 0:
					return Point(dir.x(), 0);
					break;
				case 1:
					return Point(0, dir.y());
					break;
				default:
					return Point(0, 0);
			}
		}
		else
			return dir;
	} 
	else {
		which = rand() % 4;

		//Add home hovering here
		if (monster->getLoc() < monster->getHome() + Point(3, 3)) {
			which = rand() % 2;

			switch (which) {
			case 0:
				return Point(1, 0);
			case 1:
				return Point(0, 1);
			}
		}
		else if (monster->getLoc() > monster->getHome() + Point(3, 3)) {
			which = rand() % 2;

			switch (which) {
			case 0:
				return Point(-1, 0);
			case 1:
				return Point(0, -1);
			}
		}
		else if (monster->getLoc() == monster->getHome()) {
			return pickRandomPoint();
		}
		else
			return pickRandomPoint();
	}
}
Point GameEngine::pickRandomPoint() {
	int which = rand() % 4;
	switch (which) {
	case 0:
		return Point(1, 0);
		break;
	case 1:
		return Point(0, 1);
		break;
	case 2:
		return Point(-1, 0);
		break;
	case 3:
		return Point(0, -1);
		break;
	default:
		return Point(0, 0);
	}
}

void GameEngine::killMonster(Point loc) {
	Actor* monster = map[loc.x()][loc.y()].getActor();
	int xp = monster->getActorDef().getXP();

	//Kill off the monster
	if (monster->isBoss()) {

		log.registerEvent(map[loc.x()][loc.y()].getActor()->getActorDef().getDESC() + " HAS FALLEN!");

		//Add pickups to the map where boss died
		Point start = boss->getLoc() + Point(-1, -1);
		Point end = boss->getLoc() + Point(2, 1);
		lib.loop_portion(start, end, [&](Point p) {
			PickupDef def;
			if (p == boss->getLoc())
				def = pickfromtable<PickupDef>(legendarydefs);
			else
				def = pickfromtable<PickupDef>(pickupdefs);
			pickups.push_back(new Pickup(def, p));
			map[p.x()][p.y()].setPickup(pickups.back());
		});

		bossIsDead = true;
		map[loc.x()][loc.y()].setActor(NULL);
		delete boss;

		lib.play("OnBossDeath");
	}
	else {
		unsigned int idx;
		for (idx = 0; idx < monsters.size(); idx++) {
			if (monsters[idx]->getLoc() == loc)
				break;
		}
		delete monsters[idx];
		monsters.erase(monsters.begin() + idx);

		//Give them a chance to drop a pickup
		PickupDef def = pickfromtable<PickupDef>(pickupdefs);
		pickups.push_back(new Pickup(def, loc));
		map[loc.x()][loc.y()].setPickup(pickups.back());

		map[loc.x()][loc.y()].setActor(NULL);

		lib.play("OnDeath");
	}

	//Give XP
	invLog.enemyKilled(xp);
}
void GameEngine::killHero() {
	deadHero = true;
	log.registerEvent("PRESS ESCAPE TO EXIT");
	lib.play("HeroOnDeath");
}
void GameEngine::addPickup(Point loc) {
	int idx = 0;
	bool itemAdded = false;

	//Add the new item to inventory log
	for (unsigned int i = 0; i < pickups.size(); i++) {
		if (pickups[i]->getLoc() == loc) {
			itemAdded = invLog.addItem(*pickups[i]);
			idx = i;
			break;
		}
	}

	//Add to log
	if (itemAdded) {
		log.registerEvent("Picked up a " + pickups[idx]->getPickupDef().getName() + "!");

		//Delete it from the game world
		map[loc.x()][loc.y()].setPickup(NULL);
		delete pickups[idx];
		pickups.erase(pickups.begin() + idx);
	}
	else
		log.registerEvent("Inventory full!");
}

Pickup GameEngine::registerInventoryClick() {
	int relX = lib.res().x() - 3;
	if ((lib.mouseLoc().x() == relX || lib.mouseLoc().x() == relX + 1) && lib.mouseLoc().y() >= 3 && lib.mouseLoc().y() <= 9) {
		if (!invLog.itemAlreadyEquipped(lib.mouseLoc()))
			return invLog.useItem(lib.mouseLoc());
		else if(invLog.getInvItemAtLoc(lib.mouseLoc()).getLoc() != Point(-1, -1)) {
			string event = "A " + invLog.getInvItemAtLoc(lib.mouseLoc()).getPickupDef().getTypeName() + " is already equipped!";
			log.registerEvent(event.c_str());
		}
	}
	return Pickup();
}

void GameEngine::onMouseOver() {

	//Render inventory item information
	if (lib.mouseLoc().x() > lib.res().x() - 4) {
		Pickup item = invLog.getItemAtLoc(lib.mouseLoc());

		if (item.getLoc() != Point(-1, -1)) {
			if (item.getPickupDef().getType() != 0)
				log.renderMouseOver(item.getPickupDef().getName(), item.getPickupDef().getDESC(), "Uses left: " + to_string(item.getUsesLeft()), "");
			else
				log.renderMouseOver(item.getPickupDef().getName(), item.getPickupDef().getDESC(), "", "");
		}
	}

	//Render world information
	else {
		Point relMouseLoc = screenOrientation - lib.res() / 2 + lib.mouseLoc();

		if (relMouseLoc.x() > 0 && relMouseLoc.y() > 0 && relMouseLoc.x() <= worldSize - 1 && relMouseLoc.y() <= worldSize - 1 && !shop.isShopping()) {
			if (!map[relMouseLoc.x()][relMouseLoc.y()].isVisible()) {
				Pickup* p = map[relMouseLoc.x()][relMouseLoc.y()].getPickup();
				Actor* a = map[relMouseLoc.x()][relMouseLoc.y()].getActor();

				if (a != NULL)
					log.renderMouseOver(a->getActorDef().getDESC(), "HP: " + to_string(a->getHP()), "ATK: " + a->getActorDef().actorATK().to_str(), "DEF: " + to_string(a->getActorDef().getDEF()));
				else if (p != NULL) {
					if (p->getPickupDef().getType() != 0)
						log.renderMouseOver(p->getPickupDef().getName(), p->getPickupDef().getDESC(), "Uses left: " + to_string(p->getUsesLeft()), "");
					else
						log.renderMouseOver(p->getPickupDef().getName(), p->getPickupDef().getDESC(), "", "");
				}
			}
		}
	}
	tl_scale(1);
}

//Spell stuff
void GameEngine::useSpell(Point mouseLoc) {
	Spell spell = invLog.getSpell(mouseLoc);

	if (spell.isUnlocked()) {
		if (hero->getMana() < spell.getCost())
			log.registerEvent("Not enough mana!");
		else {
			log.registerEvent(spell.getTitle() + " activated!");

			Point start = hero->getLoc() + Point(-1, -1);
			Point end = hero->getLoc() + Point(2, 2);

			int type = spell.getSpellType();
			switch (type) {
				case 1: //Field of fire
				{
					spell.setTurnActivated(turns);

					lib.loop_portion(start, end, [&](Point p) {
						map[p.x()][p.y()].setSpell(spell);
					});
					break;
				}
				case 2: //Death Rattle
				{
					lib.loop_portion(start, end, [&](Point p) {
						Actor* a = map[p.x()][p.y()].getActor();

						if (a != NULL) {
							Point relToHero = p - hero->getLoc();
							Point d(p.x() + relToHero.x(), p.y() + relToHero.y());
							
							a->doDMG(2);
							if (a->getHP() <= 0)
								killMonster(a->getLoc());

							if (moveableCell(d)) {
								map[p.x()][p.y()].setActor(NULL);
								a->setLoc(d);
								map[d.x()][d.y()].setActor(a);
							}
						}
					});
					break;
				}
				case 3: //Blessing of Katar
				{
					hero->changeHP(10);
					break;
				}
				case 4: //Ice Block
				{
					spell.setTurnActivated(turns);

					lib.loop_portion(start, end, [&](Point p) {
						map[p.x()][p.y()].setSpell(spell);
					});
					break;
				}
				case 5: //Death Curse
				{
					spell.setTurnActivated(turns);

					lib.loop_portion(start, end, [&](Point p) {
						Actor* a = map[p.x()][p.y()].getActor();
						if (a != NULL) {
							a->setSpell(spell);
						}
					});
					break;
				}
				case 6: //Fist of Katar
				{
					map[hero->getLoc().x()][hero->getLoc().y()].setSpell(spell);
					break;
				}
			}

			hero->changeMana(-spell.getCost());
			lib.play("Spell" + to_string(spell.getSpellType()));
		}
	}
}

void GameEngine::enterBossRoom() {
	//Scare the player
	log.registerEvent("WHO DARES ENTER MY REALM?!");
	log.registerEvent(boss->getActorDef().getDESC() + ":");
	lib.play("BossRoomEnter");

	//Add the stairs back up to the level
	stairAscend = Point(5, 7);
	Cell stair(stairAscend, 8, 0x18B, -1);
	bossMap[stair.getLoc().x()][stair.getLoc().y()] = stair;

	//Convert map data to the boss room map data
	mapHold = map;
	map = bossMap;

	worldSizeHold = worldSize;
	worldSize = bossMapSize;

	pickupsHold = pickups;
	pickups = bossRoomPickups;

	//Change the hero's location
	screenOrientation = Point(5, 5);
	hero->setLoc(screenOrientation);

	inBossRoom = true;
}
void GameEngine::leaveBossRoom() {
	//Delete stairs back up to the level
	stairAscend = Point();

	//Convert map data back to level map data
	map = mapHold;
	worldSize = worldSizeHold;
	bossRoomPickups = pickups;
	pickups = pickupsHold;

	mapHold.clear();
	pickupsHold.clear();

	//Set the hero's location back
	screenOrientation = bossLoc;
	hero->setLoc(screenOrientation);

	inBossRoom = false;
}