using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine.EventSystems;
using Random = UnityEngine.Random;

public class GameEngine : MonoBehaviour {
	private TileLibrary lib;
	private List<List<GameObject>> map;
	private List<Point> playableMap;
	private int worldSize = 256;
	private Hero hero;
	private int xStart, xEnd, yStart, yEnd;
	private List<Actor> monsters;
    private MessageLog log;
    private InventoryLog invLog;
    private bool deadHero = false;
    public List<PickupDef> pickupDefs;
    public List<Pickup> pickups;
    int currLevel = 0;
    int activeSlot = -1;

	//Monster table
	public List<ActorDef> monsterDefs = new List<ActorDef> {
		new ActorDef(new Dice(3, 3), 0, 20, 183, "Mutated rat",          1),
		new ActorDef(new Dice(3, 3), 0, 20, 189, "Big spider",           1),
		new ActorDef(new Dice(3, 3), 0, 20, 94, "Angry ant",             1),
		new ActorDef(new Dice(3, 3), 0, 20, 95, "Giant bee",             1),
		new ActorDef(new Dice(4, 2), 0, 20, 98, "Dung beetle",           1),
		new ActorDef(new Dice(3, 3), 0, 20, 100, "Rattlesnake",          1),
		new ActorDef(new Dice(2, 2), 1, 30, 106, "Rabid dingo",          1),
		new ActorDef(new Dice(4, 3), 2, 30, 107, "Mama fox",             1),
		new ActorDef(new Dice(4, 3), 1, 30, 122, "Mutated plant",        1),
		new ActorDef(new Dice(4, 3), 1, 30, 131, "Young wolf",           1),
		
		new ActorDef(new Dice(4, 5), 2, 40, 184, "Giant mutated rat",    2),
		new ActorDef(new Dice(4, 5), 2, 40, 190, "Mutated tarantula",    2),
		new ActorDef(new Dice(4, 5), 2, 40, 97, "Mutated fire aunt",     2),
		new ActorDef(new Dice(4, 5), 2, 40, 99, "Giant Mutated hornet",  2),
		new ActorDef(new Dice(4, 6), 2, 40, 118, "Snow wolf",            2),
		new ActorDef(new Dice(4, 6), 2, 50, 115, "Werewolf",             2),
		new ActorDef(new Dice(5, 6), 3, 50, 108, "Hyena",                3),
		new ActorDef(new Dice(5, 6), 3, 50, 123, "Eye of D'jinn",        3),
		new ActorDef(new Dice(5, 6), 3, 50, 121, "Cerberus wolf",        3),
		new ActorDef(new Dice(5, 6), 3, 50, 127, "Tentacle monster",     3)
	};

	//init
	void Start() {
        currLevel = 1;
		map = new List<List<GameObject>>();
		playableMap = new List<Point> ();
		monsters = new List<Actor>();
        pickups = new List<Pickup>();
        lib = new TileLibrary();
        log = new MessageLog();
        invLog = new InventoryLog();

		//Initialize the map
		for (int x = 0; x < worldSize; x++) {
			map.Add(new List<GameObject>());
			for(int y = 0; y < worldSize; y++) {
				GameObject go = lib.createTile (209, new Point(x, y), 0);
				map[x].Add ((GameObject)go);
				map[x][y].gameObject.GetComponent<Cell>().setCell(new Point(x,y), 2, 209, 0);
			}
		}

        ActorDef main = new ActorDef(new Dice(3, 4), 1, 1000, 138, "The hero", 1);
        hero = new Hero(main, lib.createTile (138, new Point(0, 0), 0), new Point(0, 0));

        pickupDefs = new List<PickupDef> {
		    //health pots
		    new PickupDef(414, "Small Health Potion", "Restores 10 HP", 1, 100, delegate { hero.changeHP(10); }),
		    new PickupDef(428, "Big Health Potion", "Restores 20 HP", 2, 200, delegate { hero.changeHP(20); }),
		    new PickupDef(407, "Large Health Potion", "Restores 30 HP", 3, 300, delegate { hero.changeHP(30); }),

		    //mana pots
		    new PickupDef(417, "Small Mana Potion", "Restores 5 mana", 1, 100, delegate { hero.changeMana(5); }),
		    new PickupDef(431, "Mana Potion", "Restores 10 mana", 2, 100, delegate { hero.changeMana(10); }),
		    new PickupDef(410, "Large Mana Potion", "Restores 20 mana", 3, 300, delegate { hero.changeMana(20); }),

		    //helms
		    new PickupDef(572, "Crude Helmet", "Increases defense by 1", 1, 5, 1, 100, delegate { hero.changeDEF(1); }, delegate { hero.changeDEF(-1); }),
		    new PickupDef(573, "Steel Helmet", "Increases defense by 2", 1, 5, 2, 200, delegate { hero.changeDEF(2); }, delegate { hero.changeDEF(-2); }),
		    new PickupDef(570, "Magician's Hat", "Increases max health by 10", 1, 5, 4, 400, delegate { hero.changeMaxHP(10); }, delegate { hero.changeMaxHP(-10); }),

		    //necks
		    new PickupDef(652, "Worn Necklace", "Increases max health by 5", 2, 10, 1, 100, delegate { hero.changeMaxHP(5); }, delegate { hero.changeMaxHP(-5); }),
		    new PickupDef(653, "Fine Necklace", "Increases defense by 2", 2, 5, 2, 200, delegate { hero.changeDEF(2); }, delegate { hero.changeDEF(-2); }),
		    new PickupDef(656, "Cross of Al'tair", "Increases defense by 4", 2, 5, 4, 400, delegate { hero.changeDEF(4); }, delegate { hero.changeDEF(-4); }),

		    //shirts
		    new PickupDef(561, "Tattered Shirt", "Increases max health by 5", 3, 5, 1, 100, delegate { hero.changeMaxHP(5); }, delegate { hero.changeMaxHP(-5); }),
		    new PickupDef(562, "Gold Chainmail", "Increases max health by 10", 3, 5, 2, 200, delegate { hero.changeMaxHP(10); }, delegate { hero.changeMaxHP(-10); }),
		    new PickupDef(563, "Vest of the Thief's Guild", "Increases defense by 3", 3, 5, 4, 400, delegate { hero.changeDEF(3); }, delegate { hero.changeDEF(-3); }),

		    //gloves
		    new PickupDef(582, "Worn Leather Glove", "Increases defense by 1", 4, 4, 1, 100, delegate { hero.changeDEF(1); }, delegate { hero.changeDEF(-1); }),
		    new PickupDef(584, "Chainmail Glove", "Increases defense by 2", 4, 4, 2, 200, delegate { hero.changeDEF(2); }, delegate { hero.changeDEF(-2); }),
		    new PickupDef(583, "Glove of the Magi", "Increases max health by 10", 4, 4, 4, 400, delegate { hero.changeMaxHP(10); }, delegate { hero.changeMaxHP(-10); }),

		    //shoes
		    new PickupDef(575, "Smelly Old Shoe", "Increases defense by 1", 5, 5, 1, 100, delegate { hero.changeDEF(1); }, delegate { hero.changeDEF(-1); }),
		    new PickupDef(576, "Fine Leather Shoe", "Increases defense by 2", 5, 5, 2, 200, delegate { hero.changeDEF(2); }, delegate { hero.changeDEF(-2); }),
		    new PickupDef(578, "Knight's Boot", "Increases defense by 3", 5, 5, 4, 400, delegate { hero.changeDEF(3); }, delegate { hero.changeDEF(-3); }),

		    //journals
		    new PickupDef(785, "Standard Spell Journal", "Increases max health by 5", 6, 10, 1, 100, delegate { hero.changeMaxHP(5); }, delegate { hero.changeMaxHP(-5); }),
		    new PickupDef(786, "Mage's Necronomicon", "Increases max health by 7", 6, 10, 2, 200, delegate { hero.changeMaxHP(7); }, delegate { hero.changeMaxHP(-7); }),
		    new PickupDef(789, "Death Note", "Increases max health by 9", 6, 10, 4, 400, delegate { hero.changeMaxHP(9); }, delegate { hero.changeMaxHP(-9); }),

		    //swords
		    new PickupDef(463, "Crude Dagger", "Attack: (2, 14)", 7, 5, 1, 100, delegate { hero.changeATK(new Dice(7, 2)); }, delegate { hero.revertATK(); }),
		    new PickupDef(449, "Fine Longsword", "Attack: (3, 15)", 7, 5, 2, 200, delegate { hero.changeATK(new Dice(5, 3)); }, delegate { hero.revertATK(); }),
		    new PickupDef(521, "Ogre's Battleaxe", "Attack: (4, 16)", 7, 5, 3, 300, delegate { hero.changeATK(new Dice(4, 4)); }, delegate { hero.revertATK(); }),

		    //shields
		    new PickupDef(547, "Broken Shield", "Increases defense by 1", 8, 2, 1, 100, delegate { hero.changeDEF(1); }, delegate { hero.changeDEF(-1); }),
		    new PickupDef(548, "Fine Wooden Shield", "Increases defense by 4", 8, 2, 2, 200, delegate { hero.changeDEF(4); }, delegate { hero.changeDEF(-4); }),
		    new PickupDef(549, "Tower Shield", "Increases defense by 5", 8, 2, 4, 400, delegate { hero.changeDEF(5); }, delegate { hero.changeDEF(-5); })
	    };

		createLevel ();
        log.init();
        invLog.init(hero, log);
	}

	// EQUIV TO run()
	void Update () {
		heroController ();
        invLog.updateUI();
        isMouseOverObject();
	}

	void createLevel() {

		//Generate the random rooms
		for (int i = 0; i < Random.Range(100, 130); i++) {
			Point pStart = new Point(Random.Range(1, 55), Random.Range(1, 55));
			Point pEnd = new Point(pStart.x () + Random.Range (5, 8), pStart.y () + Random.Range (5, 8));
			
			for(int x = pStart.x(); x < pEnd.x(); x++) {
				for(int y = pStart.y(); y < pEnd.y(); y++) {
					map[x][y].GetComponent<SpriteRenderer>().sprite = lib.sprites[206];
					map[x][y].GetComponent<Cell>().setTileType(1);
				}
			}
		}

		//Flood fill to connect the world
		int currZone = 0;
		List<int> zoneSize = new List<int>();
		for(int x = 0; x < worldSize; x++) {
			for(int y = 0; y < worldSize; y++) {
				Point p = new Point(x, y);

				currZone++;
				int size = floodFill(map[p.x()][p.y()].GetComponent<Cell>().getLoc(), currZone, 0);
				zoneSize.Add(size);
			}
		}
		
		//Get biggest zone in array
		int max = zoneSize[0];
		int largestZone = 0;
		for(int i = 1; i < zoneSize.Count; i++) {
			if(zoneSize[i] > max) {
				largestZone = i;
				max = zoneSize[i];
			}
		}
		largestZone++; //Offset for vector index MIGHT NOT NEED================
		
		//Get rid of everything but largest zone
		int end = worldSize - 1;
		for(int x = 0; x < worldSize; x++) {
			for(int y = 0; y < worldSize; y++) {
				Point p = new Point(x, y);

				if (map[p.x()][p.y()].GetComponent<Cell>().getZone() != largestZone) {
					if ((p.x() + 1 < end && map[p.x() + 1][p.y()].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.x() - 1 > 0 && map[p.x() - 1][p.y()].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.y() + 1 < end && map[p.x()][p.y() + 1].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.y() - 1 > 0 && map[p.x()][p.y() - 1].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.x() - 1 > 0 && p.y() - 1 > 0 && map[p.x() - 1][p.y() - 1].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.x() - 1 > 0 && p.y() + 1 < end   && map[p.x() - 1][p.y() + 1].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.x() + 1 < end && p.y() - 1 > 0 && map[p.x() + 1][p.y() - 1].GetComponent<Cell>().getZone() == largestZone) ||
					    (p.x() + 1 < end && p.y() + 1 < end && map[p.x() + 1][p.y() + 1].GetComponent<Cell>().getZone() == largestZone)) {
						map[p.x()][p.y()].GetComponent<Cell>().setTile(209);
						map[p.x()][p.y()].GetComponent<SpriteRenderer>().sprite = lib.sprites[209];
						map[p.x()][p.y()].GetComponent<Cell>().setTileType(2);
					}
					else {
						map[p.x()][p.y()].GetComponent<Cell>().setTile(0);
						map[p.x()][p.y()].GetComponent<Cell>().setTileType(2);
                        Color bCol;
                        if(UnityEngine.ColorUtility.TryParseHtmlString("2451b200", out bCol))
                            map[p.x()][p.y()].GetComponent<SpriteRenderer>().color = bCol;
					}
				}
				else if (map[p.x()][p.y()].GetComponent<Cell>().getLoc().x() == end) {
					map[p.x()][p.y()].GetComponent<Cell>().setTile(0);
					map[p.x()][p.y()].GetComponent<SpriteRenderer>().color = Color.black;
				}
			}
		}

		//Set player starting position
		for (int x = 0; x < worldSize - 1; x++) {
			for (int y = 0; y < worldSize - 1; y++) {
				Point p = new Point(x, y);
				if (map[p.x()][p.y()].GetComponent<Cell>().getZone() != 0 && map[p.x()][p.y()].GetComponent<Cell>().getCellType() != 2)
					playableMap.Add(map[p.x()][p.y()].GetComponent<Cell>().getLoc());
			}
		}
		Point heroLoc = getRandomLoc ();
        moveHero(heroLoc);
		transform.position = new Vector3 (hero.getObj().transform.position.x, hero.getObj().transform.position.y, transform.position.z);

		//Create monsters
		for (int i = 0; i < playableMap.Count; i++) {
			int chance = Random.Range (0, 20);
			if(chance == 0) {
                //Create the monster
                ActorDef monDef = pickFromActors(monsterDefs);
                createMonster(monDef, playableMap[i]);

                //Give chance to spawn with item
                int pChance = Random.Range(1, 5); //Give 10% chance to spawn
                if (pChance == 3) {
                    createPickup(playableMap[i]);
                }
			}
		}
	}
	int floodFill(Point loc, int zone, int size) {
		if (!(loc.x() < 0 || loc.x() > worldSize - 1 || loc.y() < 0 || loc.y() > worldSize - 1)) {
			if (map[loc.x()][loc.y()].GetComponent<Cell>().getZone() != 0 || map[loc.x()][loc.y()].GetComponent<Cell>().getCellType() == 2)
				return 1;
			else {
				map[loc.x()][loc.y()].GetComponent<Cell>().setZone(zone);
				//Debug.Log(zone);
				return size + floodFill(loc - new Point(0, 1), zone, size) + floodFill(loc - new Point(1, 0), zone, size) + floodFill(loc + new Point(1, 0), zone, size) + floodFill(loc + new Point(0, 1), zone, size);
			}
		}
		else
			return size;
	}


	void heroController() {
		//HERO CONTROLLER
		int dir = 0;
		if (Input.GetButtonDown ("Horizontal")) {
			if(Input.GetAxis("Horizontal") > 0) 
				dir = 1;
			else 
				dir = -1;

			Point heroLoc = hero.getLoc();
			Point p = new Point(heroLoc.x() + dir, heroLoc.y());

			if(moveableCell(p)) {
				Vector3 nPos = new Vector3(hero.getObj().transform.position.x + dir, hero.getObj().transform.position.y, hero.getObj().transform.position.z);
                moveHero(new Point((int)hero.getObj().transform.position.x + dir, (int)hero.getObj().transform.position.y));
                lib.moveCamera(new Vector3(nPos.x, nPos.y, this.transform.position.z));
                moveAI();

                if (map[p.x()][p.y()].GetComponent<Cell>().hasPickup()) {
                    addPickup(p);
                }
			}
            else if(map[p.x()][p.y()].GetComponent<Cell>().hasActor()) {
                doBattle(hero, monsters[getMonsterAtPoint(p)]);
            }
		} 
		else if (Input.GetButtonDown ("Vertical")) {
			if(Input.GetAxis("Vertical") > 0) 
				dir = 1;
			else 
				dir = -1;

            Point heroLoc = hero.getLoc();
			Point p = new Point(heroLoc.x(), heroLoc.y() + dir);
			
			if(moveableCell(p)) {
				Vector3 nPos = new Vector3(hero.getObj().transform.position.x, hero.getObj().transform.position.y + dir, hero.getObj().transform.position.z);
                moveHero(new Point((int)hero.getObj().transform.position.x, (int)hero.getObj().transform.position.y + dir));
				this.transform.position = new Vector3(nPos.x, nPos.y, this.transform.position.z); //Set camera position to follow hero
                moveAI();

                if (map[p.x()][p.y()].GetComponent<Cell>().hasPickup())
                    addPickup(p);
			}
            else if (map[p.x()][p.y()].GetComponent<Cell>().hasActor())
                doBattle(hero, monsters[getMonsterAtPoint(p)]);
		}
	}

    void doBattle(Actor atkr, Actor atkd) {
        int which = Random.Range(1, 5);

        //Juiciness
        lib.play("OnHit" + which.ToString());
        StartCoroutine(AnimateAttack(atkd.getObj()));


        int atkrDMG = atkr.getATK() - atkd.getActorDef().getDEF();
        int atkdDMG = atkd.getATK() - atkr.getActorDef().getDEF();

        atkr.doDMG(atkdDMG);
        string atkrEvent;
        if (atkrDMG > 0)
            atkrEvent = atkr.getActorDef().getDESC() + " attacked " + atkd.getActorDef().getDESC() + " for " + atkrDMG.ToString() + "!";
        else
            atkrEvent = atkr.getActorDef().getDESC() + " missed!";
        log.registerEvent(atkrEvent);

        atkd.doDMG(atkrDMG);
        string atkdEvent;
        if (atkrDMG > 0) {
            if (atkdDMG > 0)
                atkdEvent = atkd.getActorDef().getDESC() + " defended for " + atkdDMG.ToString() + "!";
            else
                atkdEvent = atkd.getActorDef().getDESC() + " couldn't defend!";
        }
        else
            atkdEvent = atkd.getActorDef().getDESC() + " missed!";
        log.registerEvent(atkdEvent);

        if (atkr.onDeath()) {
            if (atkr.isHero()) {
                lib.play("HeroOnDeath");
                killHero();
            }
            else
                killMonster(atkr.getLoc());
        }
        else if (atkd.onDeath()) {
            if (atkd.isHero()) {
                lib.play("HeroOnDeath");
                killHero();
            }
            else
                killMonster(atkd.getLoc());
        }

        //Degrade armor / weapon
        invLog.degradeGear();
    }

	Point getRandomLoc() {
		int spot = Random.Range (0, playableMap.Count);
		return new Point (playableMap[spot].x(), playableMap[spot].y());
	}
    bool moveableCell(Point p) {
        Cell c = map[p.x()][p.y()].GetComponent<Cell>();

	    if (c.getCellType() != 2 && c.hasActor() == false)
		    return true;
	    else
		    return false;
    }
    int getMonsterAtPoint(Point loc) {
        if (map[loc.x()][loc.y()].GetComponent<Cell>().hasActor()) {
            for (int i = 0; i < monsters.Count; i++)
                if (monsters[i].getLoc() == loc)
                    return i;
            return -2;
        }
        else
            return -1;
    }
    int getPickupAtPoint(Point loc) {
        if (map[loc.x()][loc.y()].GetComponent<Cell>().hasPickup()) {
            for (int i = 0; i < pickups.Count; i++)
                if (pickups[i].getLoc() == loc)
                    return i;
            return -2;
        }
        else
            return -1;
    }

//==========================AI STUFF================================
	void moveAI() {
        for (int i = 0; i < monsters.Count; i++) {
            Point loc = monsters[i].getLoc();
            Point heroLoc = new Point((int)hero.getObj().transform.position.x, (int)hero.getObj().transform.position.y);
	        int xDist = heroLoc.x() - loc.x();
	        int yDist = heroLoc.y() - loc.y();

	        Point dir = new Point(0, 0);

	        //Choose direction
	        if (xDist == 0 && yDist == 0)
	        	dir = new Point(0, 0);
	        else if (xDist == 0 && yDist != 0)
	        	dir = new Point(0, yDist / Math.Abs(yDist));
	        else if (xDist != 0 && yDist == 0)
	        	dir = new Point(xDist / Math.Abs(xDist), 0);
	        else if (xDist != 0 && yDist != 0)
	        	dir = new Point(xDist / Math.Abs(xDist), yDist / Math.Abs(yDist));
   

	        //Move monster based on whether it's close enough to the hero or not
	        if (Math.Abs(xDist) + Math.Abs(yDist) < 5) {
	        	loc = loc + pickAIPoint(monsters[i], dir, false);
	        	monsters[i].gettingTired();
	        }
	        else
	        	loc = loc + pickAIPoint(monsters[i], dir, true);

	        //Don't move the monster if it's next to the hero, make it attack
	        if (new Point(Math.Abs(xDist), Math.Abs(yDist)) == new Point(0, 1) || new Point(Math.Abs(xDist), Math.Abs(yDist)) == new Point(1, 0))
	        	doBattle(monsters[i], hero); //Is going to attack hero
	        else {
	    	    //Update loc in map grid
	    		if (loc > new Point(0, 0) && loc < new Point(63, 63)) {
				    if (moveableCell(map[loc.x()][loc.y()].GetComponent<Cell>().getLoc())) {
					    if (!monsters[i].isTired()) {
							//Move the monster
						    moveMonster(monsters[i], loc);
					    }
				    }
			    }
		    }
	    }
	}
    Point pickAIPoint(Actor monster, Point dir, bool random) {
	    int which = 0;
	    if (!random) {
            which = Random.Range(0, 1);

		    if (dir.x() != 0 && dir.y() != 0) {
			    switch (which) {
			    	case 0:
			    		return new Point(dir.x(), 0);
				    case 1:
				    	return new Point(0, dir.y());
				    default:
				    	return new Point(0, 0);
			    }
		    }
		    else
		    	return dir;
	    } 
	    else {
            which = Random.Range(0, 3);

	    	//Add home hovering here
	    	if (monster.getLoc() < monster.getHome() + new Point(3, 3)) {
                which = Random.Range(0, 2);

		    	switch (which) {
		    	case 0:
			    	return new Point(1, 0);
			    case 1:
			    	return new Point(0, 1);
                default:
                    return new Point(0, 0);
		    	}
		    }
		    else if (monster.getLoc() > monster.getHome() + new Point(3, 3)) {
                which = Random.Range(0, 2);

		    	switch (which) {
			    case 0:
			    	return new Point(-1, 0);
			    case 1:
			    	return new Point(0, -1);
                default:
                    return new Point(0, 0);
			    }
		    }
		    else if (monster.getLoc() == monster.getHome()) {
		    	return pickRandomPoint();
		    }
		    else
		    	return pickRandomPoint();
	    }
    }
    Point pickRandomPoint() {
        int which = Random.Range(0, 4);
	    switch (which) {
	        case 0:
		        return new Point(1, 0);
	        case 1:
		        return new Point(0, 1);
	        case 2:
		        return new Point(-1, 0);
	        case 3:
		        return new Point(0, -1);
	        default:
		        return new Point(0, 0);
	    }
    }

    //Pickups
    void addPickup(Point loc) {
        if (invLog.isInventoryFull()) {
            log.registerEvent("Inventory full!");
        }
        else {
            lib.play("OnPickup");
            int idx = getPickupAtPoint(loc);
            invLog.addPickup(pickups[idx]);
            log.registerEvent("Picked up a " + pickups[idx].getPickupDef().getName() + "!");
            GameObject.Destroy(pickups[idx].getObj());
            pickups.RemoveAt(idx);
            map[loc.x()][loc.y()].GetComponent<Cell>().pickup(false);
        }
    }

    //KILL
    void killMonster(Point loc) {
	    //Find the monster
		int idx;
		for (idx = 0; idx < monsters.Count; idx++) {
			if (monsters[idx].getLoc() == loc)
				break;
		}
        GameObject.Destroy(monsters[idx].getObj());
		monsters.RemoveAt(idx);
        map[loc.x()][loc.y()].GetComponent<Cell>().actor(false);

		//Give them a chance to drop a pickup
        int chance = Random.Range(0, 2);
        if (chance == 0)
            createPickup(loc);


        int which = Random.Range(1, 4);
        lib.play("OnDeath" + which.ToString());
        //Give XP
        //invLog.enemyKilled(xp);
	}
    void killHero() {
	    deadHero = true;
	    log.registerEvent("PRESS ESCAPE TO EXIT");
	    lib.play("HeroOnDeath");
    }

    //UTILITY
    void moveMonster(Actor mon, Point p) {
        map[mon.getLoc().x()][mon.getLoc().y()].GetComponent<Cell>().actor(false);
        map[p.x()][p.y()].GetComponent<Cell>().actor(true);
        mon.setLoc(p);
        mon.getObj().transform.position = new Vector3(p.x(), p.y(), mon.getObj().transform.position.z);
    }
    void moveHero(Point p) {
        hero.getObj().transform.position = new Vector3(p.x(), p.y(),-3.0F);
        hero.setLoc(p);
    }
    void createMonster(ActorDef def, Point loc) {
        GameObject mon = lib.createActor(def.getTile(), loc);
        monsters.Add(new Actor(def, mon, loc, false, false));
        map[loc.x()][loc.y()].GetComponent<Cell>().actor(true);
    }
    void createPickup(Point loc) {
        PickupDef def = pickFromPickups(pickupDefs);
        GameObject pickup = lib.createPickup(def.getTile(), loc, -1);
        pickups.Add(new Pickup(def, loc, pickup));
        map[loc.x()][loc.y()].GetComponent<Cell>().pickup(true);
    }
    void isMouseOverObject() {
        Vector3 pos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        Debug.Log(pos);

        Point mouseLoc = new Point((int)Math.Round(pos.x), (int)Math.Round(pos.y));

        if (map[mouseLoc.x()][mouseLoc.y()].GetComponent<Cell>().hasActor()) {
            Actor a = monsters[getMonsterAtPoint(mouseLoc)];
            log.renderMouseHover(a.getActorDef().getDESC(), "ATK: " + a.getActorDef().actorATK().to_str(), "DEF: " + a.getActorDef().getDEF().ToString(), "");
        }
        else if (map[mouseLoc.x()][mouseLoc.y()].GetComponent<Cell>().hasPickup()) {
            Pickup p = pickups[getPickupAtPoint(mouseLoc)];
            log.renderMouseHover(p.getPickupDef().getName(), p.getPickupDef().getDESC(), "Uses: " + p.getPickupDef().getUses(), "");
        }
        else
            log.derenderMouseHover();
          
    }

    //Pick from table
    PickupDef pickFromPickups(List<PickupDef> pUpDefs) {
        List<PickupDef> pDefs = pUpDefs;

		//Set difficulty frequencies
		for (int i = 0; i < pDefs.Count; i++) {
			float freqFloat = ((float)currLevel / (float)pDefs[i].getWeight()) * 100.0F;
			int freq = (int)freqFloat;
			pDefs[i].setWeight(freq);
		}

		int totalSum = 0;
		for (int i = 0; i < pDefs.Count; i++)
			totalSum += pDefs[i].getWeight();

        int index = Random.Range(0, totalSum);

		int sum = 0;
		int idx = 0;
		while (sum < index)
			sum = sum + pDefs[idx++].getWeight();
		if (idx == 0)
			idx++;
        int which = Random.Range(0, idx);
		return pDefs[which];
	}
    ActorDef pickFromActors(List<ActorDef> actDefs) {
        List<ActorDef> aDefs = actDefs;

		//Set difficulty frequencies
		for (int i = 0; i < aDefs.Count; i++) {
			float freqFloat = ((float)currLevel / (float)aDefs[i].getWeight()) * 100.0F;
			int freq = (int)freqFloat;
			aDefs[i].setWeight(freq);
		}

		int totalSum = 0;
		for (int i = 0; i < aDefs.Count; i++)
			totalSum += aDefs[i].getWeight();

        int index = Random.Range(0, totalSum - 1);

		int sum = 0;
		int idx = 0;
		while (sum < index) {
			sum = sum + aDefs[idx++].getWeight();
		}
		if (idx == 0)
			idx++;
        int which = Random.Range(0, idx - 1);
		return aDefs[which];
	}

//==============UI EVENTS======================
    public void onClick(string idx) {

        Debug.Log(idx);
        //Items
        if (idx[0] != 'G') {
            int i = Convert.ToInt32(idx);
            Pickup p = invLog.getPickupAtSlot(i);

            if (p.getPickupDef().getType() == 0) {
                if (invLog.usePickup(i))
                    log.registerEvent("Used a " + p.getPickupDef().getName() + "!");
            }
            else if (p.getPickupDef().getType() > 0) {
                if (invLog.equipGear(i)) {
                    log.registerEvent("Equipped a " + p.getPickupDef().getName() + "!");
                    lib.play("UnequipGear");
                }
                else {
                    log.registerEvent(p.getPickupDef().getTypeName() + " already equipped.");
                    lib.play("Error");
                }
            }
        }
        else {
            idx = idx.Remove(0, 1);
            Debug.Log("Gear click");

            int i = Convert.ToInt32(idx);
            Pickup p = invLog.getGearAtSlot(i);
            if (invLog.unequipGear(i)) {
                log.registerEvent("Unequipped a " + p.getPickupDef().getName() + "!");
                lib.play("OnUse");
            }
            else {
                log.registerEvent("Couldn't unequip! Inventory full!");
            }

        }

    }
    public void beginDrag(string idx) {
        int i = Convert.ToInt32(idx);

        if (!invLog.isSlotEmpty(i)) {
            GameObject item = GameObject.Find("Slot" + (i + 1).ToString());
            item.transform.position = Input.mousePosition;

            //Change hierarchy
            item.transform.parent = GameObject.Find("INVENTORY").transform;
            item.transform.SetAsLastSibling();
        }
    }
    public void endDrag(string idx) {
        int i = Convert.ToInt32(idx);

        if (((float)Screen.width - Input.mousePosition.x) > 120.0F) {
            if(invLog.getPickupAtSlot(i).getLoc() != new Point(-1, -1))
                log.registerEvent("Destroyed a " + invLog.getPickupAtSlot(i).getPickupDef().getName() + "!");

            GameObject slot = GameObject.Find("Slot" + (i + 1).ToString());
            GameObject slotBG = GameObject.Find("Slot" + (i + 1).ToString() + "BG");
            slot.transform.position = slotBG.transform.position;
            slot.GetComponent<Image>().sprite = slotBG.GetComponent<Image>().sprite;

            invLog.destroyPickup(Convert.ToInt32(idx));
            lib.play("DropItem");
        }
        else {
            GameObject slot = GameObject.Find("Slot" + (i + 1).ToString());
            GameObject slotBG = GameObject.Find("Slot" + (i + 1).ToString() + "BG");
            slot.transform.position = slotBG.transform.position;

            //Change hierarchy
            slot.transform.parent = slotBG.transform;
        }
    }

    public void onMouseEnter(string idx) {
        //Items
        if (idx[0] != 'G') {
            int i = Convert.ToInt32(idx);
            GameObject slotBG = GameObject.Find("Slot" + (i + 1).ToString() + "BG");

            if (!invLog.isSlotEmpty(i))
                slotBG.GetComponent<Image>().color = new Vector4(1, 0, 0, 0.7F);
            else {
                Debug.Log("herpderp");
                Pickup p = invLog.getGearAtSlot(i);
                log.renderMouseHover(p.getPickupDef().getName(), p.getPickupDef().getDESC(), p.getUsesLeft().ToString(), "");
            }
        }
        //gear
        else {
            idx = idx.Remove(0, 1);
            int i = Convert.ToInt32(idx);
            GameObject slotBG = GameObject.Find("Gear" + (i + 1).ToString() + "BG");

            if (!invLog.isGearEmpty(i))
                slotBG.GetComponent<Image>().color = new Vector4(1, 0, 0, 0.7F);
            else {
                Debug.Log("herpderp");
                Pickup p = invLog.getGearAtSlot(i);
                log.renderMouseHover(p.getPickupDef().getName(), p.getPickupDef().getDESC(), p.getUsesLeft().ToString(), "");
            }
        }
    }
    public void onMouseLeave(string idx) {
        //items
        if (idx[0] != 'G') {
            int i = Convert.ToInt32(idx);
            GameObject slotBG = GameObject.Find("Slot" + (i + 1).ToString() + "BG");

            slotBG.GetComponent<Image>().color = new Vector4(1, 1, 1, 1);
        }
        //gear
        else {
            idx = idx.Remove(0, 1);
            int i = Convert.ToInt32(idx);
            GameObject slotBG = GameObject.Find("Gear" + (i + 1).ToString() + "BG");

            slotBG.GetComponent<Image>().color = new Vector4(1, 1, 1, 1);
            log.derenderMouseHover();
        }
    }


//UI STUFF
    IEnumerator AnimateAttack(GameObject go) {
        go.GetComponent<SpriteRenderer>().color = new Vector4(1, 0, 0, 1);
        yield return new WaitForSeconds(0.1F);
        go.GetComponent<SpriteRenderer>().color = Color.white;
    }
}