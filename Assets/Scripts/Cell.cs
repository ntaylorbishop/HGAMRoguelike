using UnityEngine;
using System.Collections;

public class Cell : MonoBehaviour {
	public Point loc = new Point(0, 0);
	public int type = 0;
	public int tile = 0;
	public int zone = 0;

    public bool containsActor = false;
    public bool containsPickup = false;

	public void setCell(Point p, int nType, int nTile, int nZone) {
		loc = p;
		this.type = nType;
		this.tile = nTile;
		this.zone = nZone;
	}

	public Point getLoc() {
		return loc;
	}
	public int getCellType() { //type: 0 for dummy Tile, 1 for floor tile, 2 for wall, 3 for Character, 4 for foliage, 5 for Stairs, 6 for Shop, 7 for boss descend, 8 for boss ascend
		return type;
	}
	public int getTile() {
		return tile;
	}
	public int getZone() {
		return zone;
	}
	public void setLoc(Point p) {
		loc = p;
	}
	public void setTileType(int nType) {
		type = nType;
	}
	public void setTile(int nTile) {
		tile = nTile;
		//gameObject.GetComponent<SpriteRenderer> ().sprite = lib.sprites [nTile];
	}
	public void setZone(int nZone) {
		zone = nZone;
	}
    public bool hasActor() {
        return containsActor;
    }
    public void actor(bool b) {
        containsActor = b;
    }
    public bool hasPickup() {
        return containsPickup;
    }
    public void pickup(bool b) {
        containsPickup = b;
    }

}