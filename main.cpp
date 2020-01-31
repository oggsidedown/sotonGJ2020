#define OLC_PGE_APPLICATION
#include <iostream>
#include "olcPixelGameEngine.h"
#include "Player.cpp"
#include "constants.h"

class Game : public olc::PixelGameEngine
{	
private:
	Player player = Player(1, 5);
public:
	Game()
	{
		sAppName = "GameJam";
	}
	bool OnUserCreate() override
	{
<<<<<<< HEAD
		// Called at the start	
		for(int x = 0; x < ScreenWidth(); x++)
			for(int y = 0; y < ScreenHeight(); y++)
				Draw(x,y,olc::Pixel(50,200,50));
=======
		// Called at the start
		int map[160][90]; //0 means nothing there, 1 means block there
		int i, j;
		for(i=0;i<160;i++)
			for(j=0;j<90;j++)
				map[i][j]=0;
>>>>>>> 184a417ec8802c1781d35a2c996d5b802a3c84d7
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame
<<<<<<< HEAD
		
=======
		int closestTileX, closestTileY;
		for(int x = 0; x < ScreenWidth(); x++)
			for(int y = 0; y < ScreenHeight(); y++)
				Draw(x,y,olc::Pixel(255,0,0));
		Draw(this->player.getX(), this->player.getY(), olc::Pixel(100,100,100));
		Draw(monster.getx(), monster.gety(), olc::Pixel(0,100,0);
>>>>>>> 184a417ec8802c1781d35a2c996d5b802a3c84d7
		// Movement Logic	
		if(GetKey(olc::Key::LEFT).bHeld)
		{
			player.setX(player.getX() - player.getSpeed());
			if(player.getX() < 0) player.setX(0);
		}
		if(GetKey(olc::Key::RIGHT).bHeld)
		{
			player.setX(player.getX() + player.getSpeed());
			if(player.getX() > SCREEN_WIDTH) player.setX(SCREEN_WIDTH);
		}
		
		if(player.getY() > SCREEN_HEIGHT - 32) 
		{
			player.setGrounded(true);
			player.setY(SCREEN_HEIGHT - 32);
		}

<<<<<<< HEAD
		// Rendering	
		DrawSprite(this->player.getX(), this->player.getY(), new olc::Sprite("charTEMP.png"));
=======
		if(GetMouse(0)){
			closestTileX = getMouseX()/8;
			closestTileY = getMouseY()/8;
			map[closestTileX][closestTileY]=1;
			DrawSprite(closestTileX*8, closestTileY*8, new olc::Sprite("block.png"));
		}

		// monster movement logic
		monster.setx(monster.getx()+monster.getspeed()*monster.getdirection());
		monster.sety(monster.gety + monster.getgravity);
>>>>>>> 184a417ec8802c1781d35a2c996d5b802a3c84d7
		return true;
	}
	bool OnUserDestroy() override
	{
		// Called when window is closed
		return true;
	}
};

int main()
{
	Game demo;
	if (demo.Construct(SCREEN_WIDTH,SCREEN_HEIGHT,1,1))
		demo.Start();
	return 0;
}
