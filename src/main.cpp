#define OLC_PGE_APPLICATION
#include <iostream>
#include <vector>
#include "include/olcPixelGameEngine.h"
#include "include/constants.h"
#include "Player.cpp"
#include "Monster.cpp"
#include "Goal.cpp"
#include "Entity.cpp"

class Game : public olc::PixelGameEngine
{	
private:
	Player player = Player(100, 150);
	Monster monster = Monster(20, 20);
	std::vector<Entity*> entities;
	int map[(int)SCREEN_HEIGHT/TILESIZE][(int)SCREEN_WIDTH/TILESIZE];
	int drawJuiceMax = 120;
	int drawJuice = drawJuiceMax;
	bool paused = false;
	int newLevel = 1;
	int level = 1;
	Goal goal = Goal(1200, 25*TILESIZE); 
	olc::Sprite fact_sprite = olc::Sprite("assets/factory.png");

private:
	void checkInputs() 
	{
		// Movement Logic horizontal	
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
		
		// Causes the player to jump
		if(GetKey(olc::Key::SPACE).bHeld)
		{
			player.jump();
		}
	
		// Handle player vertical movement
		if(player.getY() > SCREEN_HEIGHT - TILESIZE) 
		{
			player.setGrounded(true);
			player.setY(SCREEN_HEIGHT - TILESIZE);
		}	

		// pause the game which allows drawing of tiles
		if(GetKey(olc::Key::ESCAPE).bPressed){
			paused = !paused;
		}	

		//if(GetKey(olc::C).bPressed && GetKey(olc::CTRL).bHeld) return false;


	}

	void createTiles() 
	{
		// Create tiles when clicking
		int closestTileX, closestTileY;
		if(GetMouse(0).bHeld && paused && drawJuice>0){
			int closestTileX = GetMouseX()/TILESIZE;
			int closestTileY = GetMouseY()/TILESIZE;
			if (!(map[closestTileY][closestTileX]==1)){
				map[closestTileY][closestTileX]=1;
				DrawSprite((closestTileX)*TILESIZE, (closestTileY)*TILESIZE, new olc::Sprite("assets/block.png"));
				drawJuice--;
			}
		}
	}

	void Render() 
	{
		// Rendering
			// Redraw the background and tiles
		int offset = 4;
		for(auto &e:entities) 
		{
			int tileX = (int)(e->getX() / TILESIZE);
			int tileY = (int)(e->getY() / TILESIZE);
			// background
			DrawPartialSprite((tileX-offset)*TILESIZE,(tileY-offset)*TILESIZE, &fact_sprite, (tileX-offset)*TILESIZE,(tileY-offset)*TILESIZE,TILESIZE*offset*2,TILESIZE*offset*2);	

			// redraw tiles near entities
			for (int i = -offset*2; i <= offset*2; i++)
			{ 
				for (int j = -offset*2; j <= offset*2; j++)
				{	
					if(tileX+j <= 0) tileX = -j;
					if(tileX+j >= SCREEN_WIDTH/TILESIZE) tileX = (SCREEN_WIDTH/TILESIZE)-j;
					if(tileY+i <= 0) tileY = -i;
					if(tileY+i >= SCREEN_HEIGHT/TILESIZE) tileY = (SCREEN_HEIGHT/TILESIZE)-i;
					
					if(map[tileY+i][tileX+j]==1)
					{
						DrawSprite((tileX+j)*TILESIZE, (tileY+i)*TILESIZE, new olc::Sprite("assets/block.png"));
					}
				}
			}	
		}
		
			// Draw the player
		DrawSprite(this->player.getX()-TILESIZE, this->player.getY()-TILESIZE, new olc::Sprite("assets/waluigi_right1.png"), 2);
			// Draw the monster
		DrawPartialSprite(monster.getX(), monster.getY(), new olc::Sprite("assets/spritesheet_transparent.png"), 0, 5*16, 16, 16, 2);
			// draw juice meter
		FillRect((SCREEN_WIDTH/2) - drawJuiceMax , 20, drawJuiceMax*2, 40, olc::Pixel(0,0,0)); 
		FillRect((SCREEN_WIDTH/2) - drawJuiceMax, 20, drawJuice*2, 40, olc::Pixel(100,255,50));
	 
	}

public:
	Game()
	{
		sAppName = "GameJam";
	}
	bool OnUserCreate() override
	{

		entities.push_back((Entity*)&player);
		entities.push_back((Entity*)&monster);
		// Called at the start	
		system("canberra-gtk-play -f assets/audio.ogg");
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
		if(newLevel){
			switch(level++){
				case 1:
					for(int i=0;i<SCREEN_WIDTH/TILESIZE;i++)
						for(int j=0;j<SCREEN_HEIGHT/TILESIZE;j++)
							DrawPartialSprite(i*TILESIZE,j*TILESIZE, &fact_sprite, i*TILESIZE,j*TILESIZE,TILESIZE,TILESIZE);
					for(int i=0;i<SCREEN_WIDTH/TILESIZE;i++){
						map[10][i]=1;
						DrawSprite(i*TILESIZE, 10*TILESIZE, new olc::Sprite("assets/block.png"));
					}
					DrawSprite(goal.getx(), goal.gety(), new olc::Sprite("assets/spanner1.png"));
					break;
				case 2:
					FillRect(0,0,SCREEN_WIDTH-1, SCREEN_HEIGHT-1, olc::Pixel(50,200,50));
					goal.setx(1200);
					goal.sety(25*TILESIZE);
					for(int i=0;i<SCREEN_WIDTH/TILESIZE;i++){
						map[i][20] = 1;
						DrawSprite(i*TILESIZE, 20*TILESIZE, new olc::Sprite("assets/block.png"));
					}
					for(int i=SCREEN_WIDTH*3/TILESIZE;i<SCREEN_WIDTH/TILESIZE;i++){
						map[30][i] = 1;
						DrawSprite(i*TILESIZE, 20*TILESIZE, new olc::Sprite("assets/block.png"));
					}
					break;
			}
			newLevel=0;
		}
		// Check if player reaches goal
		if(player.getX()-5<goal.getx() && player.getX()+5>goal.getx() && player.getY()-5<goal.gety() && player.getY()+5>goal.gety()){
			newLevel=1;
			player.setX(1);
			player.setY(2);
			for(int i=0;i<SCREEN_HEIGHT/TILESIZE;i++)
				for(int j=0;j<SCREEN_WIDTH/TILESIZE;j++)
					map[i][j]=0;
		}

		checkInputs();

		Render();

		createTiles();

		// Only update player if not paused
		if(!paused) 
		{
			for(auto &e:entities) 
			{
				e->update(map);
			}
			
			// monster update
			monster.setX(monster.getX()+monster.getspeed()*monster.getdirection());
			monster.setY(monster.getY() + GRAVITY);
		}
		// Collision Detection

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
