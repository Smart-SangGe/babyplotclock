#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <font.h>

void voice_broadcast(int * h_m)
{
    char s[20] = "play ##:##.mp3"; // 系统命令
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

    if (hour > 12)
        hour -= 12;
    // 12h制

    if (hour > 10)
    {
        s[5] = '1'; // 小时个位置1
        hour -= 10;
        itoa(hour, s + 6, 10); // 将hour的个位以十进制并且是字符串的形式写入s[6]，写入后s[7] = '\0'
    }
    else
    {
        s[5] = '0'; // 小时十位置0
        itoa(hour, s + 6, 10);
    }
    // 补全系统命令中的小时

    s[7] = ':'; // 写入小时个位后导致s[7]='\0'
    itoa(minute / 10, s + 8, 10);
    itoa(minute % 10, s + 9, 10);
    s[10] = '.'; // 写入分钟个位后导致s[10]='\0'
    system(s);
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
