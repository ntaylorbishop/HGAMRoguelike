#pragma once

#include <Windows.h>
#include <stddef.h>
#include <string>

#include "tilelib.h"
#include "Point.h"

using namespace std;

class TileLibrary {
public:
	TileLibrary();

	void init(char *windowtitle, int width, int height, char *name, int tilesz = 32, int numtex = 1);
	void shutdown();
	void framestart();
	void rendertile(int tile, Point loc);

	Point res();

	void tile_color(int col = 0xFFFFFFFF);
	void tile_scale(int sc = 1);
	void tile_rotation(int rot = 0);
	void tile_toggleflip();

	bool keydown(char *key);
	bool keywentdown(char *key);

	bool buttondown(int button = 1);
	bool buttonwentdown(int button = 1);

	Point mouseLoc();

	void play(string filename);

	void renderText(Point start, string text);

	template<typename Func>
	void loop_portion(Point start, Point end, Func f) {
		for (int x = start.x(); x < end.x(); x++) {
			for (int y = start.y(); y < end.y(); y++) {
				f(Point(x, y));
			}
		}
	}
	template<typename Func>
	void loop_portion_reverse(Point start, Point end, Func f) {
		for (int y = start.y(); y < end.y(); y++) {
			for (int x = start.x(); x < end.x(); x++) {
				f(Point(x, y));
			}
		}
	}
private:
	string fPath = "../base_materials/sound/";
};

