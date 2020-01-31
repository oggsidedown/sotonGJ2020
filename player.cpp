class Player : public olc::PixelGameEngine 
{
private:
	float x;
	float y;
	float speed = 0.5f;	
public:
	Player(float x, float y)
	{
		//Relative to pixel
		this.x = x;
		this.y = y;
	}

	bool OnUserUpdate(float fElapsedTIme) override 
	{
		//Movement
		if(GetKey(olc::Key::LEFT).bHeld)
		{
			this.x -= this.speed;
			if(this.x < 0) 
			{
				this.x = 0;
			}
		}
		if(GetKey(olc::Key::RIGHT).bHeld)
		{
			this.x -= this.speed;
			if(this.x > 100) 
			{
				this.x = 100;
			}
		}
		return true;
	}

	void Render()
	{
		//draw to sprite to screen here
		Draw(this.x, this.y, olc::Pixel(100,100,100));
	}
private:
	void readSpriteData(){
	}
};
