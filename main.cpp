#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Example : public olc::PixelGameEngine
{
	public:
		Example()
		{
			sAppName = "Example";
		}
	public:
		bool OnUserCreate() override
		{
			// Called at the start
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
}
