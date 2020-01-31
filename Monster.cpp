class Monster : public olc::PixelGameEngine
{
private:
	float x;
	float y;
	float speed = 0.1f;
	float direction; // 1 is right, -1 is left
	float gravity = 0.5f; // +ve is down
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
	int getgravity(){
		return this->gravity;
	}
	void sety(int yinput){
		this->y=yinput;
		if(this->y>=719){
			this->y=719;
			this->gravity=0;
		}
		else{
			this->gravity=0.5f;
		}
		if(this->y<0){
			this->y=0;
		}
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
	}
	void setspeed(int speedinput){
		this->speed=speedinput;
	}
	void setdirection(int directioninput){
		this->direction=directioninput;
	}
	void setgravity(int gravityinput){
		this->gravity=gravityinput;
	}
private:
	void readSpriteData(){
	}
};
		
