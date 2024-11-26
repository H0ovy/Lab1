#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
    Snake(){};
    int X, Y;
    void SetApplePos(int x, int y);
    int GetApplePosX(){
        return AppleX;
    }
    int GetApplePosY(){
        return AppleY;
    }
    void SetArea(int x, int y);
    int GetAreaPosX(){
        return AreaX;
    }
    int GetAreaPosY(){
        return AreaY;
    }

private:
    int AppleX, AppleY;
    int AreaX, AreaY;
};

#endif