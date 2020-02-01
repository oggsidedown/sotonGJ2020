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
	int map[SCREEN_HEIGHT/8][SCREEN_WIDTH/8];
public:
	Game()
	{
		sAppName = "GameJam";
	}
	bool OnUserCreate() override
	{
		// Called at the start	
		system("canberra-gtk-play -f audio.ogg");
		for(int x = 0; x < ScreenWidth(); x++)
			for(int y = 0; y < ScreenHeight(); y++)
				Draw(x,y,olc::Pixel(50,200,50));
		// Called at the start
		int newLevel = 1;
		int level = 1;
		int paused =0;
		int drawJuice = 40;
		for(int i=0;i<160;i++)
			for(int j=0;j<90;j++)
				map[i][j]=0;
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame
		if(newLevel){
			switch(level++){
				case 1:
					for(i=0;i<SCREEN_WIDTH/8;i++){
						map[i][60]=1;
						DrawSprite(i*8, 60*8, new olc::Sprite("block.png"));
					}
					Goal goal = Goal(1200, 55*8);
					DrawSprite(goal.getx(), goal.gety(), new olc::Sprite("spanner1.png"));
				break;
				case 2:
					FillRect(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-1, olc::Pixel(50,200,50);
					goal.setx(1200);
					goal.sety(55*8);
					for(i=0;i<SCREEN_WIDTH/32;i++){
						map[i][60] = 1;
						DrawSprite(i*8, 60*8, new olc::Sprite("block.png"));
					}
					for(i=SCREEN_WIDTH*3/32;i<SCREEN_WIDTH/8;i++){
						map[i][60] = 1;
						DrawSprite(i*8, 60*8, new olc::Sprite("block.png"));
					}
				break;
			}
			newLevel=0;
		}
		if(player.getX()-5<goal.getx() && player.getX()+5>goal.getx() && player.getY()-5<goal.gety() && player.getY()+5>goal.gety()){
			newLevel=1;
			player.setX(1);
			player.setY(2);
			for(int i=0;i<160;i++)
				for(int j=0;j<90;j++)
					map[i][j]=0;
			
		}
		Draw(this->player.getX(), this->player.getY(), olc::Pixel(100,100,100));
		Draw(monster.getx(), monster.gety(), olc::Pixel(0,100,0));
		if(paused){
			FillRect(SCREEN_WIDTH/2, 5, drawJuice, 10, olc::Pixel(0,100,0)); 
		}
		else{
			fillRect(SCREEN_WIDTH/2, 5, 40, 10, olc::Pixel(50,200,50));
		}
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
		if(GetMouse(0).bHeld && paused && drawJuice>0){
			int closestTileX = GetMouseX()/8;
			int closestTileY = GetMouseY()/8;
			map[closestTileY][closestTileX]=1;
			DrawSprite((closestTileX)*8, (closestTileY)*8, new olc::Sprite("block.png"));
			drawJuice--;
		}
		if(GetKey(olc::Key::ESCAPE)){
			if(paused)
				paused = 0;
			if(!paused)
				paused = 1;
		}	
		int playerTileX = player.getX() / 8;
		int playerTileY = player.getY() / 8;
		for (int i = -3; i < 3; i++)
		{ 
			for (int j = -3; i < 3; i++)
			{
				if(map[playerTileY+i][playerTileX+j]==1)
				{
					DrawSprite((playerTileX+j)*8, (playerTileY+i)*8, new olc::Sprite("block.png"));
				}
			}
		}		

		// monster movement logic
		monster.setx(monster.getx()+monster.getspeed()*monster.getdirection());
		monster.sety(monster.gety() + GRAVITY);
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
