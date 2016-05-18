using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using System;

public class TileLibrary {
	private GameObject sprite;
	private GameObject actor;
	private GameObject eMap;
	private GameObject eMonsters;
	private GameObject ePickups;
    private GameObject eUI;
	private int tileSize;
	private Color colorRGBA = new Vector4(1, 1, 1, 1);
	public Sprite[] sprites;
    private Camera mainCamera;
    private float tileScale = 1.0F;

	public TileLibrary() {
		sprites = Resources.LoadAll<Sprite>("tiles_0");

        sprite =    Resources.Load<GameObject>("sprite");
        actor =     Resources.Load<GameObject>("actor");
        eMap =      GameObject.Find("Map");
        eMonsters = GameObject.Find("Monsters");
        ePickups =  GameObject.Find("Pickups");
        eUI = GameObject.Find("UI");
        mainCamera = Camera.main;

        tileSize = 64;
	}

	public GameObject createTile(int tile, Point loc, int zIndex) {
        GameObject newObj = MonoBehaviour.Instantiate(sprite);
		newObj.transform.parent = eMap.transform;
		newObj.transform.position = new Vector3 (loc.x (), loc.y (), zIndex);
		newObj.GetComponent<SpriteRenderer> ().sprite = sprites[tile];
		newObj.GetComponent<SpriteRenderer> ().color = colorRGBA;
		newObj.GetComponent<Cell> ().setLoc (loc);
        newObj.transform.localScale = new Vector3(tileScale, tileScale, 0);
		return newObj;
	}
	public GameObject createActor (int tile, Point loc) {
        GameObject newObj = MonoBehaviour.Instantiate(actor);
		newObj.transform.parent = eMonsters.transform;
		newObj.transform.position = new Vector3 (loc.x (), loc.y (), -2);
		newObj.GetComponent<SpriteRenderer> ().sprite = sprites[tile];
		newObj.GetComponent<SpriteRenderer> ().color = colorRGBA;
        newObj.transform.localScale = new Vector3(tileScale, tileScale, 0);
		return newObj;
	}
    public GameObject createPickup(int tile, Point loc, int zIndex) {
        GameObject newObj = MonoBehaviour.Instantiate(sprite);
        newObj.transform.parent = ePickups.transform;
        newObj.transform.position = new Vector3(loc.x(), loc.y(), zIndex);
        newObj.GetComponent<SpriteRenderer>().sprite = sprites[tile];
        newObj.GetComponent<SpriteRenderer>().color = colorRGBA;
        newObj.GetComponent<Cell>().setLoc(loc);
        newObj.transform.localScale = new Vector3(tileScale, tileScale, 0);
        return newObj;
    }
    public GameObject createStaticTile(int tile, Point loc, int zIndex) {
        GameObject newObj = MonoBehaviour.Instantiate(sprite);
		newObj.transform.parent = mainCamera.transform;
		newObj.transform.position = new Vector3 (loc.x (), loc.y (), zIndex);
		newObj.GetComponent<SpriteRenderer> ().sprite = sprites[tile];
		newObj.GetComponent<SpriteRenderer> ().color = colorRGBA;
        newObj.transform.localScale = new Vector3(tileScale, tileScale, 0);
		return newObj;
    }


    public Point res() {
        int xres = Screen.width / tileSize;
        int yres = Screen.height / tileSize;

        return new Point(xres, yres);
    }
	
	public void color(string r, string g, string b, string a) {
        int rCon = Convert.ToInt32(r, 16);
        int gCon = Convert.ToInt32(g, 16);
        int bCon = Convert.ToInt32(b, 16);
        int aCon = Convert.ToInt32(a, 16);
        colorRGBA = new Color((float)rCon / 255.0F, (float)gCon / 255.0F, (float)bCon / 255.0F, (float)aCon / 100.0F);
	}
	public void scale(int sc) { //0 for biggest, 1 for medium, 2 for smallest
        if (sc == 1)
            tileScale = 1.0F;
        else if (sc == 2)
            tileScale = 0.5F;
        else if (sc == 3)
            tileScale = 0.25F;
	}
	
	public Point mouseLoc() {
		int mouse_x, mouse_y;
		mouse_x = (int)Input.mousePosition.x / tileSize;
		mouse_y = (int)Input.mousePosition.y / tileSize;

		return new Point (mouse_x, mouse_y);
	}

    public void moveCamera(Vector3 pos) {
        mainCamera.transform.position = pos;
    }

    public Sprite getSprite(int tile) {
        return sprites[tile];
    }

	public void play(string fileName) {
        AudioSource audio = mainCamera.GetComponent<AudioSource>();
        audio.PlayOneShot((AudioClip)Resources.Load("Sounds/" + fileName));
	}
}
