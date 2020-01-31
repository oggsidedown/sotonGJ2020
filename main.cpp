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
		// Called at the start
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame
		for(int x = 0; x < ScreenWidth(); x++)
			for(int y = 0; y < ScreenHeight(); y++)
				Draw(x,y,olc::Pixel(255,0,0));
		Draw(this->player.getX(), this->player.getY(), olc::Pixel(100,100,100));
		
		// Movement Logic	
		if(GetKey(olc::Key::LEFT).bHeld)
		{
			player.setX(player.getX() - player.getSpeed());
			if(player.getX() < 0) 
			{
				player.setX(0);
			}
		}
		if(GetKey(olc::Key::RIGHT).bHeld)
		{
			player.setX(player.getX() + player.getSpeed());
		}
		if(GetMouse(0)){
			Draw(GetMouseX(), GetMouseY(), olc::Pixel(0,0,100));
		}
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
