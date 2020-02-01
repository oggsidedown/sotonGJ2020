#ifndef CONSTANTS
#define CONSTANTS
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int GRAVITY = 10;
const int TILESIZE = 16;
struct Tile 
{
	int x;
	int y;
	bool collision;
};

#endif
