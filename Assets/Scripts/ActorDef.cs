using UnityEngine;
using System.Collections;

public class ActorDef {
//VARS
	private Dice atk;
	private int def;
	private int maxhp;
	private int tile;
	private string desc;
	private int weight;
	private int xp;
	
//STRUCTORS
	public ActorDef() {
		def = 0;
		maxhp = 0;
		tile = 0;
		desc = "";
	}
	public ActorDef(Dice atk, int def, int maxhp, int tile, string desc, int weight) {
		this.atk = atk;
		this.def = def;
		this.maxhp = maxhp;
		this.tile = tile;
		this.desc = desc;
		this.weight = weight;
		this.xp = weight;
	}
	
//GETTERS SETTERS
	public Dice actorATK() {
		return atk;
	}
	public int getDEF() {
		return def;
	}
	public int getMaxHP() {
		return maxhp;
	}
	public int getTile() {
		return tile;
	}
	public string getDESC() {
		return desc;
	}
	
	public void setATK(Dice atk) {
		this.atk = atk;
	}
	public void setDEF(int def) {
		this.def = def;
	}
	public void setMaxHP(int maxhp) {
		this.maxhp = maxhp;
	}
	public void setTile(int tile) {
		this.tile = tile;
	}
	public void setDESC(string str) {
		this.desc = str;
	}
	
	public int getWeight() {
		return weight;
	}
	public void setWeight(int weight) {
		this.weight = weight;
	}
	public int getXP() {
		return xp;
	}
}
