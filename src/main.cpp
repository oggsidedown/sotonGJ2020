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
	int checkX, checkY;
	bool throughWall = false;
	float firstWall;
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
	void update(int *inputmap[SCREEN_HEIGHT/TILESIZE][SCREEN_WIDTH/TILESIZE]) override
	{
		// Some acceleration
		if(moving) {
			run_vel += 0.05f ;
			if(run_vel > 1.0f) run_vel = 1.0f;
		} else {
			run_vel -= 0.05f;
			if(run_vel <= 0.0f) run_vel = 0.0f;
		}
		checkX = getX() + (getSpeed() * run_vel * direction);
		checkY = getY() + y_vel;
		for(int i=0;i<50;i++){
			if(inputmap[(int)(getY()+i*(checkY-getY())/50)][(int)(getX()+i*(checkX-getX())/50)]==1){
				if(!throughWall)
					firstWall = i;
				throughWall=true;
			}
		}
		// gravity accelerates
		if(!grounded) 
		{
			if(!throughWall){
				setY(getY() + y_vel);
			}
			else{
				setY((int)(getY()+(checkY-getY())*i/50));
			}
			y_vel += GRAVITY * grav_vel; 	
			grav_vel += 0.01f;
			if(grav_vel > 1.0f) grav_vel = 1.0f;
		} else {
			grav_vel = 0.0f;
		}
		if(!throughWall){
			setX(getX() + (getSpeed() * run_vel * direction));
		}
		else{
			setX((int)(getX()+(checkX-getX())*firstWall/50));
		}
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
