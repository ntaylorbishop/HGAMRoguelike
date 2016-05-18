#include "InventoryLog.h"

void InventoryLog::init(TileLibrary* library, Hero* hero, MessageLog* log) {
	this->lib = library;
	this->hero = hero;
	this->log = log;
	maxSize = 14;
	gearBoxSize = 15;
	highlight_color = 0x0A0091FF;
	numGear = 9;

	for (int i = 0; i < maxSize; i++)
		inventory.push_back(Pickup());
	for (int i = 0; i < numGear; i++)
		gear.push_back(Pickup());

	gearSlotIcons = { 0x2DD, 0x337, 0x2D0, 0x2E7, 0x2E0, 0x3D0, 0x250, 0x2C0 };
	spells = {spell1, spell2, spell3, spell4, spell5, spell6 };
}
bool InventoryLog::addItem(Pickup item) {
	if (isInventoryFull())
		return false;
	else {
		lib->play("OnPickup");
		for (unsigned int i = 0; i < inventory.size(); i++) {
			if (inventory[i].getLoc() == Point(-1, -1)) {
				inventory[i] = item;
				return true;
			}
		}
	}
	return false;
}
void InventoryLog::renderInventory() {
	//Render background
	lib->loop_portion(Point(lib->res().x() - 4, 0), Point(lib->res().x(), lib->res().y() - 2), [&](Point p) {
		lib->rendertile(0x125, p);
		tl_color(0xFFFFFF40);
		lib->rendertile(0x125, p);
		tl_color(0xFFFFFFFF);
	});

	//Render items
	unsigned int idx = 0;

	lib->loop_portion_reverse(Point(lib->res().x() - 3, 3), Point(lib->res().x() - 1, maxSize / 2 + 3), [&](Point p) {
		lib->rendertile(0x13D, p);
		if (lib->mouseLoc() == p && inventory[idxFromPoint(lib->mouseLoc())].getLoc() != Point(-1, -1)) {
			tl_color(0xFF000040);
			lib->rendertile(0x13D, p);
		}
		tl_color(0xFFFFFFFF);
		if (idx <= inventory.size() - 1 && !inventory.empty()) {
			lib->rendertile(inventory[idx].getPickupDef().getTile(), p);
			idx++;
		}
	});

	//RENDER TEXT
	lib->tile_scale(3);

	lib->renderText(Point(lib->res().x() - 11, 1), "HP:" + to_string(hero->getHP()) + "/" + to_string(hero->getActorDef().getMaxHP())); //Render HP
	lib->renderText(Point(lib->res().x() - 11, 2), "MN:" + to_string(hero->getMana()) + "/" + to_string(hero->getMaxMana())); //Render HP
	lib->renderText(Point(lib->res().x() - 11, 3), "ATK: " + hero->getActorDef().actorATK().to_str()); //Render ATK
	lib->renderText(Point(lib->res().x() - 11, 4), "DEF:" + to_string(hero->getActorDef().getDEF())); //Render DEF
	lib->renderText(Point(lib->res().x() - 11, 5), "Gold: " + to_string(goldAmount)); //Render gold

	lib->renderText(Point(lib->res().x() - 11, 7), "INVENTORY"); //Render inventory text
	lib->renderText(Point(lib->res().x() - 11, 32), "EQUIPMENT"); //Render equipment text

	lib->renderText(Point(lib->res().x() - 11, 50), "LEVEL: " + to_string(lvl)); //Render level
	lib->renderText(Point(lib->res().x() - 11, 51), "XP: " + to_string(xp) + "/" + to_string(toNextLvl)); //Render XP
	lib->tile_scale(1);

	renderGear();
	renderSpells();
}
Pickup InventoryLog::useItem(Point loc) {
	int idx = idxFromPoint(loc);
	int itemType = inventory[idx].getPickupDef().getType();
	Pickup itemUsed = inventory[idx];

	if (itemType != 0 && inventory[idx].getLoc() != Point(-1, -1)) {
		lib->play("OnUse");
		gear[itemType] = inventory[idx];
		gear[itemType].getPickupDef().useEffect();
		inventory[idx] = Pickup();
	}
	else {
		lib->play("OnUse");
		inventory[idx].getPickupDef().useEffect();
		inventory[idx] = Pickup();
	}

	return itemUsed;
}

int InventoryLog::idxFromPoint(Point loc) {
	loc = loc - Point(lib->res().x() - 3, 3);
	if (loc >= Point(0, 0) && loc <= Point(1, 6))
		return loc.x() + loc.y() * 2;
	else
		return -1;
}
bool InventoryLog::isInventoryFull() {
	int trueSize = 0;
	for (unsigned int i = 0; i < inventory.size(); i++) {
		if (inventory[i].getLoc() != Point(-1, -1))
			trueSize++;
	}
	if (trueSize == maxSize)
		return true;
	else
		return false;
}

int InventoryLog::getItemType(Point loc) {
	return inventory[idxFromPoint(loc)].getPickupDef().getType();
}

void InventoryLog::renderGear() {
	OutputDebugString(lib->mouseLoc().to_str().c_str());
	OutputDebugString("\n");
	tl_color(0xFFFFFFFF);
	Point gearStart = Point(lib->res().x() - 3, 12);
	Point gearEnd = Point(lib->res().x() - 1, 16);

	//Render gear slots
	int idx = 0;
	lib->loop_portion_reverse(gearStart, gearEnd, [&](Point p) {
		lib->rendertile(0x13D, p);
		idx++;

		if (lib->mouseLoc() == p) {
			tl_color(0xFF000040);
			lib->rendertile(0x13D, p);
			tl_color(0xFFFFFFFF);
		}
		if (gear[idx].getLoc() != Point(-1, -1)) //Render the gear if it exists
			lib->rendertile(gear[idx].getPickupDef().getTile(), p);
		else { //Render the background icon if it doesn't
			tl_color(0x00000060);
			lib->rendertile(gearSlotIcons[idx - 1], p);
		}
		tl_color(0xFFFFFFFF);
	});
}
void InventoryLog::degradeGear() {
	int which = rand() % 8 + 1;
	if (gear[which].getLoc() != Point(-1, -1)) { //Gear exists, so degrade it
		gear[which].degrade();
		if (gear[which].getUsesLeft() == 0) {
			lib->play("OnBreak");
			log->registerEvent(gear[which].getPickupDef().getName() + " broke!");
			gear[which].getPickupDef().removeEffect();
			gear[which] = Pickup();
		}
	}
}

Pickup InventoryLog::unequipGear(Point loc) {
	Pickup pGear;
	int idx = 0;
	Point gearStart = Point(lib->res().x() - 3, 12);
	Point gearEnd = Point(lib->res().x() - 1, 16);

	lib->loop_portion_reverse(gearStart, gearEnd, [&](Point p) {
		idx++;

		if (loc == p) {
			lib->play("UnequipGear");
			//Remove from equipment
			pGear = gear[idx];
			gear[idx] = Pickup();

			pGear.getPickupDef().removeEffect();

			//Add it back to inventory
			for (unsigned int j = 0; j < inventory.size(); j++) {
				if (inventory[j].getLoc() == Point(-1, -1)) {
					inventory[j] = pGear;
					break;
				}
			}
		}
	});

	return pGear;
}
Pickup InventoryLog::dropItem(Point loc) {
	int idx = idxFromPoint(loc);
	Pickup p;

	if (idx != -1) {
		p = inventory[idx];
		inventory[idx] = Pickup();
	}

	lib->play("DropItem");
	return p;
}

bool InventoryLog::itemAlreadyEquipped(Point loc) {
	Pickup p = getInvItemAtLoc(loc);

	bool b = false;
	for (int i = 0; i < 8; i++) {
		if (p.getPickupDef().getType() == gear[i + 1].getPickupDef().getType())
			b = true;
	}
	return b;
}
Pickup InventoryLog::getInvItemAtLoc(Point loc) {
	Pickup p;
	int idx = idxFromPoint(loc);

	if (idx != -1)
		p = inventory[idx];
	return p;
}

int InventoryLog::overInvOrGear(Point mouseLoc) {
	if (mouseLoc >= Point(lib->res().x() - 3, 3) && mouseLoc <= Point(lib->res().x() - 1, maxSize / 2 + 3))
		return 0;
	else if (mouseLoc >= Point(lib->res().x() - 3, 12) && mouseLoc <= Point(lib->res().x() - 1, 16))
		return 1;
	else
		return 2;
}

Pickup InventoryLog::getItemAtLoc(Point loc) {
	int gearX1 = lib->res().x() - 3;
	int gearX2 = lib->res().x() - 2;

	if (loc > Point(gearX1, 3) && loc < Point(gearX2 + 1, maxSize / 2 + 3)) return getInvItemAtLoc(loc);
	else if (loc == Point(gearX1, 12)) return gear[1];
	else if (loc == Point(gearX2, 12)) return gear[2];
	else if (loc == Point(gearX1, 13)) return gear[3];
	else if (loc == Point(gearX2, 13)) return gear[4];
	else if (loc == Point(gearX1, 14)) return gear[5];
	else if (loc == Point(gearX2, 14)) return gear[6];
	else if (loc == Point(gearX1, 15)) return gear[7];
	else if (loc == Point(gearX2, 15)) return gear[8];
	else                               return Pickup();
}

int InventoryLog::getGold() {
	return goldAmount;
}
void InventoryLog::changeGold(int amount) {
	goldAmount += amount;
}

Pickup InventoryLog::sellItem(Point loc) {
	int idx = idxFromPoint(loc);
	Pickup p = inventory[idx];
	inventory[idx] = Pickup();
	return p;
}

void InventoryLog::enemyKilled(int xp) {
	this->xp += xp;

	//Check to see if leveled up
	if (this->xp >= toNextLvl)
		levelUp();
}
void InventoryLog::levelUp() {
	lib->play("LevelUp");
	xp = 1;
	lvl++;
	toNextLvl = lvl * 10;

	hero->changeDEF(1);
	hero->changeMaxHP(5);
	hero->changeHP(hero->getActorDef().getMaxHP());
	hero->changeMaxMana(10);
	hero->changeMana(hero->getMaxMana());

	for (unsigned int i = 0; i < spells.size(); i++) {
		if (lvl == spells[i].getReqLvl())
			spells[i].unlock();
	}

	log->registerEvent("Hero leveled up! Now at level " + to_string(lvl));
}

void InventoryLog::renderSpells() {
	tl_scale(1);

	int idx = 0;
	int xStart = lib->res().x() / 2 - 3;
	int xEnd = lib->res().x() / 2 + 3;

	for (int x = xStart; x < xEnd; x++) {
		Point p(x, lib->res().y() - 4);

		lib->rendertile(0x13D, p);
		if (lib->mouseLoc() == p) {
			if (spells[idx].isUnlocked()) {
				tl_color(0xFF000040);
				lib->rendertile(0x13D, p);
				lib->rendertile(spells[idx].getIcon(), p);
				tl_color(0xFFFFFFFF);
				log->renderMouseOver(spells[idx].getTitle(), spells[idx].getDesc(), "Cost: " + to_string(spells[idx].getCost()), "");
			}
			else
				log->renderMouseOver(spells[idx].getTitle(), spells[idx].getDesc(), "Required Level: " + to_string(spells[idx].getReqLvl()), "");
		}
		if (!spells[idx].isUnlocked())
			tl_color(0x00000060);
		lib->rendertile(spells[idx].getIcon(), p);
		tl_color(0xFFFFFFFF);

		idx++;
	}
}
Spell InventoryLog::getSpell(Point mouseLoc) {
	return spells[mouseLoc.x() - 9];
}