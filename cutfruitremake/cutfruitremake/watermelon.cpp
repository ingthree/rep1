#include "watermelon.h"

Watermelon::Watermelon()
{
    watermelon.load(":/image/resource/sandia.png");
    x = 0;
    y = 0;
    isFree=true;
    isDestroyed = false;
    isMissed=false;
    speed = 1;
//    bomb.Bomb::getFruit('w');
//    bomb.intitial();
}

void Watermelon::updatePosition(){
    if(!isFree)
    {
        x+=speed;
      y+=0;
    }
    if(y>600||x>600||x<0)
    {
        isFree = true;
        isMissed=true;
    }

}


