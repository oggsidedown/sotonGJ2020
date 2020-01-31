#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine
{
	public:
		Game()
		{
			sAppName = "Example";
		}
	public:
		bool OnUserCreate() override
		{
			// Called at the start
			Player player = new Player(0f, 200f);
			return true;
		}
		bool OnUserUpdate(float fElapsedTime) override
		{
			// Called once per frame
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
	Example demo;
	if (demo.Construct(256,240,4,4)
	{
		demo.Start();
	}
	return 0;

