#include "MessageLog.h"

void MessageLog::init(TileLibrary* library) {
	this->lib = library;

	asciiMsgs.push_back(msgToASCII("Welcome to Roguelike!"));
	msgTurn.push_back(currTurn);
	somethingMousedOver = false;
}
void MessageLog::registerEvent(string str) {
	asciiMsgs.push_back(msgToASCII(str));
	msgTurn.push_back(currTurn);
}
void MessageLog::renderMsgs() {
	//Render background
	lib->loop_portion(Point(0, lib->res().y() - 2), Point(lib->res().x(), lib->res().y()), [&](Point p) {
		lib->rendertile(0x125, p);
	});

	//Render messages
	lib->tile_scale(2);
	Point pos(1, lib->res().y() - 4);
	if (asciiMsgs.size() >= 4) {
		for (std::vector<vector<int>>::size_type i = asciiMsgs.size() - 1; i != (std::vector<int>::size_type) - 1; i--) {
			renderMsg(pos, i);
		}
	}
	else if(asciiMsgs.size() < 4) {
		for (int i = asciiMsgs.size() - 1; i >= 0; i--)
			renderMsg(pos, i);
	}
	lib->tile_scale(1);
}

vector<int> MessageLog::msgToASCII(string str) {
	vector<int> chars;

	for (unsigned int i = 0; i < str.length(); i++)
		chars.push_back(static_cast<int>(str[i]));

	return chars;
}

void MessageLog::renderMsg(Point& pos, int idx) {
	pos.setx(1);
	if (idx >= 0 && idx <= msgTurn.size()) {
		if (msgTurn[idx] != currTurn)
			tl_color(0xFFFFFF60);
	}
	for (unsigned int j = 0; j < asciiMsgs[idx].size(); j++) {
		lib->rendertile(asciiMsgs[idx][j], pos);
		pos.setx(pos.x() + 1);
	}
	pos.sety(pos.y() + 1);
	tl_color(0xFFFFFFFF);
}

void MessageLog::renderMsg(Point& pos, string msg) {
	pos.setx(pos.x() + 1);
	vector<int> asciiMsg = msgToASCII(msg);

	for (unsigned int i = 0; i < asciiMsg.size(); i++) {
		lib->rendertile(asciiMsg[i], pos);
		pos.setx(pos.x() + 1);
	}
}
void MessageLog::incTurn() {
	currTurn++;
}

void MessageLog::renderMouseOver(string str1, string str2, string str3, string str4) {
	tl_scale(2);

	lib->loop_portion(Point(0, 0), Point(lib->res().x() - 8, 4), [&](Point p) {
		tl_color(0x00000050);
		lib->rendertile(0x100, p);
	});
	tl_color(0xFFFFFFFF);
	renderMsg(Point(0, 0), str1);
	renderMsg(Point(0, 1), str2);
	renderMsg(Point(0, 2), str3);
	renderMsg(Point(0, 3), str4);
	tl_scale(1);
}