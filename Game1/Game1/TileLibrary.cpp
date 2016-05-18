#include "TileLibrary.h"


TileLibrary::TileLibrary() {
}

void TileLibrary::init(char *windowtitle, int width, int height, char *name, int tilesz, int numtex) {
	tl_init(windowtitle, width, height, name, tilesz, numtex);
}
void TileLibrary::shutdown() {
	tl_shutdown();
}
void TileLibrary::framestart() {
	tl_framestart(0);
}
void TileLibrary::rendertile(int tile, Point loc) {
	int x = loc.x();
	int y = loc.y();

	tl_rendertile(tile, x, y);
}

Point TileLibrary::res() {
	Point p(tl_xres(), tl_yres());

	return p;
}

void TileLibrary::tile_color(int col) {
	tl_color(col);
}
void TileLibrary::tile_scale(int sc) {
	tl_scale(sc);
}
void TileLibrary::tile_rotation(int rot) {
	tl_rotation(rot);
}
void TileLibrary::tile_toggleflip() {
	tl_toggleflip();
}

bool TileLibrary::keydown(char *key) {
	return tl_keydown(key);
}
bool TileLibrary::keywentdown(char *key) {
	return tl_keywentdown(key);
}

bool TileLibrary::buttondown(int button) {
	return tl_buttondown(button);
}
bool TileLibrary::buttonwentdown(int button) {
	return tl_buttonwentdown(button);
}

Point TileLibrary::mouseLoc() {
	Point p(tl_mousex(), tl_mousey());

	return p;
}

void TileLibrary::play(string filename) {
	int which;
	if (filename == "OnHit") {
		which = rand() % 4 + 1;
		filename += to_string(which);
	}
	else if (filename == "OnDeath") {
		which = rand() % 3 + 1;
		filename += to_string(which);
	}
	string str = fPath + filename.c_str() + ".sfs";
	tl_play(const_cast<char*>(str.c_str()));
}

void TileLibrary::renderText(Point start, string text) {
	for (unsigned int i = 0; i < text.length(); i++) {
		rendertile(static_cast<int>(text[i]), start);
		start = start + Point(1, 0);
	}
}
