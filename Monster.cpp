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
	bool OnUserUpdate(float fElapsedTime) override
	{
		//movement
		this->x += this->speed*this->direction;
		this->y += this->gravity;
		if(this->x<0){
			this->x=0;
			this->direction = 1;
		}
		if(this->x>1279){
			this->x=1279;
			this->direction = -1;
		}
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
		return true;
	}
	/*void Render()
	{
		// draws a pixel for the monster
		Draw(this.x,this.y, olc::Pixel(100,100,100));
	}*/
private:
	void readSpriteData(){
	}
};
		