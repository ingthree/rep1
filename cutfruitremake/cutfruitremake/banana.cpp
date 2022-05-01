#include "banana.h"

Banana::Banana()
{
    banana.load(":/image/resource/peach.png");
    x = 0;
    y = 0;
//    bomb.Bomb::getFruit('b');
//    bomb.intitial();
    isFree=true;
    isMissed =false;
    isDestroyed = false;
    speed = 1;
}

void Banana::updatePosition(){
    if(!isFree)
    {
        x+=speed;
         y+=0;
    }
    if(y>600||x>600||x<0)
    {
        isFree = true;
        isMissed =true;
    }

}
