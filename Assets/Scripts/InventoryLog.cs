using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System;

public class InventoryLog {
    private GameObject UI_HP;
    private GameObject UI_MN;
    private GameObject UI_ATK;
    private GameObject UI_DEF;
    private int gold = 1000;
    private Hero hero;
    private int invSize = 0;
    private MessageLog log;
    private TileLibrary lib;

    
    private List<GameObject> invSlots;
    private List<GameObject> invSlotBGS;
    private List<Pickup> inventory;
    private List<bool> slotFilled;
    private List<GameObject> gearSlots;
    private List<GameObject> gearSlotBGS;
    private List<Pickup> gear;

    public void init(Hero h, MessageLog log) {
        lib = new TileLibrary();
        log = new MessageLog();

        inventory = new List<Pickup>();
        for (int i = 0; i < 14; i++) {
            inventory.Add(new Pickup());
        }

        invSlots = new List<GameObject>();
        invSlots.Add(GameObject.Find("Slot1"));
        invSlots.Add(GameObject.Find("Slot2"));
        invSlots.Add(GameObject.Find("Slot3"));
        invSlots.Add(GameObject.Find("Slot4"));
        invSlots.Add(GameObject.Find("Slot5"));
        invSlots.Add(GameObject.Find("Slot6"));
        invSlots.Add(GameObject.Find("Slot7"));
        invSlots.Add(GameObject.Find("Slot8"));
        invSlots.Add(GameObject.Find("Slot9"));
        invSlots.Add(GameObject.Find("Slot10"));
        invSlots.Add(GameObject.Find("Slot11"));
        invSlots.Add(GameObject.Find("Slot12"));
        invSlots.Add(GameObject.Find("Slot13"));
        invSlots.Add(GameObject.Find("Slot14"));

        invSlotBGS = new List<GameObject>();
        invSlotBGS.Add(GameObject.Find("Slot1BG"));
        invSlotBGS.Add(GameObject.Find("Slot2BG"));
        invSlotBGS.Add(GameObject.Find("Slot3BG"));
        invSlotBGS.Add(GameObject.Find("Slot4BG"));
        invSlotBGS.Add(GameObject.Find("Slot5BG"));
        invSlotBGS.Add(GameObject.Find("Slot6BG"));
        invSlotBGS.Add(GameObject.Find("Slot7BG"));
        invSlotBGS.Add(GameObject.Find("Slot8BG"));
        invSlotBGS.Add(GameObject.Find("Slot9BG"));
        invSlotBGS.Add(GameObject.Find("Slot10BG"));
        invSlotBGS.Add(GameObject.Find("Slot11BG"));
        invSlotBGS.Add(GameObject.Find("Slot12BG"));
        invSlotBGS.Add(GameObject.Find("Slot13BG"));
        invSlotBGS.Add(GameObject.Find("Slot14BG"));

        gearSlots = new List<GameObject>();
        gearSlots.Add(GameObject.Find("Gear1"));
        gearSlots.Add(GameObject.Find("Gear2"));
        gearSlots.Add(GameObject.Find("Gear3"));
        gearSlots.Add(GameObject.Find("Gear4"));
        gearSlots.Add(GameObject.Find("Gear5"));
        gearSlots.Add(GameObject.Find("Gear6"));
        gearSlots.Add(GameObject.Find("Gear7"));
        gearSlots.Add(GameObject.Find("Gear8"));

        gearSlotBGS = new List<GameObject>();
        gearSlotBGS.Add(GameObject.Find("Gear1BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear2BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear3BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear4BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear5BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear6BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear7BG1"));
        gearSlotBGS.Add(GameObject.Find("Gear8BG1"));

        for (int i = 0; i < gearSlotBGS.Count; i++)
            gearSlotBGS[i].GetComponent<Image>().color = new Vector4(0, 0, 0, 0.6F);

        gear = new List<Pickup>();
        for (int i = 0; i < 8; i++)
            gear.Add(new Pickup());


        UI_HP = GameObject.Find("HP");
        UI_MN = GameObject.Find("MANA");
        UI_ATK = GameObject.Find("ATK");
        UI_DEF = GameObject.Find("DEF");

        this.hero = h;
        invSize = 0;
    }

    public void updateUI() {
        UI_HP.GetComponent<Text>().text = "HP: " + hero.getHP().ToString() + " / " + hero.getActorDef().getMaxHP();
        UI_MN.GetComponent<Text>().text = "MN: " + hero.getMana().ToString() + " / " + hero.getMaxMana();
        UI_ATK.GetComponent<Text>().text = "ATK: " + hero.getActorDef().actorATK().to_str();
        UI_DEF.GetComponent<Text>().text = "DEF: " + hero.getActorDef().getDEF().ToString();
    }

    public void addPickup(Pickup item) {
        if (invSize < 14) {

            int idx = 0;
            for (int i = 0; i < inventory.Count; i++) {
                if (inventory[i].getLoc() != new Point(-1, -1))
                    idx++;
                else
                    break;
            }

            invSize++;
            invSlots[idx].GetComponent<Image>().sprite = lib.getSprite(item.getPickupDef().getTile());
            inventory[idx] = item;
        }
        else
            Debug.Log("Error: Inventory full"); //Sanity check
    }
    public bool usePickup(int idx) {
        if (inventory[idx].getLoc() != new Point(-1, -1)) {
            inventory[idx].getPickupDef().useEffect();
            GameObject.Destroy(inventory[idx].getObj());
            inventory[idx] = new Pickup();
            lib.play("OnUse");
            invSlots[idx].GetComponent<Image>().sprite = invSlotBGS[idx].GetComponent<Image>().sprite;
            invSize--;
            return true;
        }
        else
            return false;
    }
    public void destroyPickup(int idx) {
        GameObject.Destroy(inventory[idx].getObj());
        inventory[idx] = new Pickup();
        invSize--;
    }


    //Gear Stuff
    public bool equipGear(int idx) { //Idx is index of item in inventory
        int gIdx = inventory[idx].getPickupDef().getType() - 1;
        //Debug.Log(gIdx);
        if (gear[gIdx].getLoc() != new Point(-1, -1))
            return false;
        else {
            //Add gear
            gear[gIdx] = inventory[idx];
            gear[gIdx].getPickupDef().useEffect();
            gearSlots[gIdx].GetComponent<Image>().sprite = lib.getSprite(gear[gIdx].getPickupDef().getTile());
            gearSlots[gIdx].GetComponent<Image>().color = new Vector4(1, 1, 1, 1);
            gearSlotBGS[gIdx].GetComponent<Image>().color = new Vector4(1, 1, 1, 0);

            //Clear inventory slot
            inventory[idx] = new Pickup();
            invSlots[idx].GetComponent<Image>().sprite = invSlotBGS[idx].GetComponent<Image>().sprite;
            
            invSize--;

            return true;
        }
    }
    public bool unequipGear(int idx) {
        if (gear[idx].getLoc() != new Point(-1, -1)) {
            if (invSize < 14) {
                gear[idx].getPickupDef().removeEffect();
                addPickup(gear[idx]);
                gearSlots[idx].GetComponent<Image>().sprite = gearSlotBGS[idx].GetComponent<Image>().sprite;
                gearSlots[idx].GetComponent<Image>().color = gearSlotBGS[idx].GetComponent<Image>().color;
                gearSlotBGS[idx].GetComponent<Image>().color = new Vector4(0, 0, 0, 0.6F);
                gear[idx] = new Pickup();

                return true;
            }
            else
                return false;
        }
        else
            return false;

    }
    public void destroyGear(int idx) {
        GameObject.Destroy(gear[idx].getObj());
        gear[idx] = new Pickup();
    }
    public void degradeGear() {
        //for(int i = 0; i < )
    }

    public bool isSlotEmpty(int idx) {
        if (inventory[idx].getLoc() == new Point(-1, -1))
            return true;
        else
            return false;
    }
    public bool isGearEmpty(int idx) {
        if (gear[idx].getLoc() == new Point(-1, -1))
            return true;
        else
            return false;
    }
    public bool isInventoryFull() {
        if (invSize < 14)
            return false;
        else
            return true;
    }
    public Pickup getPickupAtSlot(int idx) {
        return inventory[idx];
    }
    public Pickup getGearAtSlot(int idx) {
        return gear[idx];
    }
}
