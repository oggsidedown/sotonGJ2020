#define OLC_PGE_APPLICATION
#include <iostream>
#include <map>
#include "olcPixelGameEngine.h"
#include "Player.cpp"
#include "Monster.cpp"
#include "constants.h"
#include "Goal.cpp"

class Game : public olc::PixelGameEngine
{	
private:
	Player player = Player(1, 5);
	Monster monster = Monster(0, 0, 1);
	int map[(int)SCREEN_HEIGHT/8][(int)SCREEN_WIDTH/8];
	int drawJuiceMax = 120;
	int drawJuice = drawJuiceMax;
	bool paused = false;
	int newLevel = 1;
	int level = 1;
	Goal goal = Goal(1200, 55*8);
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
		for(int i=0;i<SCREEN_HEIGHT/8;i++)
			for(int j=0;j<SCREEN_WIDTH/8;j++)
				map[i][j]=0;
		
		FillRect((SCREEN_WIDTH/2) - drawJuiceMax , 20, drawJuiceMax*2, 40, olc::Pixel(0,0,0)); 
		FillRect((SCREEN_WIDTH/2) - drawJuiceMax, 20, drawJuiceMax*2, 40, olc::Pixel(100,255,50)); 

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame
//		Clear(olc::WHITE);
		if(newLevel){
			switch(level++){
				case 1:
					for(int i=0;i<SCREEN_WIDTH/8;i++){
						map[60][i]=1;
						DrawSprite(i*8, 60*8, new olc::Sprite("block.png"));
					}
					DrawSprite(goal.getx(), goal.gety(), new olc::Sprite("spanner1.png"));
					break;
				case 2:
					FillRect(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-1, olc::Pixel(50,200,50));
					goal.setx(1200);
					goal.sety(55*8);
					for(int i=0;i<SCREEN_WIDTH/32;i++){
						map[i][60] = 1;
						DrawSprite(i*8, 60*8, new olc::Sprite("block.png"));
					}
					for(int i=SCREEN_WIDTH*3/32;i<SCREEN_WIDTH/8;i++){
						map[60][i] = 1;
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
			for(int i=0;i<SCREEN_HEIGHT/8;i++)
				for(int j=0;j<SCREEN_WIDTH/8;j++)
					map[i][j]=0;
			
		}
		Draw(this->player.getX(), this->player.getY(), olc::Pixel(100,100,100));
		Draw(monster.getx(), monster.gety(), olc::Pixel(0,100,0));
		if(paused) {	
			FillRect((SCREEN_WIDTH/2) - drawJuiceMax , 20, drawJuiceMax*2, 40, olc::Pixel(0,0,0)); 
			FillRect((SCREEN_WIDTH/2) - drawJuiceMax, 20, drawJuice*2, 40, olc::Pixel(100,255,50)); 
		}
		else{
//			FillRect(SCREEN_WIDTH/2, 20, 40, 40, olc::Pixel(50,200,50));
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
	
		if(player.getY() > SCREEN_HEIGHT - 16) 
		{
			player.setGrounded(true);
			player.setY(SCREEN_HEIGHT - 16);
		}	
	
		// Rendering	
		DrawSprite(this->player.getX(), this->player.getY(), new olc::Sprite("charTEMP.png"));
		// Create tiles when clicking
		int closestTdileX, closestTileY;
		if(GetMouse(0).bHeld && paused && drawJuice>0){
			int closestTileX = GetMouseX()/8;
			int closestTileY = GetMouseY()/8;
			if (!map[closestTileY][closestTileX]==1){
				map[closestTileY][closestTileX]=1;
				DrawSprite((closestTileX)*8, (closestTileY)*8, new olc::Sprite("block.png"));
				drawJuice--;
			}
		}
		if(GetKey(olc::Key::ESCAPE).bPressed){
			paused = !paused;
		}	

		// Only update player if not paused
		if(!paused) player.update();

		int playerTileX = player.getX() / 8;
		int playerTileY = player.getY() / 8;
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
					/*
					olc::Sprite mysprite(20, 20);
					mysprite.SetPixel(0, 0, olc::RED);
					DrawSprite(20, 20, &mysprite, 2);
					*/	
					DrawSprite((playerTileX+j)*8, (playerTileY+i)*8, new olc::Sprite("block.png"));
				}
			}
		}		

		// Collision Detection
		


		// monster movement logic
		if(!paused) {
			monster.setx(monster.getx()+monster.getspeed()*monster.getdirection());
			monster.sety(monster.gety() + GRAVITY);
		}
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
