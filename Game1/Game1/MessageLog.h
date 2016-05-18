#pragma once

#include <vector>
#include <string>
#include <Windows.h>

#include "TileLibrary.h"
#include "Point.h"

class MessageLog {
public:

	void init(TileLibrary* library);
	void registerEvent(string str);
	void renderMsgs();

	void renderMsg(Point& pos, string msg);
	void incTurn();

	void renderMouseOver(string str1, string str2, string str3, string str4);
private:
	TileLibrary* lib;
	vector<string> msgs;
	vector<int> msgTurn;
	vector<vector<int>> asciiMsgs;
	bool somethingMousedOver;
	vector<int> msgToASCII(string msg);
	int currTurn = 0;

	void renderMsg(Point& pos, int idx);
};

