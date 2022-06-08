#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <font.h>

void voice_broadcast(int * h_m)
{
    char now[10] = "now.mp3";
    char am[10] = "am.mp3";
    char pm[10] = "pm.mp3";
    char dot[10] = "hour.mp3";
    char min[10] = "min.mp3";
    char number[10] = "00.mp3";
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
        number[0] = hour / 10 == 0 ? ' ' : '1'; // 写入小时的十位，如果小时只有一位则将小时的十位置空，否则小时的十位为一
        number[1] = (char)(hour % 10 + 48); // 写入小时的个位
        system(number);
        system(dot);
        number[0] = minute / 10 == 0 ? ' ' : (char)(minute / 10 + 48); // 写入分钟的十位，如果分钟只有一位则将分钟的十位置空
        number[1] = (char)(minute % 10 + 48);
        system(number);
        system(min);
    }
    else
    {
        system(am);
        number[0] = hour / 10 == 0 ? ' ' : '1'; // 写入小时的十位，如果小时只有一位则将小时的十位置空，否则小时的十位为一
        number[1] = (char)(hour % 10 + 48); // 写入小时的个位
        system(number);
        system(dot);
        number[0] = minute / 10 == 0 ? ' ' : (char)(minute / 10 + 48); // 写入分钟的十位，如果分钟只有一位则将分钟的十位置空
        number[1] = (char)(minute % 10 + 48);
        system(number);
        system(min);
    }
}

int main()
{
    int i, h_m[4] = {0}; // h_m数组分别存放当前系统时间小时的十位、个位以及分钟的十位、个位
    int flag = 0; // flag代表组成一个数字的各组坐标的x坐标
    voice_broadcast(h_m); //语音播报

    for (i = 0; i < 4; i++)
    {
        while (LC_Num0[h_m[i]][flag] != 0)
        {
            readl(h_m[i], flag, i + 1); // i + 1分别等于1, 2, 3, 4,对应四个数字
            // 执行结束后得到坐标(Tx, Ty)
            number(point.Tx, point.Ty, h_m[i], 0.9);
            flag++;
        }
     }
}
