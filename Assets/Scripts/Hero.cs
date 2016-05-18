using UnityEngine;
using System.Collections;

public class Hero : Actor {
    Dice base_atk;
    int mana = 100;
    int maxMana = 100;

    public Hero(ActorDef def, GameObject go, Point loc) : base(def, go, loc, true, false) { 
        base_atk = def.actorATK(); 
    }

	public void changeATK(Dice d) {
	    def.setATK(d);
    }
    public void revertATK() {
	    def.setATK(base_atk);
    }
    public void changeDEF(int num) {
	    def.setDEF(def.getDEF() + num);
    }
    public void changeHP(int num) {
	    hp = hp + num;
	    if (hp > def.getMaxHP())
		    hp = def.getMaxHP();
    }
    public void changeMaxHP(int num) {
	    int newMax = def.getMaxHP() + num;
	    if (newMax < hp)
		    hp = newMax;
	    def.setMaxHP(newMax);
    }

    public void changeMana(int num) {
	    mana = mana + num;
	    if (mana > maxMana)
		    mana = maxMana;
    }
    public void changeMaxMana(int num) {
	    maxMana = maxMana + num;
    }

    public int getMana() {
	    return mana;
    }
    public int getMaxMana() {
	    return maxMana;
    }
}
