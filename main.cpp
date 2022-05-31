#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void voice_broadcast(void)
{
    char s[20] = "play ##:##.mp3"; // 系统命令
    int hour, minute;

    time_t tmpcal_ptr; 
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = gmtime(&tmpcal_ptr);
    hour = tmp_ptr->tm_hour + 8; // 时区相差八小时
    minute = tmp_ptr->tm_min;
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
    voice_broadcast(); //语音播报
    write();
    clean();
}
        