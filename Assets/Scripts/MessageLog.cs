using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class MessageLog {
	private List<string> msgs;
	private bool somethingMousedOver;
	private int currTurn = 0;

    //GUI elements
    private GameObject TextBox1;
    private GameObject TextBox2;
    private GameObject TextBox3;
    private GameObject TextBox4;

    private GameObject HoverBackground;
    private GameObject InfoBox1;
    private GameObject InfoBox2;
    private GameObject InfoBox3;
    private GameObject InfoBox4;

	public void init() {
        msgs = new List<string>();

        //Log Text boxes
        TextBox1 = GameObject.Find("TextBox1");
        TextBox2 = GameObject.Find("TextBox2");
        TextBox3 = GameObject.Find("TextBox3");
        TextBox4 = GameObject.Find("TextBox4");

        //mouseOver text boxes
        HoverBackground = GameObject.Find("Hover");
        InfoBox1 = GameObject.Find("InfoBox1");
        InfoBox2 = GameObject.Find("InfoBox2");
        InfoBox3 = GameObject.Find("InfoBox3");
        InfoBox4 = GameObject.Find("InfoBox4");
        HoverBackground.GetComponent<Image>().color = new Vector4(0, 0, 0, 0);

        registerEvent("Welcome to Roguelike!");
	}

	public void registerEvent(string str) {
        msgs.Add(str);
        if (msgs.Count < 4) {
            int idx = 0;
            for (int i = msgs.Count - 1; i >= 0; i--) {
                if(idx == 0)
                    TextBox1.GetComponent<Text>().text = msgs[i];
                else if (idx == 1)
                    TextBox2.GetComponent<Text>().text = msgs[i];
                else if (idx == 2)
                    TextBox3.GetComponent<Text>().text = msgs[i];
                else if (idx == 3)
                    TextBox4.GetComponent<Text>().text = msgs[i];
                idx++;
            }
        }
        else {
            int idx = 0;
            for (int i = msgs.Count - 1; i > msgs.Count - 5; i--) {
                if (idx == 0)
                    TextBox1.GetComponent<Text>().text = msgs[i];
                else if (idx == 1)
                    TextBox2.GetComponent<Text>().text = msgs[i];
                else if (idx == 2)
                    TextBox3.GetComponent<Text>().text = msgs[i];
                else if (idx == 3)
                    TextBox4.GetComponent<Text>().text = msgs[i];
                idx++;
            }
        }
	}

	public void incTurn() {
		currTurn++;
	}
    public void renderMouseHover(string str1, string str2, string str3, string str4) {
        //HoverBackground.GetComponent<Image>().color = new Vector4(0, 0, 0, 0.4F);
        InfoBox1.GetComponent<Text>().text = str1;
        InfoBox2.GetComponent<Text>().text = str2;
        InfoBox3.GetComponent<Text>().text = str3;
        InfoBox4.GetComponent<Text>().text = str4;
    }
    public void derenderMouseHover() {
        HoverBackground.GetComponent<Image>().color = new Vector4(1, 1, 1, 0);
        InfoBox1.GetComponent<Text>().text = "";
        InfoBox2.GetComponent<Text>().text = "";
        InfoBox3.GetComponent<Text>().text = "";
        InfoBox4.GetComponent<Text>().text = "";
    }
}
	