#include "constants.h"
class Monster : public olc::PixelGameEngine
{
private:
	int x;
	int y;
	int speed = 2;
	int direction; // 1 is right, -1 is left
public:
	Monster(float x, float y, float direction)
	{
		//relative to pixel
		this->x = x;
		this->y = y;
		this->direction = direction;
	}
	int gety(){
		return this->y;
	}
	int getx(){
		return this->x;
	}
	int getdirection(){
		return this->direction;
	}
	int getspeed(){
		return this->speed;
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
	void setspeed(int speedinput){
		this->speed=speedinput;
		return;
	}
	void setdirection(int directioninput){
		this->direction=directioninput;
		return;
	}
private:
	void readSpriteData(){
	}
};
		
