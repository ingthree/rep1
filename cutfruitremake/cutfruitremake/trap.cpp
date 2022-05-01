#include "trap.h"

Trap::Trap()
{
    trap.load(":/image/resource/boom.png");
    x = 0;
    y = 0;
    isDestroyed = false;
    speed = 1;
    isFree=true;
//   bomb.getFruit('t');
//   bomb.intitial();
}

void Trap::updatePosition(){
    if(!isFree)
    {
        x+=speed;
        y+=0;
    }
    if(y>600||x>600||x<0)
        isFree = true;
}
