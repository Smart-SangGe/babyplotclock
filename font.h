/*
* Author: Pan Qiang
*/
//#include "duoji.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define PI 3.14159

//以下三个舵机编号需修改�?
/* PWM declaration */
#define pwm0 11
#define pwm1 13

/* GPIO declaration */
#define GPIO_PIN_1 15

//以下三个宏需修改为角度：
#define LIFT0 180 // 1350 落笔写字
#define LIFT1 90  // 1250 写字时抬臂动�? 一般比lift0 �?100左右
#define LIFT2 30  // 1100 高抬笔架

int servoLift = LIFT2;

struct change_angle//左右舵机的转动角度
{
    float a1=0;
    float a2=0;
}change_angle;
float angle1=90,angle2=90;//左右舵机的初始角度
//抬笔函数，调整笔的高�? 0，落笔写字； 1，书写时抬笔�? 2，太高笔用于插板�?
/*void lift(int lift)
{
    switch (lift)
    {
        // room to optimize !

    case 0:

        if (servoLift >= LIFT0)
        {
            while (servoLift >= LIFT0)
            {
                servoLift--;
                // servo1.writeMicroseconds(servoLift);
                // delayMicroseconds(LIFTSPEED);
                //rotate(pwm0, LIFT0); // 抬臂角度需修改,继电器通电
                //usleep(400000);
            }
        }
        else
        {
            while (servoLift <= LIFT0)
            {
                servoLift++;
                // servo1.writeMicroseconds(servoLift);
                // delayMicroseconds(LIFTSPEED);
                //rotate(pwm0, LIFT0); // 抬臂角度需修改
                //usleep(400000);
            }
        }

        break;

    case 1:

        if (servoLift >= LIFT1)
        {
            while (servoLift >= LIFT1)
            {
                servoLift--;
                // servo1.writeMicroseconds(servoLift);
                // delayMicroseconds(LIFTSPEED);
                //rotate(pwm0, LIFT1); // 抬臂角度需修改
                //usleep(400000);
            }
        }
        else
        {
            while (servoLift <= LIFT1)
            {
                servoLift++;
                // servo1.writeMicroseconds(servoLift);
                // delayMicroseconds(LIFTSPEED);
                //rotate(pwm0, LIFT1); // 抬臂角度需修改
                //usleep(400000);
            }
        }

        break;

    case 2:

        if (servoLift >= LIFT2)
        {
            while (servoLift >= LIFT2)
            {
                servoLift--;
                // servo1.writeMicroseconds(servoLift);
                // delayMicroseconds(LIFTSPEED);
                //rotate(pwm0, LIFT2); // 抬臂角度需修改
                //usleep(400000);
            }
        }
        else
        {
            while (servoLift <= LIFT2)
            {
                servoLift++;
                // servo1.writeMicroseconds(servoLift);
                // delayMicroseconds(LIFTSPEED);
                //rotate(pwm0, LIFT2); // 抬臂角度需修改
                //usleep(400000);
            }
        }
        break;
    }
}*/

struct angle
{
    float angle1;
    float angle2;
} angle={180,90};
//左右舵机的初始坐�?
#define O1X 22
#define O1Y -25
#define O2X 47
#define O2Y -25
//机械臂长�?
#define L1 35
#define L2 57.1
#define L3 14
//点的坐标
struct point
{
    float Tx;
    float Ty;
} point = {0, 0};
//液晶格式的数字，记得修改单位
float LC_Num0[][100] = {
    {7, 32.5, 10.5, 32.5, 10.5, 22.5, 7, 22.5, 7, 32.5, 0},
    {7, 32.5, 7, 22.5, 0},
    {7, 32.5, 10.5, 32.5, 10.5, 27.5, 7, 27.5, 7, 22.5, 10.5, 22.5, 0},
    {7, 32.5, 10.5, 32.5, 10.5, 27.5, 7, 27.5, 10.5, 27.5, 10.5, 22.5, 7, 22.5, 0},
    {7, 32.5, 7, 27.5, 10.5, 27.5, 10.5, 32.5, 10.5, 22.5, 0},
    {10.5, 32.5, 7, 32.5, 7, 27.5, 10.5, 27.5, 10.5, 22.5, 7, 22.5, 0},
    {10.5, 32.5, 7, 32.5, 7, 22.5, 10.5, 22.5, 10.5, 27.5, 7, 27.5, 0},
    {7, 32.5, 10.5, 32.5, 10.5, 22.5, 0},
    {7, 27.5, 7, 32.5, 10.5, 32.5, 10.5, 22.5, 7, 22.5, 7, 27.5, 10.5, 27.5, 0},
    {10.5, 27.5, 7, 27.5, 7, 32.5, 10.5, 32.5, 10.5, 22.5, 7, 22.5, 0},
};

//笔擦的坐标位置，摆臂调节好后，如不能对准笔擦可以微调此参数，单位毫米
float const rubberx = 82, rubbery = 46;
float lastx = rubberx;
float lasty = rubbery;
//运笔至坐标位�?
int readl(int num, int flag, int place) //读取数字库的坐标
{
    int i, j;
    point.Tx = LC_Num0[num][flag * 2] + (place - 1) * 17.5;
    point.Ty = LC_Num0[num][flag * 2 + 1];
    if (LC_Num0[num][flag * 2] == 0)
        return 0;
    return 1;
}
float return_angle(float a, float b, float c) //计算a与c的夹角并返回夹角的�?
{
    return acos(fminl(fmaxl((a * a + c * c - b * b) / (2 * a * c),-1.0),1.0));
}
void set_XY(float Tx, float Ty) //根据坐标返回给angle结构体两个角�?
{
    // delay(1);
    float dx, dy, c, a1, a2, Hx, Hy, angle1, angle2;

    dx = Tx - O1X; //与做舵机x坐标的差�?
    dy = Ty - O1Y; // y坐标的差�?

    c = sqrt(dx * dx + dy * dy);  //与左舵机的距�?
    a1 = atan2(dy, dx);           //返回以弧度表示的 y/x 的反正切得到角度
    a2 = return_angle(L1, L2, c); //机械臂一与xo1的夹�?
    change_angle.a1=(a1+a2-angle.angle1)/PI*180;
    angle.angle1=a1+a2;
    rotate(pwm1,angle1-change_angle.a1);
    
    a2 = return_angle(L2, L1, c);
    Hx = Tx + L3 * cos((a1 - a2 + 0.45937) + PI);
    Hy = Ty + L3 * sin((a1 - a2 + 0.45937) + PI);

    dx = Hx - O2X;
    dy = Hy - O2Y;

    c = sqrt(dx * dx + dy * dy);
    a1 = atan2(dy, dx);
    a2 = return_angle(L1, (L2 - L3), c);
    change_angle.a2=(a1-a2-angle.angle2)/PI*180;
    angle.angle2 = a1 - a2;
    rotate(pwm0, angle2-change_angle.a2); 
    //printf("pwm0:%f\n",angle.angle1);
    usleep(400000);
    //printf("angle0 sleep done\n");
    //rotate(pwm1, angle.angle2);
    usleep(400000);
}
void drawTo(float pX, float pY) //到达指定坐标
{
    float dx, dy, c;
    int i;

    // dx dy of new point
    dx = pX - lastx;
    dy = pY - lasty;
    // path length in mm, times 4 equals 4 steps per mm
    c = floor(4 * sqrt(dx * dx + dy * dy));

    if (c < 1)
        c = 1;

    for (i = 0; i <= c; i++)
    {
        // draw line point by point
        set_XY(lastx + (i * dx / c), lasty + (i * dy / c));
    }

    lastx = pX;
    lasty = pY;
}
void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee)
{
    float inkr = -0.05;
    float count = 0;

    do
    {
        drawTo(sqee * radius * cos(start + count) + bx,
               radius * sin(start + count) + by);
        count += inkr;
    } while ((start + count) > ende);
}
void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee)
{
    float inkr = 0.05;
    float count = 0;

    do
    {
        drawTo(sqee * radius * cos(start + count) + bx,
               radius * sin(start + count) + by);
        count += inkr;
    } while ((start + count) <= ende);
}

void number(float bx, float by, int num, float scale)
{

    switch (num)
    {

    case 0:
        drawTo(bx + 12 * scale, by + 6 * scale);
        //lift(0);
        bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
        //lift(1);
        break;
    case 1:

        drawTo(bx + 3 * scale, by + 15 * scale);
        //drawTo(bx + 10 * scale, by + 20 * scale);
        //drawTo(bx + 10 * scale, by + 0 * scale);
        break;
    case 2:
        drawTo(bx + 2 * scale, by + 12 * scale);
        //bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
        //drawTo(bx + 1 * scale, by + 0 * scale);
        //drawTo(bx + 12 * scale, by + 0 * scale);
        break;
    case 3:
        drawTo(bx + 2 * scale, by + 17 * scale);
        //bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
        //bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
        break;
    case 4:
        drawTo(bx + 10 * scale, by + 0 * scale);
        //drawTo(bx + 10 * scale, by + 20 * scale);
        //drawTo(bx + 2 * scale, by + 6 * scale);
        //drawTo(bx + 12 * scale, by + 6 * scale);
        break;
    case 5:
        drawTo(bx + 2 * scale, by + 5 * scale);
        //bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
        //drawTo(bx + 5 * scale, by + 20 * scale);
        //drawTo(bx + 12 * scale, by + 20 * scale);
        break;
    case 6:
        drawTo(bx + 2 * scale, by + 10 * scale);
        //bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
        //drawTo(bx + 11 * scale, by + 20 * scale);
        break;
    case 7:
        drawTo(bx + 2 * scale, by + 20 * scale);
        //drawTo(bx + 12 * scale, by + 20 * scale);
        //drawTo(bx + 2 * scale, by + 0);
        break;
    case 8:
        drawTo(bx + 5 * scale, by + 10 * scale);
        //bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
        //bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
        break;

    case 9:
        drawTo(bx + 9 * scale, by + 11 * scale);
        //bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
        break;

    case 111:
        //擦除画板，如有边缘未能擦到可以修改下面的位置参数
        //lift();
        // delay(50);
        drawTo(rubberx, rubbery);
        drawTo(70, rubbery);
        drawTo(62, 45);
        drawTo(7, 45);
        drawTo(7, 41);
        drawTo(62, 41);
        drawTo(62, 37);
        drawTo(7, 37);
        drawTo(7, 33);
        drawTo(62, 33);
        drawTo(62, 29);
        drawTo(7, 29);
        drawTo(7, 25);
        drawTo(62, 25);
        drawTo(62, 20);
        drawTo(7, 20);
        drawTo(7, rubbery);
        drawTo(58, rubbery);
        drawTo(rubberx + 3, rubbery);
        //lift();

        break;

    /*case 11:
        //打冒�?
        drawTo(bx + 5 * scale, by + 15 * scale);
        lift(0);
        bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
        lift(1);
        drawTo(bx + 5 * scale, by + 5 * scale);
        lift(0);
        bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
        lift(1);
        break;*/
    }
}
