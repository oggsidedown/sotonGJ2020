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
	Player player = Player(100, 450);
	Monster monster = Monster(0, 0, 1);
	int map[(int)SCREEN_HEIGHT/TILESIZE][(int)SCREEN_WIDTH/TILESIZE];
	int drawJuiceMax = 120;
	int drawJuice = drawJuiceMax;
	bool paused = false;
	int newLevel = 1;
	int level = 1;
	Goal goal = Goal(1200, 25*TILESIZE);
	olc::Sprite fact_sprite = olc::Sprite("factory.png");
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
		for(int i=0;i<SCREEN_HEIGHT/TILESIZE;i++)
			for(int j=0;j<SCREEN_WIDTH/TILESIZE;j++)
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
					for(int i=0;i<SCREEN_WIDTH/TILESIZE;i++)
						for(int j=0;j<SCREEN_HEIGHT/TILESIZE;j++)
							DrawPartialSprite(i*TILESIZE,j*TILESIZE, &fact_sprite, i*TILESIZE,j*TILESIZE,TILESIZE,TILESIZE);
					for(int i=0;i<SCREEN_WIDTH/TILESIZE;i++){
						map[30][i]=1;
						DrawSprite(i*TILESIZE, 30*TILESIZE, new olc::Sprite("block.png"));
					}
					DrawSprite(goal.getx(), goal.gety(), new olc::Sprite("spanner1.png"));
					break;
				case 2:
					FillRect(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-1, olc::Pixel(50,200,50));
					goal.setx(1200);
					goal.sety(25*TILESIZE);
					for(int i=0;i<SCREEN_WIDTH/TILESIZE;i++){
						map[i][30] = 1;
						DrawSprite(i*TILESIZE, 30*TILESIZE, new olc::Sprite("block.png"));
					}
					for(int i=SCREEN_WIDTH*3/TILESIZE;i<SCREEN_WIDTH/TILESIZE;i++){
						map[30][i] = 1;
						DrawSprite(i*TILESIZE, 30*TILESIZE, new olc::Sprite("block.png"));
					}
					break;
			}
			newLevel=0;
		}
		if(player.getX()-5<goal.getx() && player.getX()+5>goal.getx() && player.getY()-5<goal.gety() && player.getY()+5>goal.gety()){
			newLevel=1;
			player.setX(1);
			player.setY(2);
			for(int i=0;i<SCREEN_HEIGHT/TILESIZE;i++)
				for(int j=0;j<SCREEN_WIDTH/TILESIZE;j++)
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
	
		if(player.getY() > SCREEN_HEIGHT - 32) 
		{
			player.setGrounded(true);
			player.setY(SCREEN_HEIGHT - 32);
		}	
	
		// Rendering	
		DrawSprite(this->player.getX(), this->player.getY(), new olc::Sprite("charTEMP.png"));
		// Create tiles when clicking
		int closestTdileX, closestTileY;
		if(GetMouse(0).bHeld && paused && drawJuice>0){
			int closestTileX = GetMouseX()/TILESIZE;
			int closestTileY = GetMouseY()/TILESIZE;
			if (!map[closestTileY][closestTileX]==1){
				map[closestTileY][closestTileX]=1;
				DrawSprite((closestTileX)*TILESIZE, (closestTileY)*TILESIZE, new olc::Sprite("block.png"));
				drawJuice--;
			}
		}
		if(GetKey(olc::Key::ESCAPE).bPressed){
			paused = !paused;
		}	

		// Only update player if not paused
		if(!paused) player.update();

		int playerTileX = player.getX() / TILESIZE;
		int playerTileY = player.getY() / TILESIZE;
		for (int i = -4; i <= 4; i++)
		{ 
			for (int j = -4; j <= 4; j++)
			{	
				if(playerTileX+j <= 0) playerTileX = -j;
				if(playerTileX+j >= SCREEN_WIDTH/TILESIZE) playerTileX = (SCREEN_WIDTH/TILESIZE)-j;
				if(playerTileY+i <= 0) playerTileY = -i;
				if(playerTileY+i >= SCREEN_HEIGHT/TILESIZE) playerTileY = (SCREEN_HEIGHT/TILESIZE)-i;
				
				if(map[playerTileY+i][playerTileX+j]==1)
				{
					/*
					olc::Sprite mysprite(20, 20);
					mysprite.SetPixel(0, 0, olc::RED);
					DrawSprite(20, 20, &mysprite, 2);
					*/	
					DrawSprite((playerTileX+j)*TILESIZE, (playerTileY+i)*TILESIZE, new olc::Sprite("block.png"));
				}
			}
		}		

		// Collision Detection
			// Horizontal LEFT
		if((map[playerTileY][playerTileX-1] == 1 || map[playerTileY+1][playerTileX-1] == 1) && player.getDirection() == -1) player.setXVel(0.0f); 
			// Horizontal RIGHT
		if((map[playerTileY][playerTileX+2] == 1 || map[playerTileY+1][playerTileX+2] == 1) && player.getDirection() == 1) player.setXVel(0.0f);
			// Vertical UP 
		if((map[playerTileY-1][playerTileX] == 1 || map[playerTileY-1][playerTileX+1] == 1)) player.setYVel(1.0f);
			// Vertical DOWN 
		if((map[playerTileY+2][playerTileX] == 1 || map[playerTileY+2][playerTileX+1] == 1) && player.getGrounded() == false)
		{
			player.setYVel(0.0f);
			player.setGrounded(true);
		} else {
			player.setGrounded(false);
		} 

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
