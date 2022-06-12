/*
* Author: Deng Qinyu
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "font.h"

void voice_broadcast(int * h_m)
{
    char now[] = "play soundsw.mp3 >> /dev/null 2>&1";
    char am[] = "play sounds.mp3 >> /dev/null 2>&1";
    char pm[] = "play sounds/pm.mp3 >> /dev/null 2>&1";
    char dot[] = "play sounds/hour.mp3 >> /dev/null 2>&1";
    char min[] = "play sounds/min.mp3 >> /dev/null 2>&1";
    char number[] = "play sounds/00.mp3 >> /dev/null 2>&1";
    int hour, minute;

    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = gmtime(&tmpcal_ptr);
    hour = tmp_ptr->tm_hour + 8; // 时区相差八小时
    h_m[0] = hour / 10;
    h_m[1] = hour % 10; // 将当前系统时间的小时的十位和个位拆分
    minute = tmp_ptr->tm_min;
    h_m[2] = minute / 10;
    h_m[3] = minute % 10; // 将当前系统时间的分钟的十位和个位拆分
    // 获取当前时间并分离小时和分钟
    system(now);
    
    if (hour > 12)
    {
        system(pm);
        hour -= 12;
        number[12] = (char)(hour / 10 + 48); // 写入小时的十位，如果小时只有一位则将小时的十位置空，否则小时的十位为一
        number[13] = (char)(hour % 10 + 48); // 写入小时的个位
        system(number);
        system(dot);
        number[12] = (char)(minute / 10 + 48); // 写入分钟的十位，如果分钟只有一位则将分钟的十位置空
        number[13] = (char)(minute % 10 + 48);
        system(number);
        system(min);
    }
    else
    {
        system(am);
        number[12] = (char)(hour / 10 + 48); // 写入小时的十位，如果小时只有一位则将小时的十位置空，否则小时的十位为一
        number[13] = (char)(hour % 10 + 48); // 写入小时的个位
        system(number);
        system(dot);
        number[12] = (char)(minute / 10 + 48); // 写入分钟的十位，如果分钟只有一位则将分钟的十位置空
        number[13] = (char)(minute % 10 + 48);
        system(number);
        system(min);
    }
}

int main()
{
    int i, h_m[4] = {0}; // h_m数组分别存放当前系统时间小时的十位、个位以及分钟的十位、个位
    int flag = 0, k = 0; // flag代表组成一个数字的各组坐标的x坐标
    for(i = 0; i < 3; i++){
        voice_broadcast(h_m); 
        // 语音播报并给h_m数组赋值
        printf("playing");
    }

    init(); // 初始化
    // mraa_gpio_write(gpio1, 1); // 继电器通电，控制抬臂舵机
    // lift(2); // 高抬臂
    
    for (i = 0; i < 4; i++)
    {
        flag = 0;
        k = 0;
        printf("now input the number is %d",h_m[i]);
        
        while (LC_Num0[h_m[i] - 1][flag] != 0)
        {
            
            readl(h_m[i] - 1, flag, i + 1); // i + 1分别等于1, 2, 3, 4,对应四个数字
            // 执行结束后得到坐标(Tx, Ty)
            // mraa_gpio_write(gpio1, 0); // 继电器断电，控制左右臂舵机
            number(point.Tx, point.Ty, h_m[i], 0.9);

            if (!k)
            {
                // mraa_gpio_write(gpio1, 1); // 继电器通电，控制抬臂舵机
                // lift(0);
            }
                
            k = 1; // 表示落笔完成，之后循环
            flag++;
        }

        // mraa_gpio_write(gpio1, 1); // 继电器通电，控制抬臂舵机
        // lift(1); // 写字状态抬臂
     }

    // mraa_gpio_write(gpio1, 1); // 继电器通电，控制抬臂舵机
    // lift(2);
    // mraa_gpio_write(gpio1, 0); // 继电器断电，控制左右臂舵机
    // number(0, 0, 111, 1); // 控制机械臂擦除字迹，该情况不使用bx, by, 故bx，by置零
}