using UnityEngine;
using System.Collections;

public class Pickup {
//VARS
	private PickupDef def;
	private Point loc;
	private int uses;
    private GameObject obj;
	
//STRUCTORS
	public Pickup() {
		this.def = new PickupDef();
		this.loc = new Point(-1, -1);
		this.uses = -1;
	}
	public Pickup(PickupDef def, Point loc, GameObject go) {
		this.def = def;
		this.loc = loc;
		this.uses = def.getUses();
        obj = go;
	}
	
//GETTERS / SETTERS
	public PickupDef getPickupDef() {
		return def;
	}
	public Point getLoc() {
		return loc;
	}
    public GameObject getObj() {
        return obj;
    }
	public void setLoc(Point nLoc) {
		loc = nLoc;
	}
    public void setObj(GameObject go) {
        obj = go;
    }
	public void degrade() {
		if (uses > 0)
			uses--;
	}
	public int getUsesLeft() {
		return uses;
	}

//UTILITY
	public override bool Equals(object Obj) {
		Pickup other = (Pickup)Obj;
		return (this.def == other.def);
	}
	public static bool operator ==(Pickup p1, Pickup p2) {
		return (p1.def == p2.def);
	}
	public static bool operator !=(Pickup p1, Pickup p2) {
		return (p1.def != p2.def);
	}
    public override int GetHashCode() {
        return -1;
    }
}
