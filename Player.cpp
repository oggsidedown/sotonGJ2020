#include <iostream>
class Player : public olc::PixelGameEngine 
{
private:
	int x;
	int y;
	int speed = 1;	
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
		return this->speed;
	}	

	void setX(int x)
	{
		this->x = x;
	}
	void setY(int y)
	{
		this->y = y;
	}
private:
	void readSpriteData(){
	}
};
