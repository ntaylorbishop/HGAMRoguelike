#pragma once

// tilelib: very simple tile library to create grid based games, by Wouter van Oortmerssen.
// use SDL, OpenGL, and code from sfxr & picopng

extern void tl_init(char *windowtitle,   
                    int width,              // initial size, window is resizable, be sure to use tl_xres() below when rendering
                    int height, 
                    char *name,             // base name of the tile textures
                    int tilesz = 32,        // size in pixels of tiles contained in textures
                    int numtex = 1);        // number of textures to load, system will load name_N.png, where N = 0..numtex-1

extern void tl_shutdown(char *why = NULL);  // if not NULL, will pop up a messagebox

extern void tl_framestart(int col = 0);     // call this once at the start of your main loop

extern void tl_rendertile(int tile,         // the Nth tile, where N is counted left to right, then top to bottom
                          int tx,           // coordinates are relative to the current scale, and out of bounds coordinates are automatically clipped
                          int ty);

extern int tl_xres();                       // size of screen in tiles, i.e. for tiles of size 32 on a 800 wide window, this returns 25
extern int tl_yres();

extern void tl_color(int col = 0xFFFFFFFF); // color in RGBA format, modulates the next call to tl_rendertile()
extern void tl_scale(int sc = 1);           // rendering scale, usually 1, 2, or 4 (which render using textures 0, 1 and 2)
void tl_rotation(int rot = 0);              // rotation 0..3 (up, left, down, right)
void tl_toggleflip();                       // mirrors along the Y axis

extern bool tl_keydown(char *key);          // true if the key is current being held down 
extern bool tl_keywentdown(char *key);      // true if the key went down this frame

/* possible values for key:

   backspace tab clear return pause escape space delete
   ! " # $ & ' ( ) * + , - . / 0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ [ \ ] ^ _ ` 
   a b c d e f g h i j k l m n o p q r s t u v w x y z
   [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [.] [/] [*] [-] [+]
   enter equals up down right left insert home end page up page down
   f1 f2 f3 f4 f5 f6 f7 f8 f9 f10 f11 f12 f13 f14 f15
   numlock caps lock scroll lock right shift left shift right ctrl left ctrl right alt left alt
   right meta left meta left super right super alt gr compose help print screen sys req break
   menu power euro undo
*/

extern bool tl_buttondown(int button = 1);          // left = 1 / right = 2 / middle = 3
extern bool tl_buttonwentdown(int button = 1);

extern int tl_mousex();                     // coordinates relative to the current scale (!)
extern int tl_mousey();

extern void tl_play(char *sfs_filename);    // play sound sample according to .sfs file
                                            // create them with: http://www.drpetter.se/project_sfxr.html

