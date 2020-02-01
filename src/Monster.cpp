#include "include/constants.h"
#include "include/olcPixelGameEngine.h"
#include "Entity.cpp"

class Monster : public Entity
{
private:
	int speed = 2;
	int direction = 1; // 1 is right, -1 is left
public:
	
	using Entity::Entity;
	
	int getdirection()
	{
		return this->direction;
	}
	int getspeed()
	{
		return this->speed;
	}

	void update() override
	{
		// Horizontal boundaries
		if(this->x<0){
				this->x=0;
				this->direction = 1;
		}
		if(this->x>SCREEN_WIDTH){
				this->x=SCREEN_WIDTH;
				this->direction = -1;
		}
		// Vertical boundaries
		if(this->y>=SCREEN_HEIGHT-TILESIZE){
			this->y=SCREEN_HEIGHT-TILESIZE;
		}
		if(this->y<0){
			this->y=0;
		}
	}

	void setSpeed(int speedinput)
	{
		this->speed=speedinput;
		return;
	}
	void setDirection(int directioninput)
	{
		this->direction=directioninput;
		return;
	}
};
		
