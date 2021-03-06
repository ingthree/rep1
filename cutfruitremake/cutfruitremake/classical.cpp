#include "classical.h"
#include <ctime>
#include <cmath>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <iostream>
using namespace std;

Classical::Classical(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose,true);
    resize(600,550);
    Score = 0;
    setAutoFillBackground(true);
    QPalette pal;
    QPixmap pixmap(":/image/resource/background.png");
    pal.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(pal);
    life=new QLabel(this);
    score=new QLabel(this);
    life->setFont(QFont("Algerian",16));
    life->setStyleSheet("QLabel{background:transparent;color:white;}");
    score->setFont(QFont("Algerian",16));
    score->setStyleSheet("QLabel{background:transparent;color:white;}");
    QVBoxLayout *lay = new QVBoxLayout;                     //垂直布局
    lay->addWidget(life);
    lay->addWidget(score);
    setLayout(lay);
    win = false;
    winPlayed = false;
    initial();
}

Classical::~Classical()
{
    setAttribute(Qt::WA_DeleteOnClose,true);
}

void Classical::initial()
{
    Timer.setInterval(10);		//设置定时器间隔，每10ms刷新一次
    fruitRecorded=0;
    startGame();
    srand((unsigned int)time(NULL));
}

void Classical::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
     painter.drawPixmap(myKnife.x,myKnife.y,myKnife.myKnife);
     for(int i=0;i<20;i++)
     {
         if(!banana[i].isFree)
         {
             if(!banana[i].isDestroyed)
                 painter.drawPixmap(banana[i].x,banana[i].y,banana[i].banana);

         }
     }
     for(int i=0;i<20;i++)
     {
         if(!watermelon[i].isFree)
         {
             if(!watermelon[i].isDestroyed)
                 painter.drawPixmap(watermelon[i].x,watermelon[i].y,watermelon[i].watermelon);

         }
     }
     for(int i=0;i<5;i++)
     {
         if(!trap[i].isFree)
         {
             if(!trap[i].isDestroyed)
                 painter.drawPixmap(trap[i].x,trap[i].y,trap[i].trap);

         }
     }
     painter.drawPixmap(myKnife.x,myKnife.y,myKnife.myKnife);
}

void Classical::mouseMoveEvent(QMouseEvent *E){
    int x = E->x()-35;
    int y = E->y()-40;
    if(x>0&&x<575)
        myKnife.x = x;
    if(y>0&&y<505)
        myKnife.y = y;
    update();
}

void Classical::updatePositino()
{
    life->setText(QString(LIFE).arg(myKnife.life));	//随时更新相关信息
        score->setText(QString(SCORE).arg(Score));
        for(int i=0;i<5;i++)
            if(!trap[i].isFree&&!trap[i].isDestroyed){
                trap[i].updatePosition();
            }
        for(int i=0;i<20;i++)
            if(!watermelon[i].isFree&&!watermelon[i].isDestroyed){
                watermelon[i].updatePosition();
            }
        for(int i=0;i<20;i++)
            if(!banana[i].isFree&&!banana[i].isDestroyed){
                banana[i].updatePosition();
            }
}

void Classical::startGame(){

    Timer.start();
       connect(&Timer , &QTimer::timeout,[=](){
           FruitShow();
           updatePositino();
           collisionDetetion();
           update();
           endGame();
       });

}

void Classical::FruitShow()
{
    fruitRecorded++;
    if(fruitRecorded<200)
        return;
    fruitRecorded=0;
    int fruitCount;
    fruitCount=rand()%4+3;
    int trapCount;
    trapCount=rand()%3;
    int watermelonCount;
    watermelonCount=rand()%(fruitCount-trapCount+1);
    int bananaCount;
    bananaCount=fruitCount-trapCount-watermelonCount;
    int j;
    for(int i=0,j=0;i<trapCount&&(i+j<20);j++)
        if(trap[i+j].isFree){
            trap[i+j].isFree = false;
            trap[i+j].x = 0;
            trap[i+j].y = rand()%300+125;
            i++;
        }
    for(int i=0,j=0;i<watermelonCount&&(i+j<20);j++)
        if(watermelon[i+j].isFree){
            watermelon[i+j].isMissed=false;
             watermelon[i+j].isDestroyed=false;
            watermelon[i+j].isFree = false;
            watermelon[i+j].x = 0;
            watermelon[i+j].y = rand()%300+125;
            i++;
        }
    for(int i=0,j=0;i<bananaCount&&(i+j<20);j++)
        if(banana[i+j].isFree){
            banana[i+j].isMissed=false;
             banana[i+j].isDestroyed=false;
            banana[i+j].isFree = false;
            banana[i+j].x = 0;
            banana[i+j].y = rand()%300+125;
            i++;
        }
}

void Classical::collisionDetetion()
{
    for(int i=0;i<20;i++)
    {
        if(!banana[i].isFree&&!banana[i].isDestroyed)
        {
            if(getDistanceBAK(banana[i], myKnife)<30)
             {
                Score++;
                banana[i].isDestroyed=true;
                banana[i].isFree=true;

             }
        }
        else if(banana[i].isMissed)
        {
            myKnife.life--;
        }

    }


    for(int i=0;i<20;i++)
    {
        if(!watermelon[i].isFree&&!watermelon[i].isDestroyed)
        {
            if(getDistanceWAK(watermelon[i], myKnife)<30)
            {
                Score++;
                watermelon[i].isDestroyed=true;
                watermelon[i].isFree=true;

            }
            else if(watermelon[i].isMissed)
            {
                myKnife.life--;
            }
        }
    }

    for(int i=0;i<5;i++)
    {
        if(!trap[i].isFree&&!trap[i].isDestroyed)
        {
            if(getDistanceTAK(trap[i], myKnife)<30)
            {
            myKnife.life--;
            trap[i].isDestroyed=true;


            }
        }
    }
}

void Classical::endGame(){
    if(myKnife.life==0&&!myKnife.isPlayed){
        myKnife.isPlayed = true;
        EndGame *e = new EndGame(Score);
        cout<<myKnife.life;
        cout<<myKnife.isPlayed;
        cout<<winPlayed;
        e->show();
        this->close();
    }
}
int Classical::getDistanceBAK(Banana B,Knife K)
{
    return sqrt((B.x-20-K.x)*(B.x-20-K.x)+(B.y+20-K.y)*(B.y+20-K.y));
}

int Classical::getDistanceWAK(Watermelon W,Knife K)
{
    return sqrt((W.x-20-K.x)*(W.x-20-K.x)+(W.y+20-K.y)*(W.y+20-K.y));
}

int Classical::getDistanceTAK(Trap T,Knife K)
{
    return sqrt((T.x-20-K.x)*(T.x-20-K.x)+(T.y+20-K.y)*(T.y+20-K.y));
}
