#include <iostream>
#include "include/constants.h"
#include "include/olcPixelGameEngine.h"
#include "Entity.cpp"

class Player : public Entity
{
private:
	int max_vel_x = 5;	
	float y_vel = 0.0f;
	
	bool grounded = false;
	// 1 or -1
	int direction = 1;
	bool moving = false;
	float grav_vel = 0.0f;
	float run_vel = 0.0f; 
public:

	using Entity::Entity;

	int getSpeed()
	{
		return this->max_vel_x;
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
	void update() override
	{
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
			y_vel = -12.0f;
			setGrounded(false);
		}
	}
	
private:
	void readSpriteData(){
	}
};
