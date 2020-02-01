#include "olcPixelGameEngine.h"
#define SPRITE_HEIGHT 16
#define SPRITE_WIDTH 16

class SpriteSheet {
	private:
		Sprite spritesheet;
	public:
		SpriteSheet(std::string sImageFile);
		Sprite crop(int32_t x, int32_t y, int32_t w, int32_t h);
		void loadSprites();
};

SpriteSheet::SpriteSheet(std::string sImageFile){
	spritesheet.LoadFromFile(sImageFile);
}

SpriteSheet::Sprite crop(int32_t x, int32_t y, int32_t w, int32_t h){
	//Takes subimage from spritesheet, starting at (x, y) with width w and height h
	Sprite subimage(w,h);
	for(int a=0; a<h; a++){
		for(int b=0; b<w; b++){
			subimage.SetPixel(b, a, spritesheet.GetPixel(x+b, y+a));
		}
	}
	return subimage;
}

class Assets{
	public static:
		Sprite block, ladder, goal;
		Sprite spanner[4], battery;
		Sprite waluigi[2][4], gnw[2];
	public:
		void loadSprites();
};

Assets::void loadSprites(){
	SpriteSheet ss("spritesheet_transparent.pdf");
	
	//platforms
	block = ss.crop(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
	ladder = ss.crop(SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
	goal = ss.crop(SPRITE_WIDTH*2, 0, SPRITE_WIDTH, SPRITE_HEIGHT);
	
	//projectiles
	for(int i=0; i<spanner.size(); i++)
		spanner[i] = ss.crop(SPRITE_WIDTH*i, SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
	
	//power-ups
	battery = ss.crop(SPRITE_WIDTH*4, SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
	
	//character
	for(int j=0; j<waluigi.size(); j++)
		for(int i=0; i<waluigi[j].size(); i++)
			waluigi[j][i] = ss.crop(SPRITE_WIDTH*i, SPRITE_HEIGHT*(j+2), SPRITE_WIDTH, SPRITE_HEIGHT*(j+1));
	
	//enemies
	for(int i=0; i<gnw.size(); i++)
		gnw[i] = ss.crop(SPRITE_WIDTH*i, SPRITE_HEIGHT*5, SPRITE_WIDTH, SPRITE_HEIGHT);
	
}