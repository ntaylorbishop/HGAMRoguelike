using UnityEngine;
using System.Collections;

public class Actor {
//VARS
	private Point loc;
	protected int hp;
	protected bool hero;
	protected ActorDef def;
	protected Point home;
	protected int tireOut = 5;
	protected bool boss;
	protected GameObject obj;
	
//STRUCTORS
	public Actor() {
		this.loc = new Point(-1, -1);
	}
	public Actor(ActorDef def, GameObject go, Point loc, bool isHero, bool boss) {
		this.def = def;
		this.hp = def.getMaxHP();
		this.loc = loc;
		this.hero = isHero;
		this.home = loc;
		this.boss = boss;
		obj = go;
	}
	public void killActor() {
		GameObject.Destroy (obj);
	}
	
//GETTERS SETTERS
	public int getHP() {
		return hp;
	}
	public Point getLoc() {
		return loc;
	}
	public ActorDef getActorDef() {
		return def;
	}
	public int getATK() {
		return def.actorATK().rollDice();
	}
    public GameObject getObj() {
        return obj;
    }

	public void doDMG(int dmg) {
		if (dmg > 0) {
			hp = hp - dmg;
			if (hp < 0)
				hp = 0;
		}
	}
	public void setLoc(Point p) {
		this.loc = p;
	}
	public void setActorDef(ActorDef def) {
		this.def = def;
	}
	public bool isHero() {
		return hero;
	}
	public bool isBoss() {
		return boss;
	}
	public Point getHome() {
		return home;
	}
	public void setHome(Point newHome) {
		home = newHome;
	}

//OTHER
	public void gettingTired() {
		tireOut--;
		if (tireOut == -5) {
			tireOut = 5;
			home = loc;
		}
	}
	public bool isTired() {
		return (tireOut <= 0);
	}
	public bool onDeath() {
		if (hp <= 0)
			return true;
		else
			return false;
	}
	
	//UTILITY
	public bool instanceof(Actor a) {
		if (this.def == a.getActorDef())
			return true;
		else
			return false;
	}
}
