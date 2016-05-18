using UnityEngine;
using System.Collections;

public class Dice {
	private int sides;
	private int rolls;
	
	public Dice() {
		this.sides = -1;
		this.rolls = -1;
	}
	public Dice(int sides, int rolls) {
		this.sides = sides;
		this.rolls = rolls;
	}
	public int rollDice() {
		int sum = 0;
		for (int i = 1; i < rolls; i++)
			sum += Random.Range (1, sides);
		return sum;
	}
	public string to_str() {
		return rolls.ToString () + ", " + (rolls * sides).ToString ();
	}
	
	public int getSides() {
		return sides;
	}
	public int getRolls() {
		return rolls;
	}
	public void setSides(int sides) {
		this.sides = sides;
	}
	public void setRolls(int rolls) {
		this.rolls = rolls;
	}
}
