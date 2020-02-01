#include "constants.h"
class Goal : public olc::PixelGameEngine
{
private:
	int x;
	int y;
public:
	Goal(float x, float y)
	{
		//relative to pixel
		this->x = x;
		this->y = y;
	}
	int gety(){
		return this->y;
	}
	int getx(){
		return this->x;
	}
	void sety(int yinput){
		this->y=yinput;
		if(this->y>=SCREEN_HEIGHT-32){
			this->y=SCREEN_HEIGHT-32;
		}
		if(this->y<0){
			this->y=0;
		}
		return;
	}
	void setx(int xinput){
		this->x=xinput;
		if(this->x<0){
				this->x=0;
				this->direction = 1;
		}
		if(this->x>1279){
				this->x=1279;
				this->direction = -1;
		}
		return;
	}
private:
	void readSpriteData(){
	}
};
