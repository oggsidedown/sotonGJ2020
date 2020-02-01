#define OLC_PGE_APPLICATION
#include <iostream>
#include <map>
#include "olcPixelGameEngine.h"
#include "Player.cpp"
#include "Monster.cpp"
#include "constants.h"

class Game : public olc::PixelGameEngine
{	
private:
	Player player = Player(1, 5);
	Monster monster = Monster(0, 0, 1);
	int map[(int)SCREEN_HEIGHT/8][(int)SCREEN_WIDTH/8];
public:
	Game()
	{
		sAppName = "GameJam";
	}
	bool OnUserCreate() override
	{
		// Called at the start	
		for(int x = 0; x < ScreenWidth(); x++)
			for(int y = 0; y < ScreenHeight(); y++)
				Draw(x,y,olc::Pixel(50,200,50));
		// Called at the start
		for(int i=0;i<(int)SCREEN_HEIGHT/8;i++)
			for(int j=0;j<(int)SCREEN_WIDTH/8;j++)
				map[i][j]=0;
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame
//		Clear(olc::WHITE);	
		Draw(this->player.getX(), this->player.getY(), olc::Pixel(100,100,100));
		Draw(monster.getx(), monster.gety(), olc::Pixel(0,100,0));
		// Movement Logic	
		if(GetKey(olc::Key::RIGHT).bHeld)
		{
			player.setMoving(true);
			player.setDirection(1);
		} else	if(GetKey(olc::Key::LEFT).bHeld) {
			player.setMoving(true);
			player.setDirection(-1);
		} else {
			player.setMoving(false);
		}
		
		if(GetKey(olc::Key::SPACE).bPressed)
		{
			player.jump();
		}
	
		if(player.getY() > SCREEN_HEIGHT - 32) 
		{
			player.setGrounded(true);
			player.setY(SCREEN_HEIGHT - 32);
		}
			
		// update player
		player.update();
	
		// Rendering	
		DrawSprite(this->player.getX(), this->player.getY(), new olc::Sprite("charTEMP.png"));
		// Create tiles when clicking
		int closestTdileX, closestTileY;
		if(GetMouse(0).bHeld){
			int closestTileX = GetMouseX()/8;
			int closestTileY = GetMouseY()/8;
			map[closestTileY][closestTileX]=1;
			DrawSprite((closestTileX)*8, (closestTileY)*8, new olc::Sprite("block.png"));
		}
	
		int playerTileX = player.getX() / 8;
		int playerTileY = player.getY() / 8;
		std::cout << player.getX() << ", " << player.getY() << std::endl;
		for (int i = -4; i <= 4; i++)
		{ 
			for (int j = -4; j <= 4; j++)
			{	
				if(playerTileX+j <= 0) playerTileX = -j;
				if(playerTileX+j >= SCREEN_WIDTH/8) playerTileX = (SCREEN_WIDTH/8)-j;
				if(playerTileY+i <= 0) playerTileY = -i;
				if(playerTileY+i >= SCREEN_HEIGHT/8) playerTileY = (SCREEN_HEIGHT/8)-i;
				
				if(map[playerTileY+i][playerTileX+j]==1)
				{
					DrawSprite((playerTileX+j)*8, (playerTileY+i)*8, new olc::Sprite("block.png"));
				}
			}
		}		

		// monster movement logic
		monster.setx(monster.getx()+monster.getspeed()*monster.getdirection());
		monster.sety(monster.gety() + GRAVITY);
		if(GetKey(olc::C).bPressed && GetKey(olc::CTRL).bHeld) return false;
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
