#include <iostream>
#include "include/constants.h"
#include "include/olcPixelGameEngine.h"

class Player : public olc::PixelGameEngine 
{
private:
	int x;
	int y;
	int max_vel_x = 5;	
	float y_vel = 0.0f;
	
	bool grounded = false;
	// 1 or -1
	int direction = 1;
	bool moving = false;
	float grav_vel = 0.0f;
	float run_vel = 0.0f; 
public:

	Player(int x, int y)
	{
		//Relative to pixel
		this->x = x;
		this->y = y;
	}

	void Render()
	{
		Draw(getX(), getY(), olc::Pixel(100,100,100));
	}

	int getX()
	{
		return this->x;
	}
	int getY()
	{
		return this->y;
	}
	int getSpeed()
	{
		return this->max_vel_x;
	}	

	void setX(int x)
	{
		this->x = x;
	}
	void setY(int y)
	{
		this->y = y;
	}

	void setGrounded(bool grounded) 
	{
		this->grounded = grounded;	
	}
	void setMoving(bool moving) 
	{
		this->moving = moving;
	}
	void setDirection(int direction)
	{
		this->direction = direction;
	}

	void setXVel(float vel)
	{
		run_vel = vel;
	}
	void setYVel(float vel) 
	{
		y_vel = vel;
	}

	bool getGrounded()
	{
		return grounded;
	}
	int getDirection() 
	{
		return direction;
	}		
	void update() {
		// gravity accelerates
		if(!grounded) 
		{
			setY(getY() + y_vel);
			y_vel += GRAVITY * grav_vel; 	
			grav_vel += 0.01f;
			if(grav_vel > 1.0f) grav_vel = 1.0f;
		} else {
			grav_vel = 0.0f;
		}
		// Some acceleration
		if(moving) {
			run_vel += 0.05f ;
			if(run_vel > 1.0f) run_vel = 1.0f;
		} else {
			run_vel -= 0.05f;
			if(run_vel <= 0.0f) run_vel = 0.0f;
		}
		setX(getX() + (getSpeed() * run_vel * direction));	
	}	
	
	void jump() 
	{
		if(grounded) 
		{
			y_vel = -8.0f;
			setGrounded(false);
		}
	}
	
private:
	void readSpriteData(){
	}
};
