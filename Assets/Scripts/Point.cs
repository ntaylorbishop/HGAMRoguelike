using UnityEngine;
using System.Collections;

public class Point {
	private int xCoord, yCoord;

	public Point() {
		xCoord = 0;
		yCoord = 0;
	}
	public Point(int x, int y) {
		xCoord = x;
		yCoord = y;
	}
	
	//Getters / Setters
	public int x() {
		return xCoord;
	}
	public int y() {
		return yCoord;
	}
	public void setx(int x) {
		this.xCoord = x;
	}
	public void sety(int y) {
		this.yCoord = y;
	}
	public void setCoords(int x, int y) {
		this.xCoord = x;
		this.yCoord = y;
	}
	
	public string to_str() {
		return "(" + xCoord.ToString() + ", " + yCoord.ToString () + ")";
	}
	
	public static Point operator+(Point p1, Point p2) {
		return new Point(p1.xCoord + p2.xCoord, p1.yCoord + p2.yCoord);
	}
	public static Point operator-(Point p1, Point p2) {
		return new Point(p1.xCoord - p2.xCoord, p1.yCoord - p2.yCoord);
	}
    public static Point operator/(Point p1, int n) {
		return new Point(p1.xCoord / n, p1.yCoord / n);
	}

	//CONDITIONAL OPERATORS
	public static bool operator<(Point p1, Point p2) {
		if (p1.xCoord <= p2.xCoord && p1.yCoord < p2.yCoord)
			return true;
		else if (p1.xCoord < p2.xCoord && p1.yCoord <= p2.yCoord)
			return true;
		else
			return false;
	}
	public static bool operator>(Point p1, Point p2) {
		if (p1.xCoord >= p2.xCoord && p1.yCoord > p2.yCoord)
			return true;
		else if (p1.xCoord > p2.xCoord && p1.yCoord >= p2.yCoord)
			return true;
		else
			return false;
	}
	public static bool operator>=(Point p1, Point p2) {
		if (p1.xCoord >= p2.xCoord && p1.yCoord >= p2.yCoord)
			return true;
		else
			return false;
	}
    public static bool operator<=(Point p1, Point p2) {
		if (p1.xCoord <= p2.xCoord && p1.yCoord <= p2.yCoord)
			return true;
		else
			return false;
	}
	public static bool operator==(Point p1, Point p2) {
		if (p1.xCoord == p2.xCoord && p1.yCoord == p2.yCoord)
			return true;
		else
			return false;
	}
    public static bool operator !=(Point p1, Point p2) {
        if (p1.xCoord != p2.xCoord && p1.yCoord != p2.yCoord)
            return true;
        else
            return false;
    }
    public override bool Equals(object obj) {
        return base.Equals(obj);
    }
    public override int GetHashCode() {
        return base.GetHashCode();
    }
}
