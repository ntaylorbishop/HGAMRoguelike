using UnityEngine;
using System.Collections;
using System;

public delegate void useEffect();
public delegate void removeEffect();

public class PickupDef {
//VARS
	private int tile;
	private string name;
	private string desc;
	private int type; //0 Potion, 1 Head, 2 Neck, 3 Chest, 4 Hand, 5 feet, 6 tomb, 7 sword, 8 shield
	private int uses;
	private int weight;
	private int price;

	public useEffect useEffect;
	public removeEffect removeEffect;

//STRUCTORS
	public PickupDef() {
		this.tile = 0;
		this.name = "NULL";
		this.desc = "NULL";
		this.type = -1;
		this.weight = 0;
	}
	public PickupDef(int tile, string name, string desc, int weight, int price, useEffect useEffect) {
		this.tile = tile;
		this.name = name;
		this.desc = desc;
		this.type = 0;
		this.useEffect = useEffect;
		this.weight = weight;
		this.price = price;
	}
	public PickupDef(int tile, string name, string desc, int type, int uses, int weight, int price, useEffect useEffect, removeEffect removeEffect) {
		this.tile = tile;
		this.name = name;
		this.desc = desc;
		this.type = type;
		this.uses = uses;
		this.useEffect = useEffect;
		this.removeEffect = removeEffect;
		this.weight = weight;
		this.price = price;
	}
	public PickupDef(int tile, string name, string desc, int type, int uses, int weight, int price) {
		this.tile = tile;
		this.name = name;
		this.desc = desc;
		this.type = type;
		this.uses = uses;
		this.weight = weight;
		this.price = price;
	}

//GETTERS / SETTERS
	public int getTile() {
		return tile;
	}
	public string getName() {
		return name;
	}
	public string getDESC() {
		return desc;
	}
	public int getType() {
		return type;
	}
	public string getTypeName() {
		switch (type) {
		case 1:
			return "head piece";
		case 2:
			return "necklace";
		case 3:
			return "chest piece";
			 
		case 4:
			return "glove";
			 
		case 5:
			return "boot";
			 
		case 6:
			return "tomb";
			 
		case 7:
			return "weapon";
			 
		case 8:
			return "shield";
			 
		default:
			return "error";
			
		}
	}
	public int getUses() {
		return uses;
	}
	public int getWeight() {
		return weight;
	}
	public void setWeight(int weight) {
		this.weight = weight;
	}
	public int getPrice() {
		return price;
	}
	
	public void addEffects(useEffect useEffect, removeEffect removeEffect) {
		this.useEffect = useEffect;
		this.removeEffect = removeEffect;
	}

//UTILITY
	public override bool Equals(object Obj) {
		PickupDef other = (PickupDef)Obj;
		return (this.name == other.name);
	}
	public static bool operator ==(PickupDef p1, PickupDef p2)  {
		return (p1.name == p2.name);
	}
	public static bool operator !=(PickupDef p1, PickupDef p2)  {
		return (p1.name != p2.name);
	}
    public override int GetHashCode() {
        return -1;
    }

}
