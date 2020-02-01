#ifndef ENTITY
#define ENTITY
class Entity
{
    protected:
        int x, y;
    public: 

        Entity(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        virtual void update() = 0;

        int getX()
        {
            return x;
        }
        int getY()
        {
            return y;
        }
        void setX(int x)
        {
            this->x = x;
        }
        void setY(int y)
        {
            this->y = y;
        }
};
#endif