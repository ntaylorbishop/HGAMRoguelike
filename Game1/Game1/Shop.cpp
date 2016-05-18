#include "Shop.h"

Shop::Shop() {

}
Shop::Shop(Point loc, int difficulty, vector<PickupDef> potItems, TileLibrary* lib, Hero* hero, MessageLog* log, InventoryLog* invLog) {
	this->loc = loc;
	this->difficulty = difficulty;
	this->potItems = potItems;
	this->lib = lib;
	this->hero = hero;
	this->log = log;
	this->invLog = invLog;

	start = Point(2, 2);
	end = Point(lib->res().x() - 6, lib->res().y() - 4);

	//Fill the store
	int which = 0;
	lib->loop_portion_reverse(start + Point(5, 5), end + Point(-5, -5), [&](Point p) {
		which = rand() % potItems.size();
		storeItems.push_back(Pickup(potItems[which], p));
	});
}
void Shop::renderShop() {
	if (shopOpen) {
		//Render the background
		lib->loop_portion(start, end, [&](Point p) {
			lib->rendertile(0x125, p);
		});
		//Render the close button
		if (lib->mouseLoc() == start) //Highlight if mouse is over close button
			tl_color(0x000000FF);
		lib->rendertile(static_cast<int>('x'), start);
		tl_color(0xFFFFFFFF);

		//If close button is hit, close the shop
		if (tl_buttonwentdown(1) && lib->mouseLoc() == start)
			shopOpen = false;
		
		tl_scale(2);
		lib->renderText(Point(start.x() + 6, start.y() + 3), "Well Hello There, Stranger!"); //Compensate start point with scale
		lib->renderText(Point(start.x() + 10, end.y() + 12), "Gold Amount: " + to_string(shopGold));
		tl_scale(1);

		//Render icon slots
		unsigned int idx = 0;
		Point iconStart = start + Point(5, 5);
		Point iconEnd = end + Point(-5, -5);
		lib->loop_portion(iconStart, end + Point(-5, -5), [&](Point p) {
			lib->rendertile(0x13D, p);
			if (lib->mouseLoc() == p && storeItems[idx].getLoc() != Point(-1, -1)) {
				tl_color(0xFF000040);
				lib->rendertile(0x13D, p);
			}
			tl_color(0xFFFFFFFF);
			if (storeItems[idx].getLoc() != Point(-1, -1))
				lib->rendertile(storeItems[idx].getPickupDef().getTile(), p);
			idx++;
		});

		if (lib->mouseLoc() >= iconStart && lib->mouseLoc() <= iconEnd - Point(1, 1)) {
			//Render item mouse over
			Pickup p = storeItems[idxFromPoint(lib->mouseLoc() - iconStart)];
			Point loc = lib->mouseLoc() - iconStart;

			if (p.getLoc() != Point(-1, -1)) {
				if (p.getPickupDef().getType() != 0)
					log->renderMouseOver(p.getPickupDef().getName(), p.getPickupDef().getDESC(), "Uses left: " + to_string(p.getUsesLeft()), "Cost: " + to_string(p.getPickupDef().getPrice()));
				else
					log->renderMouseOver(p.getPickupDef().getName(), p.getPickupDef().getDESC(), "Cost: " + to_string(p.getPickupDef().getPrice()), "");
			}
			//Buy item
			if (tl_buttonwentdown(1))
				buy(loc);
		}
		else if (lib->mouseLoc() >= Point(lib->res().x() - 3, 3) && lib->mouseLoc() <= Point(lib->res().x() - 2, 9)) {
			if (tl_buttonwentdown(1)) {
				Pickup p = invLog->sellItem(lib->mouseLoc());
				sell(p);
			}
		}
	}
}

void Shop::buy(Point loc) {
	int idx = idxFromPoint(loc);
	Pickup itemToBuy = storeItems[idx];
	int price = itemToBuy.getPickupDef().getPrice();

	if (invLog->getGold() >= price && !invLog->isInventoryFull()) { //Make sure hero has enough cash and inv isn't full
		invLog->addItem(itemToBuy);
		storeItems[idx] = Pickup();
		invLog->changeGold(-price);
		log->registerEvent("Bought a " + itemToBuy.getPickupDef().getName() + " for " + to_string(price));
		lib->play("Buy");
	}
	else {
		log->registerEvent("Not enough gold!");
		lib->play("CantBuy");
	}
}
void Shop::sell(Pickup p) {
	if (p.getLoc() != Point(-1, -1)) { //Make sure we're actually selling an item
		//Add it to the store if there's room
		for (unsigned int i = 0; i < storeItems.size(); i++) {
			if (storeItems[i].getLoc() == Point(-1, -1)) {
				storeItems[i] = p;
				break;
			}
		}

		//Decrement gold, add it to the player
		int price = p.getPickupDef().getPrice();
		invLog->changeGold(price);
		shopGold -= price;
		lib->play("Sell");
		log->registerEvent("Sold a " + p.getPickupDef().getName() + " for " + to_string(price) + " gold");
	}
}

void Shop::activateShop() {
	 shopOpen = true;
}
bool Shop::isShopping() {
	return shopOpen;
}
//Getters / setters
Point Shop::getLoc() {
	return loc;
}
void Shop::setLoc(Point nLoc) {
	loc = nLoc;
}
int Shop::getTile() {
	return tile;
}

//Utility
int Shop::idxFromPoint(Point loc) {
	//Point p = loc - (start + Point(5, 5));
	return loc.y() + loc.x() * 5;
}